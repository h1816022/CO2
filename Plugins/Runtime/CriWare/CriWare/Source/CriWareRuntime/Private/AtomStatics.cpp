/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2014-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Atom Statics
 * File     : AtomStatics.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "AtomStatics.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareRuntimePrivatePCH.h"
#include "CriWareInitializer.h"
#include "AtomSoundManager.h"
#include "AtomDisposer.h"

/* Unreal Engine 4関連ヘッダ */
#include "UObject/Package.h"
#include "GameFramework/WorldSettings.h"
#include "Containers/Map.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "AtomStatics"

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

/***************************************************************************
 *      クラス定義
 *      Class Definition
 ***************************************************************************/
UAtomStatics::UAtomStatics()
{
#if WITH_EDITOR
	/* Localization of unreal properties metadata with LOCTEXT markups and reflection */
	CRI_LOCCLASS(GetClass());
#endif
}

void UAtomStatics::PlaySoundAtLocation(UObject* WorldContextObject, class USoundAtomCue* Sound, FVector Location, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation* AttenuationSettings, class USoundConcurrency* ConcurrencySettings)
{
	SpawnSoundAtLocation(WorldContextObject, Sound, Location, FRotator::ZeroRotator, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings);
}

void UAtomStatics::PlaySoundAtLocation(UObject* WorldContextObject, class USoundAtomCue* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation* AttenuationSettings, class USoundConcurrency* ConcurrencySettings)
{
	SpawnSoundAtLocation(WorldContextObject, Sound, Location, Rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings);
}

UAtomComponent* UAtomStatics::SpawnSound2D(const UObject* WorldContextObject, USoundAtomCue* Sound, float PitchMultiplier, float StartTime, bool bPersistAcrossLevelTransition, bool bAutoDestroy)
{
	if (!Sound || !GEngine || !GEngine->UseSound()) {
		return nullptr;
	}

	/* 音声再生の可否をチェック */
	UWorld* ThisWorld = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!ThisWorld || !ThisWorld->bAllowAudioPlayback || ThisWorld->GetNetMode() == NM_DedicatedServer) {
		return nullptr;
	}

	const bool bIsInGameWorld = ThisWorld->IsGameWorld();
	AWorldSettings *WorldSettings = ThisWorld->GetWorldSettings();

	UAtomComponent* AtomComponent;
	if (WorldSettings) {
		if (!bPersistAcrossLevelTransition) {
			AtomComponent = NewObject<UAtomComponent>(WorldSettings);
		} else {
			AtomComponent = NewObject<UAtomComponent>();
			AtomComponent->MarkAsRooted();
		}
	} else {
		AtomComponent = NewObject<UAtomComponent>();
		if (bPersistAcrossLevelTransition) {
			AtomComponent->MarkAsRooted();
		}
	}

	if (AtomComponent)
	{
		AtomComponent->SetPitchMultiplier(PitchMultiplier);
		AtomComponent->bIsUISound = true;
		AtomComponent->bAutoDestroy = bAutoDestroy;
		AtomComponent->bAllowAnyoneToDestroyMe = true;
		AtomComponent->SetSound(Sound);

		if (!bPersistAcrossLevelTransition) {
			/* 再生終了検知のためRegisterComponentを実行 */
			/* 注意）シーク再生をリクエスト済みなので、Auto ActivateはOFFに設定。   */
			/* 　　　→Activate時の再生でシーク再生がキャンセルされるのを防止。     */
			AtomComponent->bAutoActivate = false;
			AtomComponent->RegisterComponent();
		}

		AtomComponent->Play(StartTime);
	}

	return AtomComponent;
}

UAtomComponent* UAtomStatics::CreateRootedAtomComponent(const UObject* WorldContextObject, bool bAutoDestroy)
{
	if (!GEngine || !GEngine->UseSound()) {
		return nullptr;
	}

	UWorld* ThisWorld = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!ThisWorld || !ThisWorld->bAllowAudioPlayback || ThisWorld->GetNetMode() == NM_DedicatedServer) {
		return nullptr;
	}

	const bool bIsInGameWorld = ThisWorld->IsGameWorld();
	AWorldSettings *WorldSettings = ThisWorld->GetWorldSettings();

	UAtomComponent* AtomComponent;
	AtomComponent = NewObject<UAtomComponent>();
	AtomComponent->MarkAsRooted();

	if (AtomComponent)
	{
		AtomComponent->bIsUISound = true;
		AtomComponent->bAutoDestroy = bAutoDestroy;
		AtomComponent->bAllowAnyoneToDestroyMe = true;
	}
	return AtomComponent;
}

