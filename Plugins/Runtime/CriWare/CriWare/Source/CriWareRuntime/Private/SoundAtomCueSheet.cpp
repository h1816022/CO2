/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Atom Sound Data (CueSheet)
 * File     : SoundAtomCueSheet.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "SoundAtomCueSheet.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareRuntimePrivatePCH.h"
#include "AtomSoundData.h"

/* Unreal Engine 4関連ヘッダ */
#include "UObject/Package.h"
#include "Serialization/CustomVersion.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "SoundAtomCueSheet"

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
namespace SoundAtomCueSheet
{
	enum Type
	{
		/* バージョン番号が付与される前 */
		BeforeCustomVersionWasAdded = 0,

		/* ACBファイルの取り込みに対応 */
		IncludeAcb,

		/* UAssetImportDataによるアセット管理に対応 */
		IncludeAssetImportData,

		/* キューシート名をアセットに保持 */
		StoreCueSheetName,

		/* スロット数をアセットに保持 */
		StoreNumSlots,

		/* 最新バージョンの番号を取得するための番兵 */
		VersionPlusOne,

		/* 最新バージョンの番号を指す */
		LatestVersion = VersionPlusOne - 1,
	};
}

/* バージョン番号 */
const int32 FAtomCueSheetVersion::AssetVersion = SoundAtomCueSheet::LatestVersion;

/* GUID */
const FGuid FAtomCueSheetVersion::AssetGuid(0x29391EC5, 0xA293410D, 0x88C35FCB, 0x2E48DBBC);

/* バージョン登録 */
FCustomVersionRegistration GAtomCueSheetVersion(
	FAtomCueSheetVersion::AssetGuid, FAtomCueSheetVersion::AssetVersion, TEXT("AtomCueSheetAssetVersion"));

/***************************************************************************
 *      クラス定義
 *      Class Definition
 ***************************************************************************/
USoundAtomCueSheet::USoundAtomCueSheet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	/* Localization of unreal properties metadata with LOCTEXT markups and reflection */
	CRI_LOCCLASS(GetClass());
#endif

	bOverrideAwbDirectory = false;
	NumSlots = -1;
	Binder = NULL;
	ResourceData = NULL;
	AcbHn = NULL;
	ReferenceCount.Reset();
}

USoundAtomCueSheet* USoundAtomCueSheet::Find(FName AcbName, FString PackagePath)
{
	/* ACBファイル名の取得 */
	FString AcbNameString = AcbName.ToString();

	/* 既存ACBオブジェクトの検索 */
	USoundAtomCueSheet* AcbData = (USoundAtomCueSheet*)StaticFindObject(
		USoundAtomCueSheet::StaticClass(), ANY_PACKAGE, *AcbNameString);

	if ((AcbData == nullptr) && (!PackagePath.IsEmpty())) {
		/* ACBオブジェクトが見つからない場合はパッケージを検索してロード */
		/* 備考）フルパスでのサーチを優先。 */
		FString PackageName = PackagePath + "/" + AcbNameString;
		UPackage* Pkg = FindPackage(nullptr, *PackageName);
		if (Pkg == nullptr) {
			Pkg = LoadPackage(nullptr, *PackageName, LOAD_None);
		}

		/* ACBオブジェクトの再検索 */
		AcbData = (USoundAtomCueSheet*)StaticFindObject(
			USoundAtomCueSheet::StaticClass(), ANY_PACKAGE, *AcbNameString);
	}

	if (AcbData == nullptr) {
		/* フルパスでACBオブジェクトが見つからない場合はアセット名のみで再検索 */
		UPackage* Pkg = FindPackage(nullptr, *AcbNameString);
		if (Pkg == nullptr) {
			Pkg = LoadPackage(nullptr, *AcbNameString, LOAD_None);
		}

		/* ACBオブジェクトの再検索 */
		AcbData = (USoundAtomCueSheet*)StaticFindObject(
			USoundAtomCueSheet::StaticClass(), ANY_PACKAGE, *AcbNameString);
	}

	if (AcbData == nullptr) {
		/* ACBオブジェクトが見つからない場合はuassetファイル自体を検索 */
		FString AssetFileName = AcbName.ToString() + TEXT(".uasset");
		TArray<FString> AssetFiles;
		IFileManager::Get().FindFilesRecursive(
			AssetFiles, *FPaths::ProjectContentDir(), *AssetFileName, true, false);
		for (FString& AssetPath : AssetFiles) {
			UPackage* Package = LoadPackage(nullptr, *AssetPath, LOAD_None);
		}

		/* ACBオブジェクトの再検索 */
		AcbData = (USoundAtomCueSheet*)StaticFindObject(
			USoundAtomCueSheet::StaticClass(), ANY_PACKAGE, *AcbNameString);
	}

	/* エラーチェック */
	if (AcbData == nullptr) {
		UE_LOG(LogCriWareRuntime, Error, TEXT("Failed to load '%s' (Atom Cue Sheet)."), *AcbNameString);
		return nullptr;
	}

	return AcbData;
}

