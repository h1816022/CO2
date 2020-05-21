/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Atom Sound Data (Cue)
 * File     : SoundAtomCue.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "SoundAtomCue.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareRuntimePrivatePCH.h"

/* Unreal Engine 4関連ヘッダ */
#include "Serialization/CustomVersion.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "SoundAtomCue"

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/

/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      クラス宣言
 *      Prototype Classes
 ***************************************************************************/

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/***************************************************************************
 *      変数定義
 *      Variable Definition
 ***************************************************************************/
/* バージョン番号 */
namespace SoundAtomCue
{
	enum Type
	{
		/* バージョン番号が付与される前 */
		BeforeCustomVersionWasAdded = 0,

		/* バージョン情報を追加 */
		StoreVersionInfo,

		/* キュー名をアセットに保持 */
		StoreCueName,

		/* SoundConcurrency情報をアセットに保持 */
		StoreSoundConcurrency,

		/* 最新バージョンの番号を取得するための番兵 */
		VersionPlusOne,

		/* 最新バージョンの番号を指す */
		LatestVersion = VersionPlusOne - 1,
	};
}

/* バージョン番号 */
const int32 FAtomCueVersion::AssetVersion = SoundAtomCue::LatestVersion;

/* GUID */
const FGuid FAtomCueVersion::AssetGuid(0x0FAD527A, 0xEEC1492E, 0x8819E1BB, 0xE3B780B9);

/* バージョン登録 */
FCustomVersionRegistration GAtomCueVersion(
	FAtomCueVersion::AssetGuid, FAtomCueVersion::AssetVersion, TEXT("AtomCueAssetVersion"));

/***************************************************************************
 *      定数定義
 *      Constant Definition
 ***************************************************************************/
namespace {
	float ATTENUATION_DISTANCE_NOT_INITIALIZED = -1.0f;
}

/***************************************************************************
 *      クラス定義
 *      Class Definition
 ***************************************************************************/
USoundAtomCue::USoundAtomCue(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	/* Localization of unreal properties metadata with LOCTEXT markups and reflection */
	CRI_LOCCLASS(GetClass());
#endif

	CueSheet = nullptr;
	bApplyAtomParameter = false;
	RawPCMData = nullptr;
	RawPCMDataChannels = 0;
	RawPCMDataSamplingRate = 0;
	RawPCMDataSamples = 0;
	SoundConcurrencySettings = nullptr;
	Priority = 0.0f;

#if WITH_EDITOR
	Duration = -1.0f;
	UserData.Reset();
	CategoryName.Reset();
	AisacControlName.Reset();
	MaxAttenuationDistance = ATTENUATION_DISTANCE_NOT_INITIALIZED;
	MinAttenuationDistance = ATTENUATION_DISTANCE_NOT_INITIALIZED;
#endif
}

int32 USoundAtomCue::GetLength()
{
	/* CueSheet未指定時は0を返す */
	/* 備考）シーケンスクック時にアセットがロードされていない状態で         */
	/* 　　　GetLengthが呼ばれる可能性があるので、エラーにしてはいけない。  */
	if (CueSheet == NULL) {
		return 0;
	}

	/* キューシートからキューの長さを取得 */
	int64 Length;
	CueSheet->AddRef();
	{
		Length = criAtomExAcb_GetLengthByName(CueSheet->GetAcbHn(), TCHAR_TO_UTF8(*CueName));
	}
	CueSheet->Release();

	/* Blueprintで扱えるのは32bit値まで */
	if (Length > MAX_int32) {
		UE_LOG(LogCriWareRuntime, Warning, TEXT("Length of Cue is longer than MAX_int32."));
		Length = MAX_int32;
	}

	return (int32)Length;
}

FString USoundAtomCue::GetUserData()
{
	FString String;

	if (CueSheet == NULL) {
		UE_LOG(LogCriWareRuntime, Error, TEXT("CueSheet is not set."));
		return String;
	}

	/* キューシートからユーザデータを取得 */
	CueSheet->AddRef();
	{
		const char* UserDataCPtr = criAtomExAcb_GetUserDataByName(CueSheet->GetAcbHn(), TCHAR_TO_UTF8(*CueName));
		if (UserDataCPtr != nullptr) {
			String = FString(UTF8_TO_TCHAR(UserDataCPtr));
		}
	}
	CueSheet->Release();

	return String;
}

void USoundAtomCue::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	/* アセットバージョンの使用を通知 */
	Ar.UsingCustomVersion(FAtomCueVersion::AssetGuid);

	/* バージョンチェック */
	if (Ar.IsLoading()) {
		/* アーカイブのバージョンをチェック */
		int32 archiveVer = Ar.CustomVer(FAtomCueVersion::AssetGuid);

		/* キューシート名がない場合は補完 */
		if (archiveVer < SoundAtomCue::StoreCueName) {
			CueName = GetFName().ToString();
		}

		/* 初期バージョン専用の処理 */
		if (archiveVer < SoundAtomCue::StoreVersionInfo) {
			SerializeOldVersion(Ar);
			return;
		}
	}
}