UAtomComponent* UAtomStatics::SpawnSoundAtLocation(const UObject* WorldContextObject, class USoundAtomCue* Sound, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation* AttenuationSettings, class USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	if (!GEngine) {
		return nullptr;
	}

	/* 備考）Soundがnullptrの場合はAtomComponentの作成のみを行う。 */

	/* 音声再生の可否をチェック */
	UWorld* ThisWorld = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!ThisWorld || !ThisWorld->bAllowAudioPlayback || ThisWorld->GetNetMode() == NM_DedicatedServer) {
		return nullptr;
	}

	const bool bIsInGameWorld = ThisWorld->IsGameWorld();
	AWorldSettings *WorldSettings = ThisWorld->GetWorldSettings();

	USoundAttenuation* SoundAttenuation = AttenuationSettings;
	if ((SoundAttenuation == nullptr) && (Sound != nullptr)) {
		SoundAttenuation = Sound->DefaultAttenuation;
	}

	/* 音声再生用にAtomComponentを確保 */
	UAtomComponent* AtomComponent;
	if (WorldSettings) {
		AtomComponent = NewObject<UAtomComponent>(WorldSettings);
	} else {
		AtomComponent = NewObject<UAtomComponent>();
	}
	if (AtomComponent != NULL) {
		AtomComponent->SetWorldLocationAndRotation(Location, Rotation);
		AtomComponent->DefaultVolume = VolumeMultiplier;
		AtomComponent->AttenuationSettings = SoundAttenuation;
		AtomComponent->bAutoDestroy = bAutoDestroy;
		AtomComponent->bAllowAnyoneToDestroyMe = true;
		AtomComponent->bIsUISound = !bIsInGameWorld;

		/* 音声データの指定 */
		if (Sound != nullptr) {
			AtomComponent->SetSound(Sound);
		}

		/* 再生終了検知のためRegisterComponentを実行 */
		/* 注意）シーク再生をリクエスト済みなので、Auto ActivateはOFFに設定。   */
		/* 　　　→Activate時の再生でシーク再生がキャンセルされるのを防止。     */
		AtomComponent->bAutoActivate = false;
		AtomComponent->RegisterComponent();

		/* 再生の開始 */
		if (Sound != nullptr) {
			AtomComponent->Play(StartTime);
		}
	}

	return AtomComponent;
}

UAtomComponent* UAtomStatics::SpawnSoundAtLocation(const UObject* WorldContextObject, class USoundAtomCueSheet* CueSheet, FString CueName, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation* AttenuationSettings, class USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	if (!GEngine) {
		return nullptr;
	}

	/* 備考）CueNameがEmptyの場合はAtomComponentの作成のみを行う。 */

	/* 音声再生の可否をチェック */
	UWorld* ThisWorld = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!ThisWorld || !ThisWorld->bAllowAudioPlayback || ThisWorld->GetNetMode() == NM_DedicatedServer) {
		return nullptr;
	}

	const bool bIsInGameWorld = ThisWorld->IsGameWorld();
	AWorldSettings *WorldSettings = ThisWorld->GetWorldSettings();

	/* 音声再生用にAtomComponentを確保 */
	UAtomComponent* AtomComponent;
	if (WorldSettings) {
		AtomComponent = NewObject<UAtomComponent>(WorldSettings);
	} else {
		AtomComponent = NewObject<UAtomComponent>();
	}
	if (AtomComponent != NULL) {
		AtomComponent->SetWorldLocationAndRotation(Location, Rotation);
		AtomComponent->DefaultVolume = VolumeMultiplier;
		AtomComponent->AttenuationSettings = AttenuationSettings;
		AtomComponent->bAutoDestroy = bAutoDestroy;
		AtomComponent->bAllowAnyoneToDestroyMe = true;
		AtomComponent->bIsUISound = !bIsInGameWorld;

		/* 音声データの指定 */
		if (!CueName.IsEmpty()) {
			AtomComponent->SetSound(CueSheet, CueName);
		}

		/* 再生終了検知のためRegisterComponentを実行 */
		/* 注意）シーク再生をリクエスト済みなので、Auto ActivateはOFFに設定。   */
		/* 　　　→Activate時の再生でシーク再生がキャンセルされるのを防止。     */
		AtomComponent->bAutoActivate = false;
		AtomComponent->RegisterComponent();

		/* 再生の開始 */
		if (!CueName.IsEmpty()) {
			AtomComponent->Play(StartTime);
		}
	}

	return AtomComponent;
}