USoundAtomCueSheet* USoundAtomCueSheet::LoadAtomCueSheet(USoundAtomCueSheet* CueSheet)
{
	/* オブジェクトを管理するActorを作成 */
	/* 備考）USoundAtomCueSheet単体ではプレビュー終了時等にACBをReleaseできない	*/
	/* 　　　（終了を検知できない）ため、破棄処理専用の管理アクタを作成する。	*/
	AAtomSoundData* NewActor = GWorld->SpawnActor<AAtomSoundData>();

	/* キューシートの実体をロード */
	NewActor->LoadCueSheet(CueSheet);

	return CueSheet;
}

USoundAtomCueSheet* USoundAtomCueSheet::LoadAcb(FName AcbName)
{
	/* ファイル名だとエディタでしか読めないのでパスで指定する */
	FString AcbPath = AcbName.ToString();

	/* パスの分解 */
	FString FileDir, FileName, FileExt;
	FPaths::Split(AcbPath, FileDir, FileName, FileExt);

	/* 拡張子を含まないフルパスを作成 */
	FString PackageName;
	if (FPaths::IsRelative(AcbPath)) {
		PackageName = "/Game/" + FileDir + "/" + FileName;
	} else {
		PackageName = FileDir + "/" + FileName;
	}

	/* 「/」の重複を回避 */
	/* 注意）「/」の重複があるとLoadObject内で例外が発生する。 */
	FPaths::RemoveDuplicateSlashes(PackageName);

	/* 既存ACBオブジェクトの検索 */
	FPaths::Split(PackageName, FileDir, FileName, FileExt);
	USoundAtomCueSheet* AcbData = USoundAtomCueSheet::Find(FName(*FileName), FileDir);

	/* AtomCueSheetの有効化 */
	AcbData = USoundAtomCueSheet::LoadAtomCueSheet(AcbData);

	return AcbData;
}

void USoundAtomCueSheet::ReleaseAcb(FName AcbName)
{
	/* 不具合対策のため機能を無効化 */
}

void USoundAtomCueSheet::AddRef(void)
{
	/* リファレンスカウンタの更新 */
	int32 Result = ReferenceCount.Increment();
	if (Result != 1) {
		return;
	}

	/* GCを回避 */
	AddToRoot();

	/* リソースの確保 */
	MakeSureAtomCueSheetIsLoaded();
}

void USoundAtomCueSheet::Release(void)
{
	/* 既にリリース済みの場合は何もしない */
	int32 Current = ReferenceCount.GetValue();
	if (Current == 0) {
		return;
	}

	/* リファレンスカウンタの更新 */
	int32 Result = ReferenceCount.Decrement();
	if (Result != 0) {
		return;
	}

	/* リソースの破棄 */
	ForceUnload();

	/* GCを許可 */
	RemoveFromRoot();
}

