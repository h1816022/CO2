/****************************************************************************
*
* CRI Middleware SDK
*
* Copyright (c) 2018 CRI Middleware Co., Ltd.
*
* Library  : CRIWARE plugin for Unreal Engine 4
* Module   : Atom Sound Manager
* File     : AtomSoundManager.cpp
*
****************************************************************************/

/***************************************************************************
*      インクルードファイル
*      Include files
***************************************************************************/
/* モジュールヘッダ */
#include "AtomSoundManager.h"
#include "AtomListener.h"
#include "CriWareInitializer.h"
#include "AtomParameterComponent.h"
#include "Sound/SoundAttenuation.h"

#include "Engine/LocalPlayer.h"

#if WITH_EDITOR
#include "Editor.h"
#include "DrawDebugHelpers.h"
#endif

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "AtomSoundManager"

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
int64 FAtomSoundManager::AtomSoundID = 0;
TMap<int64, class FAtomSoundSettingsForAnimNotify*> FAtomSoundManager::AtomSoundSettingsForAnimNotifyMap;

/***************************************************************************
 *      クラス定義
 *      Class Definition
 ***************************************************************************/
FAtomSoundSettingsForAnimNotify::FAtomSoundSettingsForAnimNotify()
{
	PlayerHn = NULL;
	SourceHn = NULL;
	PlaybackId = -1;
	CueSheetPtr.Reset();
	ParameterPtr.Reset();
	AttachToComponent.Reset();
	SoundAttenuation.Reset();

#if WITH_EDITOR
	SpriteComponent = nullptr;
	bInitDebugShowingInfo = false;
#endif

	AtomActiveSound = new FAtomActiveSound();
}

FAtomSoundSettingsForAnimNotify::~FAtomSoundSettingsForAnimNotify()
{
#if WITH_EDITOR
	if (SpriteComponent) {
		if (SpriteComponent->GetFName().IsValid()) {
			if (SpriteComponent->GetFName().ToString().Contains("BillboardComponent")
				&& !SpriteComponent->IsBeingDestroyed()) {
				SpriteComponent->DestroyComponent();
			}
			SpriteComponent = nullptr;
		}
	}
	bInitDebugShowingInfo = false;
#endif

	delete AtomActiveSound;
}

FAtomSoundSettingsForAnimNotify* FAtomSoundSettingsForAnimNotify::Create()
{
	/* オブジェクトの作成 */
	FAtomSoundSettingsForAnimNotify* AtomSoundSetting = new FAtomSoundSettingsForAnimNotify();
	if (!AtomSoundSetting) {
		return nullptr;
	}

	/* ソースの作成 */
	AtomSoundSetting->SourceHn = criAtomEx3dSource_Create(NULL, NULL, 0);
	if (AtomSoundSetting->SourceHn == NULL) {
		AtomSoundSetting->Destroy();
		return nullptr;
	}

	/* プレーヤの作成 */
	/* 備考）ユーザの操作対象ではないので、再生時刻は取得しない。 */
	CriAtomExPlayerConfig PlayerConfig;
	criAtomExPlayer_SetDefaultConfig(&PlayerConfig);
	PlayerConfig.updates_time = CRI_FALSE;
	AtomSoundSetting->PlayerHn = criAtomExPlayer_Create(&PlayerConfig, NULL, 0);
	if (AtomSoundSetting->PlayerHn == NULL) {
		AtomSoundSetting->Destroy();
		return nullptr;
	}

	/* 7.1ch環境向けにパンスピーカータイプを設定 */
	criAtomExPlayer_SetPanSpeakerType(AtomSoundSetting->PlayerHn, CRIATOMEX_PAN_SPEAKER_TYPE_6CH);

	return AtomSoundSetting;
}

void FAtomSoundSettingsForAnimNotify::Destroy()
{
	/* ソースとプレーヤを破棄 */
	/* 注意）GC処理の順序によっては、ライブラリ終了処理後にここに来る可能性がある。 */
	if (criAtomEx_IsInitialized() != CRI_FALSE) {
		if (PlayerHn != NULL) {
			criAtomExPlayer_Destroy(PlayerHn);
		}
		if (SourceHn != NULL) {
			criAtomEx3dSource_Destroy(SourceHn);
		}
	}

	DefaultListener = NULL;

	/* オブジェクトの破棄 */
	delete this;
}