class UAtomComponent* UAtomStatics::SpawnSoundAttached(class USoundAtomCue* Sound, class USceneComponent* AttachToComponent, FName AttachPointName, FVector Location, FRotator Rotation, EAttachLocation::Type LocationType, bool bStopWhenAttachedToDestroyed, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation* AttenuationSettings, class USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	/* サウンド未指定時は何もしない */
	if (Sound == nullptr) {
		return nullptr;
	}

	/* アタッチ先の有無をチェック */
	if (AttachToComponent == NULL) {
		UE_LOG(LogCriWareRuntime, Warning, TEXT("UAtomStatics::SpawnSoundAttached: NULL AttachComponent specified!"));
		return NULL;
	}

	/* 音声再生の可否をチェック */
	/* 備考）Personaアセットブラウザ等での再生をブロック。 */
	UWorld* ThisWorld = AttachToComponent->GetWorld();
	if (ThisWorld->bAllowAudioPlayback == false) {
		return NULL;
	}

	USoundAttenuation* SoundAttenuation = (AttenuationSettings == NULL) ? Sound->DefaultAttenuation : AttenuationSettings;

	/* 音声再生用にAtomComponentを確保 */
	UAtomComponent* AtomComponent = NULL;
	if (AttachToComponent->GetOwner() == NULL) {
		AtomComponent = NewObject<UAtomComponent>();
	} else {
		AtomComponent = NewObject<UAtomComponent>(AttachToComponent->GetOwner());
	}

	if (AtomComponent) {
		const bool bIsInGameWorld = AtomComponent->GetWorld()->IsGameWorld();

		AtomComponent->AttachToComponent(AttachToComponent, FAttachmentTransformRules::KeepRelativeTransform, AttachPointName);
		if (LocationType == EAttachLocation::KeepWorldPosition) {
			AtomComponent->SetWorldLocationAndRotation(Location, Rotation);
		} else {
			AtomComponent->SetRelativeLocationAndRotation(Location, Rotation);
		}

		AtomComponent->DefaultVolume = VolumeMultiplier;
		AtomComponent->AttenuationSettings = SoundAttenuation;
		AtomComponent->bStopWhenOwnerDestroyed = bStopWhenAttachedToDestroyed;
		AtomComponent->bAutoDestroy = bAutoDestroy;
		AtomComponent->bAllowAnyoneToDestroyMe = true;
		AtomComponent->bIsUISound = !bIsInGameWorld;
		AtomComponent->SetSound(Sound);

		/* 再生終了検知のためRegisterComponentを実行 */
		/* 注意）シーク再生をリクエスト済みなので、Auto ActivateはOFFに設定。   */
		/* 　　　→Activate時の再生でシーク再生がキャンセルされるのを防止。     */
		AtomComponent->bAutoActivate = false;
		AtomComponent->RegisterComponentWithWorld(AttachToComponent->GetWorld());

		AtomComponent->Play(StartTime);
	}

	return AtomComponent;
}

UAtomComponent* UAtomStatics::SpawnSoundAttached(USoundAtomCueSheet* CueSheet, FString CueName, USceneComponent* AttachToComponent, FName AttachPointName, FVector Location, FRotator Rotation, EAttachLocation::Type LocationType, bool bStopWhenAttachedToDestroyed, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundAttenuation* AttenuationSettings, USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	/* アタッチ先の有無をチェック */
	if (AttachToComponent == NULL) {
		UE_LOG(LogCriWareRuntime, Warning, TEXT("UAtomStatics::SpawnSoundAttached: NULL AttachComponent specified!"));
		return NULL;
	}

	/* 音声再生の可否をチェック */
	/* 備考）Personaアセットブラウザ等での再生をブロック。 */
	UWorld* ThisWorld = AttachToComponent->GetWorld();
	if (ThisWorld->bAllowAudioPlayback == false) {
		return NULL;
	}

	/* 音声再生用にAtomComponentを確保 */
	UAtomComponent* AtomComponent = NULL;
	if (AttachToComponent->GetOwner() == NULL) {
		AtomComponent = NewObject<UAtomComponent>();
	} else {
		AtomComponent = NewObject<UAtomComponent>(AttachToComponent->GetOwner());
	}

	if(AtomComponent) {
		const bool bIsInGameWorld = AtomComponent->GetWorld()->IsGameWorld();

		AtomComponent->AttachToComponent(AttachToComponent, FAttachmentTransformRules::KeepRelativeTransform, AttachPointName);
		if (LocationType == EAttachLocation::KeepWorldPosition) {
			AtomComponent->SetWorldLocationAndRotation(Location, Rotation);
		} else {
			AtomComponent->SetRelativeLocationAndRotation(Location, Rotation);
		}

		AtomComponent->DefaultVolume = VolumeMultiplier;
		AtomComponent->AttenuationSettings = AttenuationSettings;
		AtomComponent->bStopWhenOwnerDestroyed = bStopWhenAttachedToDestroyed;
		AtomComponent->bAutoDestroy = bAutoDestroy;
		AtomComponent->bAllowAnyoneToDestroyMe = true;
		AtomComponent->bIsUISound = !bIsInGameWorld;
		AtomComponent->SetSound(CueSheet, CueName);

		/* 再生終了検知のためRegisterComponentを実行 */
		/* 注意）シーク再生をリクエスト済みなので、Auto ActivateはOFFに設定。   */
		/* 　　　→Activate時の再生でシーク再生がキャンセルされるのを防止。     */
		AtomComponent->bAutoActivate = false;
		AtomComponent->RegisterComponentWithWorld(AttachToComponent->GetWorld());

		AtomComponent->Play(StartTime);
	}

	return AtomComponent;
}