void USoundAtomCueSheet::MakeSureAtomCueSheetIsLoaded()
{
	FScopeLock Lock(&CriticalSection);

	/* 既にロード済みの場合は何もしない */
	if (AcbHn != NULL) {
		return;
	}

	/* データディレクトリの取得 */
	FString BaseName;
	if (bOverrideAwbDirectory == false) {
		BaseName = UCriWareInitializer::GetContentDir();
	} else {
		BaseName = FPaths::ProjectContentDir() + AwbDirectory.Path;
	}

	/* パスの終端に「/」を付加 */
	if (BaseName.EndsWith(TEXT("/")) == false) {
		BaseName += "/";
	}

	/* キューシート名を付加 */
	BaseName += CueSheetName;

	/* ACBファイル名、AWBファイル名の作成 */
	FString AcbName = BaseName + TEXT(".acb");
	FString AwbName = BaseName + TEXT(".awb");

	/* RawデータからACBを展開 */
	if (ResourceData == nullptr) {
		if (RawData.GetBulkDataSize() > 0) {
			RawData.GetCopy((void**)&ResourceData, false);
		}
	}

	/* ACBファイルのロード */
	if (ResourceData != nullptr) {
		/* uasset内にACBデータが保持されている場合はメモリからロード */
		AcbHn = criAtomExAcb_LoadAcbData(
			(void *)ResourceData, (CriSint32)RawData.GetBulkDataSize(), Binder, TCHAR_TO_UTF8(*AwbName), NULL, 0);
	} else {
		/* uasset内にACBデータが保持されていない場合はファイルからロード（旧バージョンのデータが該当） */
		AcbHn = criAtomExAcb_LoadAcbFile(
			NULL, TCHAR_TO_UTF8(*AcbName), Binder, TCHAR_TO_UTF8(*AwbName), NULL, 0);
	}

	/* ロード結果の表示 */
	if (AcbHn != NULL) {
		UE_LOG(LogCriWareRuntime, Verbose, TEXT("'%s' is loaded."), *GetFullName());
	}
}

void USoundAtomCueSheet::ForceUnload()
{
	FScopeLock Lock(&CriticalSection);

	/* リソースが解放済みの場合は何もしない */
	if (AcbHn == NULL) {
		return;
	}

	/* ライブラリが初期化済みかどうかチェック */
	/* 注意）GC処理の順序によっては、ライブラリ初期化後にここに来る可能性がある。	*/
	/* 備考）criAtomExAcb_LoadAcbFile関数失敗時はAcbHnがNULLになる。				*/
	if ((criAtomEx_IsInitialized() != CRI_FALSE) && (AcbHn != NULL)) {
		/* ACBハンドルの破棄 */
		criAtomExAcb_Release(AcbHn);
		AcbHn = NULL;
	}

	/* バインダの破棄 */
	if (Binder != NULL) {
#if !defined(CRIWARE_UE4_LE)	/* <cri_delete_if_LE> */
#endif 	/* </cri_delete_if_LE> */
		Binder = NULL;
	}

	/* 展開済みデータの破棄 */
	if (ResourceData != nullptr) {
		FMemory::Free(ResourceData);
		ResourceData = nullptr;
	}

	/* リリース結果の表示 */
	UE_LOG(LogCriWareRuntime, Verbose, TEXT("'%s' is released."), *GetFullName());
}

bool USoundAtomCueSheet::IsLoaded()
{
	FScopeLock Lock(&CriticalSection);

	return (AcbHn != NULL);
}

USoundAtomCue* USoundAtomCueSheet::GetAtomCueByIndex(int32 CueIndex)
{
	/* キューシートハンドルへのアクセスを保証 */
	MakeSureAtomCueSheetIsLoaded();

	/* キュー情報の取得 */
	CriAtomExCueInfo CueInfo;
	CriBool bResult = criAtomExAcb_GetCueInfoByIndex(AcbHn, CueIndex, &CueInfo);
	if (bResult == CRI_FALSE) {
		return nullptr;
	}

	/* キューオブジェクトの作成 */
	USoundAtomCue* NewAtomCue = NewObject<USoundAtomCue>(this);

	/* パラメータの設定 */
	NewAtomCue->CueName = UTF8_TO_TCHAR(CueInfo.name);
	NewAtomCue->CueSheet = this;

	return NewAtomCue;
}