float FAtomSoundSettingsForAnimNotify::GetTime()
{
	CriSint64 TimeMS = criAtomExPlayback_GetTime(PlaybackId);
	if (TimeMS < 0) {
		return -1.0f;
	}
	else {
		return ((float)TimeMS * 0.001f);
	}
}

EAtomComponentStatus FAtomSoundSettingsForAnimNotify::GetStatus()
{
	if (PlayerHn == NULL) {
		return EAtomComponentStatus::Error;
	}

	/* AtomExプレーヤのステータスを取得 */
	CriAtomExPlayerStatus PlayerStatus = criAtomExPlayer_GetStatus(PlayerHn);

	/* コンポーネントのステータスに変換 */
	EAtomComponentStatus ComponentStatus;
	switch (PlayerStatus) {
	case CRIATOMEXPLAYER_STATUS_STOP:
		ComponentStatus = EAtomComponentStatus::Stop;
		break;

	case CRIATOMEXPLAYER_STATUS_PREP:
		ComponentStatus = EAtomComponentStatus::Prep;
		break;

	case CRIATOMEXPLAYER_STATUS_PLAYING:
		ComponentStatus = EAtomComponentStatus::Playing;
		break;

	case CRIATOMEXPLAYER_STATUS_PLAYEND:
		ComponentStatus = EAtomComponentStatus::PlayEnd;
		break;

	default:
		ComponentStatus = EAtomComponentStatus::Error;
		break;
	}

	return ComponentStatus;
}

void ApplyAttenuation(FAtomSoundSettingsForAnimNotify* AtomSoundSetting)
{
	if (!AtomSoundSetting) {
		return;
	}
	USceneComponent* attach_to_component = AtomSoundSetting->AttachToComponent.Get();
	if (!attach_to_component
		||!attach_to_component->GetFName().IsValid()
		|| attach_to_component->GetFName().ToString().Contains("None")
		|| attach_to_component->GetFName().ToString().Contains("Property")) {
		return;
	}

	if (!AtomSoundSetting->DefaultListener) {
		return;
	}

	if (!UAtomComponent::GetDefaultAttenuationEnable()) {
		/* Attenuation設定が無効である場合は以下の設定を行わない */
		return;
	}

	USoundAttenuation* sound_attenuation = AtomSoundSetting->SoundAttenuation.Get();
	if (sound_attenuation) {
		float tmpVolume = AtomSoundSetting->Volume;

		AtomSoundSetting->Filter_Frequency = MAX_FILTER_FREQUENCY;

		AActor* Actor = attach_to_component->GetOwner();
		uint32 UniqueID = attach_to_component->GetUniqueID();
		FName Name = attach_to_component->GetFName();
		UWorld* World = attach_to_component->GetWorld();

		AtomSoundSetting->AtomActiveSound->SetAtomComponent(nullptr, 0, Name);
		AtomSoundSetting->AtomActiveSound->SetWorld(World);

		/* 距離減衰の計算 */
		/* 備考）UE4.10相当の処理を移植。 */
		const auto* Settings = &(sound_attenuation->Attenuation);
		FVector ListenerLocation = AtomSoundSetting->DefaultListener->GetListeningPoint();

		const FRotator SourceRotation = attach_to_component->GetComponentRotation();
		const FVector SourcePosition = attach_to_component->GetComponentLocation();

		/* ボリュームの初期値を計算 */
		FTransform SoundTransform = FTransform(SourceRotation, SourcePosition);

		if (Settings->bAttenuate) {
			switch (Settings->AttenuationShape) {
			case EAttenuationShape::Sphere:
			{
				const float Distance = FMath::Max(
					FVector::Dist(SoundTransform.GetTranslation(), ListenerLocation)
					- Settings->AttenuationShapeExtents.X, 0.f);
				tmpVolume *= Settings->AttenuationEval(Distance, Settings->FalloffDistance, 1.0f);
				break;
			}

			case EAttenuationShape::Box:
				tmpVolume *= Settings->AttenuationEvalBox(SoundTransform, ListenerLocation, 1.0f);
				break;

			case EAttenuationShape::Capsule:
				tmpVolume *= Settings->AttenuationEvalCapsule(SoundTransform, ListenerLocation, 1.0f);
				break;

			case EAttenuationShape::Cone:
				tmpVolume *= Settings->AttenuationEvalCone(SoundTransform, ListenerLocation, 1.0f);
				break;

			default:
				check(false);
			}
		}

		// Only do occlusion traces if the sound is audible
		if (Settings->bEnableOcclusion && tmpVolume > 0.0f /*&& !AudioDevice->IsAudioDeviceMuted()*/) {
			AtomSoundSetting->AtomActiveSound->CheckOcclusion(ListenerLocation, attach_to_component->GetComponentLocation(), Settings);
			AtomSoundSetting->Filter_Frequency = AtomSoundSetting->AtomActiveSound->CurrentOcclusionFilterFrequency.GetValue();
			// Apply the volume attenuation due to occlusion (using the interpolating dynamic parameter)

			tmpVolume *= AtomSoundSetting->AtomActiveSound->CurrentOcclusionVolumeAttenuation.GetValue();
		}

		/* ボリュームの更新 */
		criAtomExPlayer_SetVolume(AtomSoundSetting->PlayerHn, tmpVolume);

		/* LPFの適用 */
		criAtomExPlayer_SetBandpassFilterParameters(AtomSoundSetting->PlayerHn, 0.f, AtomSoundSetting->Filter_Frequency / MAX_FILTER_FREQUENCY);
	}
}