UAtomComponent* UAtomStatics::SpawnSoundAttached(class USoundAtomCue* Sound, class USceneComponent* AttachToComponent, FName AttachPointName, FVector Location, EAttachLocation::Type LocationType, bool bStopWhenAttachedToDestroyed, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation* AttenuationSettings, class USoundConcurrency* ConcurrencySettings, bool bAutoDestroy)
{
	return SpawnSoundAttached(Sound, AttachToComponent, AttachPointName, Location,  FRotator::ZeroRotator, LocationType, bStopWhenAttachedToDestroyed, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings, bAutoDestroy);
}

UAtomComponent* UAtomStatics::PlaySoundAttached(USoundAtomCue* Sound, USceneComponent* AttachToComponent, FName AttachPointName, FVector Location, bool bStopWhenAttachedToDestroyed, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation* AttenuationSettings)
{
	/* Sound未指定時はnullptrを返す */
	if (Sound == nullptr) {
		return nullptr;
	}

	/* アタッチ先の有無をチェック */
	if (AttachToComponent == NULL) {
		UE_LOG(LogCriWareRuntime, Warning, TEXT("UAtomStatics::SpawnSoundAttached: NULL AttachComponent specified!"));
		return NULL;
	}

	/* 音声再生の可否をチェック */
	/* 備考）Personaアセットブラウザ等での再生をブロック。 */
	UWorld* ThisWorld = AttachToComponent->GetWorld();
	if (ThisWorld->bAllowAudioPlayback == false) {
		return NULL;
	}

	/* 音声再生用にAtomComponentを確保 */
	UAtomComponent* AtomComponent = NULL;
	if (AttachToComponent->GetOwner() == NULL) {
		AtomComponent = NewObject<UAtomComponent>();
	} else {
		AtomComponent = NewObject<UAtomComponent>(AttachToComponent->GetOwner());
	}

	// Attachされたボーンの座標値を取得
	FVector TestLocation = Location;
	if (AttachPointName != NAME_None)
	{
		TestLocation = AttachToComponent->GetSocketTransform(AttachPointName).GetLocation();
	} else {
		TestLocation = AttachToComponent->GetComponentTransform().GetLocation();
	}

	if (AtomComponent) {
		const bool bIsInGameWorld = AtomComponent->GetWorld()->IsGameWorld();

		AtomComponent->SetWorldLocation(TestLocation);
		AtomComponent->DefaultVolume = VolumeMultiplier;
		AtomComponent->AttenuationSettings = AttenuationSettings ? AttenuationSettings : Sound->DefaultAttenuation;
		AtomComponent->bStopWhenOwnerDestroyed = bStopWhenAttachedToDestroyed;
		AtomComponent->bAutoDestroy = true;
		AtomComponent->bAllowAnyoneToDestroyMe = true;
		AtomComponent->bIsUISound = !bIsInGameWorld;
		AtomComponent->SetSound(Sound);

		/* 再生終了検知のためRegisterComponentを実行 */
		/* 注意）シーク再生をリクエスト済みなので、Auto ActivateはOFFに設定。   */
		/* 　　　→Activate時の再生でシーク再生がキャンセルされるのを防止。     */
		AtomComponent->bAutoActivate = false;
		AtomComponent->RegisterComponent();

		AtomComponent->Play(StartTime);
	}

	return AtomComponent;
}

