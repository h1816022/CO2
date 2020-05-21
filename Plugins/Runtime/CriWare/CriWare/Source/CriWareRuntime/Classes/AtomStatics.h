/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2014-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Atom Statics
 * File     : AtomStatics.h
 *
 ****************************************************************************/

/* 多重定義防止 */
#pragma once

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* Unreal Engine 4関連ヘッダ */
#include "Kismet/BlueprintFunctionLibrary.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareApi.h"
#include "SoundAtomCue.h"
#include "AtomComponent.h"
#include "SoundAtomConfig.h"

/* モジュールヘッダ */
#include "AtomStatics.generated.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/

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
UCLASS(meta=(ToolTip = "AtomComponent class."))
class CRIWARERUNTIME_API UAtomStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UAtomStatics();

	/**
	 * 指定された位置に音源を配置し、キューを再生します。
	 * ループ音を再生すると停止できないため、ワンショット音にのみ使用してください。
	 * ループ音の再生には SpawnSoundAtLocation 関数を使用してください。
	 * 本関数で配置した音源はどのActorにも追従しません。
	 * 各引数の意味はUGamePlayStatics::SpawnSoundAtLocation関数に従います。
	 */
	UFUNCTION(BlueprintCallable, Category="Atom", meta=(WorldContext="WorldContextObject", AdvancedDisplay = "3", UnsafeDuringActorConstruction = "true", ToolTip = "Play sound at location."))
	static void PlaySoundAtLocation(UObject* WorldContextObject, class USoundAtomCue* Sound, FVector Location, FRotator Rotation = FRotator::ZeroRotator, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = NULL, class USoundConcurrency* ConcurrencySettings = nullptr);

	/** PlaySoundAtLocation関数からRotator引数を省いたバージョン。 */
	static void PlaySoundAtLocation(UObject* WorldContextObject, class USoundAtomCue* Sound, FVector Location, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = NULL, class USoundConcurrency* ConcurrencySettings = nullptr);

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Atom", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "2", UnsafeDuringActorConstruction = "true", Keywords = "Play"))
	static class UAtomComponent* SpawnSound2D(const UObject* WorldContextObject, USoundAtomCue* Sound, float PitchMultiplier = 1.f, float StartTime = 0.f, bool bPersistAcrossLevelTransition = false, bool bAutoDestroy = true);

	/* Root化されたAtomComponentを作成 */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Atom", meta = (WorldContext = "WorldContextObject", AdvancedDisplay = "2", UnsafeDuringActorConstruction = "true", Keywords = "Create", ToolTip = "Create rooted atom component."))
	static class UAtomComponent* CreateRootedAtomComponent(const UObject* WorldContextObject, bool bAutoDestroy = true);

	/**
	 * 指定された位置に音源を配置し、キューを再生します。
	 * 本関数で配置した音源はどのActorにも追従しません。
	 * 各引数の意味はUGamePlayStatics::SpawnSoundAtLocation関数に従います。
	 */
	UFUNCTION(BlueprintCallable, Category="Atom", meta=(WorldContext="WorldContextObject", AdvancedDisplay = "3", UnsafeDuringActorConstruction = "true", Keywords = "play", ToolTip = "Spawn sound at location."))
	static class UAtomComponent* SpawnSoundAtLocation(const UObject* WorldContextObject, class USoundAtomCue* Sound, FVector Location, FRotator Rotation = FRotator::ZeroRotator, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = NULL, class USoundConcurrency* ConcurrencySettings = nullptr, bool bAutoDestroy = true);

	/**
	 * 指定されたコンポーネントに追従する音源を配置し、キューを再生します。
	 * 各引数の意味はUGamePlayStatics::SpawnSoundAttached関数に従います。
	 * 引数 ConcurrencySettings は利用できません（内部で無視されます）
	 */
	UFUNCTION(BlueprintCallable, Category="Atom", meta=(AdvancedDisplay = "2", UnsafeDuringActorConstruction = "true", ToolTip = "Spawn sound attached."))
	static class UAtomComponent* SpawnSoundAttached(class USoundAtomCue* Sound, class USceneComponent* AttachToComponent, FName AttachPointName = NAME_None, FVector Location = FVector(ForceInit), FRotator Rotation = FRotator::ZeroRotator, EAttachLocation::Type LocationType = EAttachLocation::KeepRelativeOffset, bool bStopWhenAttachedToDestroyed = false, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = NULL, class USoundConcurrency* ConcurrencySettings = nullptr, bool bAutoDestroy = true);

	/** SpawnSoundAttached関数からRotator引数を省いたバージョン。 */
	static class UAtomComponent* SpawnSoundAttached(class USoundAtomCue* Sound, class USceneComponent* AttachToComponent, FName AttachPointName = NAME_None, FVector Location = FVector(ForceInit), EAttachLocation::Type LocationType = EAttachLocation::KeepRelativeOffset, bool bStopWhenAttachedToDestroyed = false, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = NULL, class USoundConcurrency* ConcurrencySettings = nullptr, bool bAutoDestroy = true);

	/**
	 * 指定されたコンポーネントに追従する音源を配置し、キューを再生します。
	 * 各引数の意味はUGamePlayStatics::SpawnSoundAttached関数に従います。
	 * ※本関数は将来のバージョンで削除される予定です。SpawnSoundAttached関数へ移行をお願いいたします。
	 */
	UFUNCTION(BlueprintCallable, Category="Atom", meta=(AdvancedDisplay = "2", UnsafeDuringActorConstruction = "true", ToolTip = "Play sound attached."))
	static class UAtomComponent* PlaySoundAttached(class USoundAtomCue* Sound, class USceneComponent* AttachToComponent, FName AttachPointName = NAME_None, FVector Location = FVector(ForceInit), bool bStopWhenAttachedToDestroyed = false, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = NULL);

	UFUNCTION(BlueprintCallable, Category = "Atom", meta = (AdvancedDisplay = "2", UnsafeDuringActorConstruction = "true", ToolTip = "Play sound attached."))
	static void PlaySoundForAnimNotify(class USoundAtomCue* Sound, class USceneComponent* AttachToComponent, FName AttachPointName = NAME_None, FVector Location = FVector(ForceInit), bool bStopWhenAttachedToDestroyed = false, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = NULL);

	UFUNCTION(BlueprintCallable, Category="Atom", meta=(ToolTip = "Pause audio output."))
	static void PauseAudioOutput(bool bPause);

	UFUNCTION(BlueprintCallable, Category="Atom", meta=(ToolTip = "Stop all sounds."))
	static void StopAllSounds();

	/* ACF差し替え用関数 */
	UFUNCTION(BlueprintCallable, Category = "Atom", meta = (UnsafeDuringActorConstruction = "true", ToolTip = "Reload ACF."))
	static bool LoadAtomConfig(USoundAtomConfig* AcfObject);

	/* C++ API */
	static UAtomComponent* SpawnSoundAtLocation(const UObject* WorldContextObject, USoundAtomCueSheet* CueSheet, FString CueName, FVector Location, FRotator Rotation = FRotator::ZeroRotator, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = NULL, class USoundConcurrency* ConcurrencySettings = nullptr, bool bAutoDestroy = true);
	static UAtomComponent* SpawnSoundAttached(USoundAtomCueSheet* CueSheet, FString CueName, USceneComponent* AttachToComponent, FName AttachPointName = NAME_None, FVector Location = FVector(ForceInit), FRotator Rotation = FRotator::ZeroRotator, EAttachLocation::Type LocationType = EAttachLocation::KeepRelativeOffset, bool bStopWhenAttachedToDestroyed = false, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, USoundAttenuation* AttenuationSettings = nullptr, USoundConcurrency* ConcurrencySettings = nullptr, bool bAutoDestroy = true);

private:
	static void ResumeAudioOutput(void* Object);
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