void FAtomSoundManager::TickComponentForAnimNotify()
{
	for (auto settings = FAtomSoundManager::AtomSoundSettingsForAnimNotifyMap.CreateIterator(); settings; ++settings) {
		FAtomSoundSettingsForAnimNotify* atom_sound_settings = settings.Value();

		/* プレーヤのステータスをチェック */
		CriAtomExPlayerStatus Status = criAtomExPlayer_GetStatus(atom_sound_settings->PlayerHn);
		if ((Status == CRIATOMEXPLAYER_STATUS_PREP) || (Status == CRIATOMEXPLAYER_STATUS_PLAYING)) {
			ApplyAttenuation(atom_sound_settings);
			criAtomExPlayer_UpdateAll(atom_sound_settings->PlayerHn);

#if WITH_EDITOR
			/* 距離減衰領域の表示 */
			if (GEditor && (GEditor->PlayWorld || GIsPlayInEditorWorld)) {
				/* コンソール変数 "cri.ShowAtomSoundActor" が 0 より大きいときのみ表示する。 */
				static const auto bShowSoundLoation = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("cri.ShowSoundLocation"));
				if (bShowSoundLoation->GetValueOnGameThread() > 0) {
					atom_sound_settings->DrawDebugShape();
				}
			}
#endif //WITH_EDITOR
			continue;
		}

		/* キューシートのリリース */
		USoundAtomCueSheet* CueSheet = atom_sound_settings->CueSheetPtr.Get();
		if (CueSheet != nullptr) {
			CueSheet->Release();
			CueSheet = nullptr;
		}

		/* キューシートの参照を破棄 */
		atom_sound_settings->CueSheetPtr.Reset();

		/* SoundObjectとの関連付けを解除 */
		UAtomParameterComponent* AtomParameter = atom_sound_settings->ParameterPtr.Get();
		if (AtomParameter != nullptr) {
			UAtomSoundObject* SoundObject = AtomParameter->SoundObject;
			if (SoundObject != nullptr) {
				criAtomExSoundObject_DeletePlayer(SoundObject->GetSoundObjectHandle(), atom_sound_settings->PlayerHn);
			}
		}

		/* AtomParameterの参照を破棄 */
		atom_sound_settings->ParameterPtr.Reset();

		atom_sound_settings->AttachToComponent.Reset();
		atom_sound_settings->SoundAttenuation.Reset();

#if WITH_EDITOR
		atom_sound_settings->FinalizeDebugShowInfo();
#endif

		/* サウンドが停止した要素を削除 */
		int64 atom_sound_settings_id = atom_sound_settings->AtomSoundID;
		FAtomSoundManager::AtomSoundSettingsForAnimNotifyMap.Remove(atom_sound_settings_id);

		/* リソースの破棄 */
		atom_sound_settings->Destroy();
		atom_sound_settings = nullptr;
	}

	/* Removeされた要素のためMapをShrinkする */
	FAtomSoundManager::AtomSoundSettingsForAnimNotifyMap.Shrink();
}