void UAtomStatics::PlaySoundForAnimNotify(USoundAtomCue* Sound, USceneComponent* AttachToComponent, FName AttachPointName, FVector Location, bool bStopWhenAttachedToDestroyed, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation* AttenuationSettings)
{
	/* Sound未指定時はnullptrを返す */
	if (Sound == nullptr) {
		return;
	}

	/* アタッチ先の有無をチェック */
	if (AttachToComponent == NULL) {
		UE_LOG(LogCriWareRuntime, Warning, TEXT("UAtomStatics::SpawnSoundAttached: NULL AttachComponent specified!"));
		return;
	}

	/* 音声再生の可否をチェック */
	/* 備考）Personaアセットブラウザ等での再生をブロック。 */
	UWorld* ThisWorld = AttachToComponent->GetWorld();
	if (ThisWorld->bAllowAudioPlayback == false) {
		return;
	}

	if (Sound->GetLength() == -1) {
		/* ループ音の場合はコンポーネントを作成 */
		SpawnSoundAttached(Sound, AttachToComponent, AttachPointName, Location, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, bStopWhenAttachedToDestroyed, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, nullptr, true);
	} else {
		/* 3Dポジショニングを行うかどうかの判定 */
		bool bEnabled3DPositioning = true;
#if WITH_EDITOR
		const bool bIsInGameWorld = ThisWorld->IsGameWorld();
		bEnabled3DPositioning = bIsInGameWorld;
#endif

		/* ループ音でない場合はコンポーネントを作成しない */
		FAtomSoundManager::PlaySoundAnimNotify(StartTime, AttachToComponent, AttachPointName, Sound, bEnabled3DPositioning, VolumeMultiplier,
			AttenuationSettings ? AttenuationSettings : Sound->DefaultAttenuation);
	}
}

void UAtomStatics::PauseAudioOutput(bool bPause)
{
	if (bPause != false) {
		/* ポーズ */
		criAtomExAsr_PauseOutputVoice(CRI_TRUE);
		criAtomEx_PauseTimer(CRI_TRUE);

		/* レベル遷移時やプレビュー終了時にポーズ解除するアクタを作成 */
		AAtomDisposer* ExistingActor = (AAtomDisposer*)StaticFindObject(
			AAtomDisposer::StaticClass(), ANY_PACKAGE, TEXT("UAtomStatics_PauseAudioOutput"));
		if (ExistingActor == NULL) {
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.Name = *FString::Printf(TEXT("UAtomStatics_PauseAudioOutput"));
			AAtomDisposer* NewActor = GWorld->SpawnActor<AAtomDisposer>(SpawnInfo);
			NewActor->SetEndPlayCallback(UAtomStatics::ResumeAudioOutput, nullptr);
		}
	} else {
		/* ポーズ解除 */
		UAtomStatics::ResumeAudioOutput(nullptr);
	}
}

void UAtomStatics::ResumeAudioOutput(void* Object)
{
	/* ポーズ解除 */
	criAtomExAsr_PauseOutputVoice(CRI_FALSE);
	criAtomEx_PauseTimer(CRI_FALSE);
}

void UAtomStatics::StopAllSounds()
{
	/* 全てのAtomExプレーヤを停止 */
	criAtomExPlayer_StopAllPlayers();
}

bool UAtomStatics::LoadAtomConfig(USoundAtomConfig* AcfObject)
{
	/* ACFデータの解放 */
	if (UCriWareInitializer::AcfData != nullptr) {
		UE_LOG(LogCriWareRuntime, Log, TEXT("Atom Config is unloaded."));
		criAtomEx_UnregisterAcf();
		FMemory::Free(UCriWareInitializer::AcfData);
		UCriWareInitializer::AcfData = nullptr;
	}

	/* ACFアセットの参照をクリア */
	UCriWareInitializer::AcfAssetReference.Reset();

	if (AcfObject != nullptr) {
		int32 AcfDataSize = AcfObject->RawData.GetBulkDataSize();
		AcfObject->RawData.GetCopy((void**)&UCriWareInitializer::AcfData, false);
		if (UCriWareInitializer::AcfData == nullptr) {
			UE_LOG(LogCriWareRuntime, Error, TEXT("Failed to load '%s'."), *AcfObject->GetName());
			return false;
		} else {
			/* ACFデータのロード */
			criAtomEx_RegisterAcfData(UCriWareInitializer::AcfData, AcfDataSize, NULL, 0);

			/* ACFアセットの参照の更新 */
			UCriWareInitializer::AcfAssetReference = FSoftObjectPath(AcfObject);
			return true;
		}
	}
	return false;
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/
#undef LOCTEXT_NAMESPACE

/* --- end of file --- */