void USoundAtomCue::PostLoad()
{
	Super::PostLoad();

#if WITH_EDITOR
	/* ACFがロード済みかどうかチェック */
	bool bIsAcfLoaded = UCriWareInitializer::IsAcfLoaded();
	if (bIsAcfLoaded == false) {
		/* ACF未ロード時は情報を表示しない */
		return;
	}

	/* キューシートが設定されているかどうかチェック */
	if (CueSheet == NULL) {
		/* キューシート未設定時は情報を表示しない */
		return;
	}

	/* キューシートから各種情報を取得 */
	CueSheet->AddRef();
	{
		/* キュー情報の取得 */
		CriAtomExCueInfo CueInfo;
		CriBool bResult = criAtomExAcb_GetCueInfoByName(
			CueSheet->GetAcbHn(), TCHAR_TO_UTF8(*CueName), &CueInfo);
		if (bResult != CRI_FALSE) {
			/* キューの長さを取得 */
			if (CueInfo.length >= 0) {
				Duration = (float)CueInfo.length * 0.001f;
			} else {
				Duration = -1.0f;
			}

			/* ユーザーデータの取得 */
			if (CueInfo.user_data != nullptr) {
				UserData = FString(UTF8_TO_TCHAR(CueInfo.user_data));
			}

			/* カテゴリ名一覧の取得 */
			CategoryName.Reset();
			for (int i = 0; i < CRIATOMEXCATEGORY_MAX_CATEGORIES_PER_PLAYBACK; i++) {
				CriAtomExCategoryInfo CategoryInfo;
				CriBool result = criAtomExAcf_GetCategoryInfo(CueInfo.categories[i], &CategoryInfo);
				if (result == CRI_FALSE) {
					break;
				}
				CategoryName.Add(CategoryInfo.name);
			}
		}

		/* AISACコントロール名一覧の取得 */
		AisacControlName.Reset();
		CriSint32 NumControls = criAtomExAcb_GetNumUsableAisacControlsByName(CueSheet->GetAcbHn(), TCHAR_TO_UTF8(*CueName));
		for (int i = 0; i < NumControls; i++) {
			CriAtomExAisacControlInfo ControlInfo;
			CriBool result = criAtomExAcb_GetUsableAisacControlByName(
				CueSheet->GetAcbHn(), TCHAR_TO_UTF8(*CueName), (CriUint16)i, &ControlInfo);
			if (result != CRI_FALSE) {
				AisacControlName.Add(ControlInfo.name);
			}
		}
	}
	CueSheet->Release();
#endif
}

void USoundAtomCue::BeginDestroy()
{
	/* リソースの解放 */
	if (RawPCMData != nullptr) {
		FMemory::Free(RawPCMData);
		RawPCMData = nullptr;
	}

	Super::BeginDestroy();
}

const FSoundConcurrencySettings* USoundAtomCue::GetSoundConcurrencySettingsToApply() const
{
	if (SoundConcurrencySettings)
	{
		return &SoundConcurrencySettings->Concurrency;
	}
	return nullptr;
}

uint32 USoundAtomCue::GetSoundConcurrencyObjectID() const
{
	if (SoundConcurrencySettings)
	{
		return SoundConcurrencySettings->GetUniqueID();
	}
	return INDEX_NONE;
}

/* 旧バージョンデータの読み込み */
void USoundAtomCue::SerializeOldVersion(FArchive& Ar)
{
	UE_LOG(LogCriWareRuntime, Warning, TEXT("Atom Cue asset is not compatible. (%s)"), *GetFName().ToString());

	/* キューシート名を保存 */
	/* 備考）2014/03以前のデータを扱うための処理。 */
	Ar << CueSheetName;
}

#if WITH_EDITOR
float USoundAtomCue::GetMaxAttenuationDistance()
{
	if (MaxAttenuationDistance == ATTENUATION_DISTANCE_NOT_INITIALIZED) {
		if (ReadCueInfo() == false) {
			return 0.0f;
		}
	}
	return MaxAttenuationDistance;
}

float USoundAtomCue::GetMinAttenuationDistance()
{
	if (MinAttenuationDistance == ATTENUATION_DISTANCE_NOT_INITIALIZED) {
		if (ReadCueInfo() == false) {
			return 0.0f;
		}
	}
	return MinAttenuationDistance;
}

bool USoundAtomCue::ReadCueInfo()
{
	if (CueSheet == NULL) {
		return false;
	}

	CriAtomExCueInfo cueInfo = {0};

	CriBool isGetCueInfoSucceed = CRI_FALSE;
	CueSheet->AddRef();
	{
		if (criAtomExAcb_ExistsName(static_cast<CriAtomExAcbHn>(CueSheet->GetAcbHn()), TCHAR_TO_UTF8(*(CueName))) == CRI_TRUE) {
			isGetCueInfoSucceed = criAtomExAcb_GetCueInfoByName(static_cast<CriAtomExAcbHn>(CueSheet->GetAcbHn()), TCHAR_TO_UTF8(*(CueName)), &cueInfo);
		}
	}
	CueSheet->Release();

	if (isGetCueInfoSucceed == CRI_FALSE) {
		return false;
	}

	MaxAttenuationDistance = cueInfo.pos3d_info.max_distance;
	MinAttenuationDistance = cueInfo.pos3d_info.min_distance;

	return true;
}
#endif // WITH_EDITOR

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/
#undef LOCTEXT_NAMESPACE

/* --- end of file --- */