int32 FAtomSoundManager::PlaySoundAnimNotify(float StartTime, USceneComponent* AttachToComponent, FName AttachPointName, USoundAtomCue* Sound, bool bEnabled3DPositioning, float Volume, USoundAttenuation* SoundAttenuation)
{
	/* サウンドが指定されていない場合は何もしない */
	if (Sound == nullptr) {
		return -1;
	}

	/* デフォルトのリスナを取得 */
	FAtomListener* DefaultListener = FAtomListener::GetListener();
	if (DefaultListener == NULL) {
		/* リスナが存在しない場合は何もしない */
		return -1;
	}

	/* ここで音声再生を行うのは最後に追加された要素 */
	FAtomSoundSettingsForAnimNotify* AtomSoundSetting = FAtomSoundSettingsForAnimNotify::Create();
	if (!AtomSoundSetting) {
		return -1;
	}

	/* 距離係数の取得 */
	/* 注意）オーディオスレッドからの取得はスレッドセーフではないので、先に変数に保存しておく。 */
	AtomSoundSetting->DistanceFactor = UCriWareInitializer::GetDistanceFactor();

	/* キューシートの取得 */
	USoundAtomCueSheet* CueSheet = Sound->CueSheet;
	if (CueSheet != nullptr) {
		CueSheet->AddRef();
	}
	AtomSoundSetting->CueSheetPtr = CueSheet;

	/* AtomParameterの参照 */
	UAtomParameterComponent* AtomParameter = nullptr;
	if (Sound->bApplyAtomParameter != false) {
		/* パラメータの検索 */
		AActor *TestActor = AttachToComponent->GetOwner();
		while (TestActor) {
			/* Actorにパラメータが設定されているかどうかチェック */
			AtomParameter = Cast<UAtomParameterComponent>(
				TestActor->GetComponentByClass(UAtomParameterComponent::StaticClass()));
			if (AtomParameter != nullptr) {
				break;
			}

			TestActor = TestActor->GetOwner();
		}
	}

	/* サウンドオブジェクトの適用 */
	if (AtomParameter != nullptr) {
		UAtomSoundObject* SoundObject = AtomParameter->SoundObject;
		if (SoundObject != nullptr) {
			criAtomExSoundObject_AddPlayer(SoundObject->GetSoundObjectHandle(), AtomSoundSetting->PlayerHn);
			AtomSoundSetting->ParameterPtr = AtomParameter;
		}
	}

	/* キュー名の設定 */
	CriAtomExAcbHn AcbHn = ((CueSheet != nullptr) ? CueSheet->GetAcbHn() : nullptr);
	criAtomExPlayer_SetCueName(AtomSoundSetting->PlayerHn, AcbHn, TCHAR_TO_UTF8(*Sound->CueName));

	AtomSoundSetting->CueName = TCHAR_TO_UTF8(*Sound->CueName);
	USoundConcurrency* SoundConcurrency = Sound->SoundConcurrencySettings;
	AtomSoundSetting->SoundConcurrencyName = SoundConcurrency ? Sound->SoundConcurrencySettings->GetName() : FString("None");

	AtomSoundSetting->Volume = Volume;

	USceneComponent* scene_component = AttachToComponent;
	AtomSoundSetting->AttachToComponent = scene_component;
	 
	AtomSoundSetting->AttachPointName = AttachPointName;
	AtomSoundSetting->DefaultListener = DefaultListener;

	USoundAttenuation* sound_attenuation = SoundAttenuation;
	AtomSoundSetting->SoundAttenuation = sound_attenuation;

	/* 再生パラメータの設定*/
	criAtomExPlayer_SetVolume(AtomSoundSetting->PlayerHn, AtomSoundSetting->Volume);
	criAtomExPlayer_SetStartTime(AtomSoundSetting->PlayerHn, (CriSint32)(StartTime * 1000.0f));

	/* 音源の座標と向きを取得 */
	FVector Location;
	FRotator Rotation;
	if (AttachToComponent != nullptr) {
		if (AttachPointName != NAME_None) {
			Location = AttachToComponent->GetSocketTransform(AttachPointName).GetLocation();
		} else {
			Location = AttachToComponent->GetComponentTransform().GetLocation();
		}
		Rotation = AttachToComponent->GetComponentRotation();
	} else {
		Location = FVector::ZeroVector;
		Rotation = FRotator::ZeroRotator;
	}
	AtomSoundSetting->Location = Location;
	AtomSoundSetting->Rotation = Rotation;

	/* ソース、リスナをプレーヤに関連付け */
	criAtomExPlayer_Set3dListenerHn(AtomSoundSetting->PlayerHn, DefaultListener->GetListenerHandle());
	criAtomExPlayer_Set3dSourceHn(AtomSoundSetting->PlayerHn, AtomSoundSetting->SourceHn);

	/* 音源の位置を更新 */
	AtomSoundSetting->UpdateTransform();

	/* 2D再生かどうかチェック */
	if (bEnabled3DPositioning == false) {
		criAtomExPlayer_SetPanType(AtomSoundSetting->PlayerHn, CRIATOMEX_PAN_TYPE_PAN3D);
	}

	ApplyAttenuation(AtomSoundSetting);

	criAtomExPlayer_UpdateAll(AtomSoundSetting->PlayerHn);

	/* 再生の開始 */
	AtomSoundSetting->PlaybackId = criAtomExPlayer_Start(AtomSoundSetting->PlayerHn);

#if WITH_EDITOR
	AtomSoundSetting->InitDebugShowingInfo(Sound);
#endif //WITH_EDITOR

	/* Mapに追加 */
	AtomSoundSetting->AtomSoundID = ++FAtomSoundManager::AtomSoundID;
	FAtomSoundManager::AtomSoundSettingsForAnimNotifyMap.Add(AtomSoundSetting->AtomSoundID, AtomSoundSetting);

	/* Mapに追加されたIDを返す(AtomComponentを生成しない形での再生のため外側でIDの管理を行う) */
	return AtomSoundSetting->AtomSoundID;
}