USoundAtomCue* USoundAtomCueSheet::GetAtomCueById(int32 CueId)
{
	/* キューシートハンドルへのアクセスを保証 */
	MakeSureAtomCueSheetIsLoaded();

	/* キュー情報の取得 */
	CriAtomExCueInfo CueInfo;
	CriBool bResult = criAtomExAcb_GetCueInfoById(AcbHn, CueId, &CueInfo);
	if (bResult == CRI_FALSE) {
		return nullptr;
	}

	/* キューオブジェクトの作成 */
	USoundAtomCue* NewAtomCue = NewObject<USoundAtomCue>(this);

	/* パラメータの設定 */
	NewAtomCue->CueName = UTF8_TO_TCHAR(CueInfo.name);
	NewAtomCue->CueSheet = this;

	return NewAtomCue;
}

USoundAtomCue* USoundAtomCueSheet::GetAtomCueByName(FString CueName)
{
	/* キューシートハンドルへのアクセスを保証 */
	MakeSureAtomCueSheetIsLoaded();

	/* キュー情報の取得 */
	CriAtomExCueInfo CueInfo;
	CriBool bResult = criAtomExAcb_GetCueInfoByName(AcbHn, TCHAR_TO_UTF8(*CueName), &CueInfo);
	if (bResult == CRI_FALSE) {
		return nullptr;
	}

	/* キューオブジェクトの作成 */
	USoundAtomCue* NewAtomCue = NewObject<USoundAtomCue>(this);

	/* パラメータの設定 */
	NewAtomCue->CueName = UTF8_TO_TCHAR(CueInfo.name);
	NewAtomCue->CueSheet = this;

	return NewAtomCue;
}

void USoundAtomCueSheet::AttachDspBusSetting(FString SettingName)
{
	/* ライブラリが初期化済みかどうかチェック */
	/* 注意）GC処理の順序によっては、ライブラリ初期化後にここに来る可能性がある。 */
	if (criAtomEx_IsInitialized() != CRI_FALSE) {
		/* DSPバス設定の適用 */
		criAtomEx_AttachDspBusSetting(TCHAR_TO_UTF8(*SettingName), NULL, 0);
	}
}

void USoundAtomCueSheet::DetachDspBusSetting()
{
	/* ライブラリが初期化済みかどうかチェック */
	/* 注意）GC処理の順序によっては、ライブラリ初期化後にここに来る可能性がある。 */
	if (criAtomEx_IsInitialized() != CRI_FALSE) {
		/* DSPバス設定の無効化 */
		criAtomEx_DetachDspBusSetting();
	}
}

void USoundAtomCueSheet::ApplyDspBusSnapshot(FString SnapshotName, int32 Milliseconds)
{
	/* ライブラリが初期化済みかどうかチェック */
	/* 注意）GC処理の順序によっては、ライブラリ初期化後にここに来る可能性がある。 */
	if (criAtomEx_IsInitialized() != CRI_FALSE) {
		/* DSPバススナップショットの適用 */
		criAtomEx_ApplyDspBusSnapshot(TCHAR_TO_UTF8(*SnapshotName), Milliseconds);
	}
}

void USoundAtomCueSheet::PostInitProperties()
{
#if WITH_EDITORONLY_DATA
	if (!HasAnyFlags(RF_ClassDefaultObject)) {
		AssetImportData = NewObject<UAssetImportData>(this, TEXT("AssetImportData"));
	}
#endif

	Super::PostInitProperties();
}

void USoundAtomCueSheet::BeginDestroy()
{
	ForceUnload();

	Super::BeginDestroy();
}

void USoundAtomCueSheet::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	/* アセットバージョンの使用を通知 */
	Ar.UsingCustomVersion(FAtomCueSheetVersion::AssetGuid);