void FAtomSoundSettingsForAnimNotify::UpdateTransform()
{
	/* 音源の位置を更新 */
	CriAtomExVector pos;
	pos.x = Location.X * DistanceFactor;
	pos.y = Location.Y * DistanceFactor;
	pos.z = Location.Z * DistanceFactor;
	criAtomEx3dSource_SetPosition(SourceHn, &pos);

	/* 音源の向きを更新 */
	FVector FrontVector = Rotation.Vector();
	CriAtomExVector front;
	front.x = FrontVector.X;
	front.y = FrontVector.Y;
	front.z = FrontVector.Z;
	criAtomEx3dSource_SetConeOrientation(SourceHn, &front);

	/* 更新の適用 */
	criAtomEx3dSource_Update(SourceHn);

	/* リスナの差し替え */
	FAtomListener* NewListener = FAtomListener::GetNearestListener(Location);
	if (NewListener != nullptr) {
		criAtomExPlayer_Set3dListenerHn(PlayerHn, NewListener->GetListenerHandle());
		criAtomExPlayer_UpdateAll(PlayerHn);
	}
};

#if WITH_EDITOR
void FAtomSoundSettingsForAnimNotify::InitDebugShowingInfo(USoundAtomCue* Sound) 
{
	FVector attach_to_component_location;

	bPlaySoundInPIE = false;
	bPlaySoundInEditor = false;

	if (bInitDebugShowingInfo == true) {
		return;
	}

	if (GIsEditor) {
		/* Editor状態で再生されたという情報を保存 */
		bPlaySoundInEditor = true;
	}

	if (GEditor && (GEditor->PlayWorld || GIsPlayInEditorWorld)) {
		/* PIE状態で再生されたという情報を保存 */
		bPlaySoundInPIE = true;
	}

	if (Sound) {
		auto MaxAttenuationDistance = Sound->GetMaxAttenuationDistance();
		max_attenuation_distance = MaxAttenuationDistance / DistanceFactor;

		auto MinAttenuationDistance = Sound->GetMinAttenuationDistance();
		min_attenuation_distance = MinAttenuationDistance / DistanceFactor;
	} else {
		max_attenuation_distance = 0.0f;
		min_attenuation_distance = 0.0f;
	}
	
	static const auto bShowSoundLoation = IConsoleManager::Get().FindTConsoleVariableDataInt(TEXT("cri.ShowSoundLocation"));
	if (bShowSoundLoation->GetValueOnGameThread() > 0) {
		/* エディターのパースペクティブビューに、スピーカーのアイコンを表示
		* インゲームでも、デバッグ表示向けにSpriteComponentを初期化しておく */
		/* SceneComponent.cpp USceneComponent::OnRegisterを参考 */
		if (SpriteComponent == nullptr) {
			USceneComponent* attach_to_component = AttachToComponent.Get();
			if (attach_to_component) {
				if (attach_to_component->GetOwner()) {
					SpriteComponent = NewObject<UBillboardComponent>(attach_to_component->GetOwner());
				}
				else {
					SpriteComponent = NewObject<UBillboardComponent>();
				}

				// Attachされたボーンの座標値を取得

				if (AttachPointName != NAME_None)
				{
					attach_to_component_location = attach_to_component->GetSocketTransform(AttachPointName).GetLocation();
				}
				else {
					attach_to_component_location = attach_to_component->GetComponentTransform().GetLocation();
				}
			}
		}

		if (SpriteComponent) {
			SpriteComponent->SetWorldLocation(attach_to_component_location);
			SpriteComponent->RelativeScale3D = FVector(0.5f, 0.5f, 0.5f);
			SpriteComponent->Mobility = EComponentMobility::Movable;
			SpriteComponent->AlwaysLoadOnClient = false;
			SpriteComponent->AlwaysLoadOnServer = false;
			SpriteComponent->SpriteInfo.Category = TEXT("Misc");
			SpriteComponent->SpriteInfo.DisplayName = NSLOCTEXT("SpriteCategory", "Misc", "Misc");
			SpriteComponent->bIsScreenSizeScaled = true;
			SpriteComponent->bUseInEditorScaling = true;
			if (SpriteComponent->GetOwner()) {
				SpriteComponent->GetOwner()->SetActorHiddenInGame(false);
			}
			SpriteComponent->SetHiddenInGame(false, true);
			SpriteComponent->RegisterComponent();

			SpriteComponent->SetSprite(LoadObject<UTexture2D>(NULL, TEXT("/Engine/EditorResources/AudioIcons/S_AudioComponent_AutoActivate.S_AudioComponent_AutoActivate")));
			bInitDebugShowingInfo = true;
		}
	}
}