#if WITH_EDITORONLY_DATA
	if ((Ar.IsLoading()) && (AssetImportData == nullptr)) {
		// AssetImportData should always be valid
		AssetImportData = NewObject<UAssetImportData>(this, TEXT("AssetImportData"));
	}
#endif

	/* バージョンチェック */
	if (Ar.IsLoading()) {
		/* アーカイブのバージョンをチェック */
		int32 ArchiveVer = Ar.CustomVer(FAtomCueSheetVersion::AssetGuid);

		/* 初期バージョン専用の処理 */
		if (ArchiveVer < SoundAtomCueSheet::IncludeAcb) {
			SerializeOldVersion(Ar);
			return;
		}

		/* Ver.1アセットはVer.2アセットに変換 */
		if (ArchiveVer < SoundAtomCueSheet::IncludeAssetImportData) {
			UpdateAsset();
		}

		/* キューシート名がない場合は補完 */
		if (ArchiveVer < SoundAtomCueSheet::StoreCueSheetName) {
			CueSheetName = GetFName().ToString();
		}

		/* スロット数がない場合は補完 */
		if (ArchiveVer < SoundAtomCueSheet::StoreNumSlots) {
			NumSlots = -1;
		}
	}

	/* ACBデータのシリアライズ */
	RawData.Serialize(Ar, this);
}

#if WITH_EDITOR
void USoundAtomCueSheet::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	bool bIsRelative = FPaths::IsRelative(AwbDirectory.Path);
	if (bIsRelative == false) {
		FPaths::MakePathRelativeTo(AwbDirectory.Path, *FPaths::ProjectContentDir());
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

/* 旧バージョンデータの読み込み */
void USoundAtomCueSheet::SerializeOldVersion(FArchive& Ar)
{
	UE_LOG(LogCriWareRuntime, Warning, TEXT("Atom Cue Sheet asset is not compatible. (%s)"), *GetFName().ToString());

	/* パス文字列のチェック */
	/* 注意）2013/10以前のACBアセットには本パラメータが含まれない。 */
	if (AcbFilePath.Len() > 0) {
		/* ACBファイルパスを保存 */
		Ar << AcbFilePath;
	}

	/* ACBデータのチェック */
	/* 注意）2015/02以前のACBアセットには本パラメータが含まれない。 */
	if ((RawData.IsBulkDataLoaded()) && (RawData.GetElementSize() > 0)) {
		/* ACBデータの保存 */
		RawData.Serialize(Ar, this);
	}

	/* キューシート名の補完 */
	CueSheetName = GetFName().ToString();
}

void USoundAtomCueSheet::UpdateAsset()
{
	/* ACBファイルパスが指定されている場合はインポート用のパスとして使用。 */
	FString ResolvedSourceFilePath = AcbFilePath;
	if ((ResolvedSourceFilePath.Contains(":") == false)
		&& (ResolvedSourceFilePath.StartsWith("/") == false)
		&& (ResolvedSourceFilePath.StartsWith("\\") == false)) {
		ResolvedSourceFilePath = FPaths::Combine(*UCriWareInitializer::GetContentDir(), *ResolvedSourceFilePath);
	}

	if (AcbFilePath.Len() > 0) {
		/* 旧ACBファイルディレクトリをAWBファイルディレクトリに設定 */
		AwbDirectory.Path = ResolvedSourceFilePath;
		FPaths::MakePathRelativeTo(AwbDirectory.Path, *FPaths::ProjectContentDir());

		/* AWBディレクトリの上書きを有効化 */
		bOverrideAwbDirectory = true;
	}

#if WITH_EDITORONLY_DATA
	/* 旧ACBファイルディレクトリパスを元にACBファイルパス名を特定 */
	/* 備考）ファイルが存在するかどうか不明なのでパス情報のみを更新。 */
	const FString FileName = GetName() + ".acb";
	ResolvedSourceFilePath = FPaths::Combine(*ResolvedSourceFilePath, *FileName);
	AssetImportData->UpdateFilenameOnly(ResolvedSourceFilePath);
#endif
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/
#undef LOCTEXT_NAMESPACE

/* --- end of file --- */