void FAtomSoundSettingsForAnimNotify::FinalizeDebugShowInfo()
{
	if (bInitDebugShowingInfo == false) {
		return;
	}

	if (((GEditor && (GEditor->PlayWorld || GIsPlayInEditorWorld)) && bPlaySoundInPIE && bPlaySoundInEditor)
	|| (bPlaySoundInEditor && !bPlaySoundInPIE)) {
		if (SpriteComponent) {
			if (SpriteComponent->GetFName().IsValid()) {
				if (SpriteComponent->GetFName().ToString().Contains("BillboardComponent")
					&& !SpriteComponent->IsBeingDestroyed()) {
					SpriteComponent->DestroyComponent();
				}
				SpriteComponent = nullptr;
			}
		}
		bInitDebugShowingInfo = false;
	}
}

void FAtomSoundSettingsForAnimNotify::DrawDebugShape()
{
	if (bInitDebugShowingInfo == false) {
		return;
	}

	UWorld* World = (GEditor ? (GEditor->PlayWorld) : nullptr);
	class ULocalPlayer* LocalPlayer = (GEngine ? (GEngine->GetDebugLocalPlayer()) : nullptr);
	if (LocalPlayer) {
		UWorld* PlayerWorld = LocalPlayer->GetWorld();
		if (!World) {
			World = PlayerWorld;
		}
	}
	if (!World) {
		return;
	}

	if (!SpriteComponent) {
		return;
	}

	if (!SpriteComponent->GetFName().IsValid()) {
		return;
	}

	if (!SpriteComponent->GetFName().ToString().Contains("BillboardComponent")) {
		return;
	}

	const FRotator SourceRot = SpriteComponent->GetComponentRotation();
	const FVector SourceVec = SpriteComponent->GetComponentLocation();
	const FTransform SourceTrsf = FTransform(SourceRot, SourceVec);

	DrawDebugSphere(World, SourceTrsf.GetTranslation(), max_attenuation_distance, 10, FColor(255, 0, 0));
	DrawDebugSphere(World, SourceTrsf.GetTranslation(), min_attenuation_distance, 10, FColor(155, 0, 0));
}
#endif //WITH_EDITOR

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/
#undef LOCTEXT_NAMESPACE
