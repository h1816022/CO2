/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : AudioComponent for Atom
 * File     : AtomComponent.h
 *
 ****************************************************************************/

/* 多重定義防止 */
#pragma once

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* Unreal Engine 4関連ヘッダ */
#include "Components/SceneComponent.h"
#include "Sound/SoundAttenuation.h"

#if WITH_EDITORONLY_DATA
#include "Runtime/Engine/Classes/Components/BillboardComponent.h"
#include "Runtime/Engine/Classes/Components/DrawSphereComponent.h"
#endif

/* CRIWAREプラグインヘッダ */
#include "SoundAtomCueSheet.h"
#include "SoundAtomCue.h"
#include "AtomSoundObject.h"
#include "AtomActiveSound.h"
#include "AtomPlaylist.h"

/* モジュールヘッダ */
#include "AtomComponent.generated.h"

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
UENUM(BlueprintType)
enum class EAtomComponentStatus : uint8
{
	Stop,				/** 停止中 */
	Prep,				/** 再生準備中 */
	Playing,			/** 再生中 */
	PlayEnd,			/** 再生終了 */
	Error				/** エラー */
};

class FAtomListener;
struct FAtomActiveSound;

/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      クラス宣言
 *      Prototype Classes
 ***************************************************************************/
/* AISACコントロールパラメータ */
USTRUCT(BlueprintType, meta = (ToolTip = "AtomAisacControlParam struct."))
struct FAtomAisacControlParam
{
	GENERATED_USTRUCT_BODY()

	FAtomAisacControlParam();

	/* AISACコントロール名 */
	UPROPERTY(EditAnywhere, Category = "Aisac", meta = (ToolTip = "Name."))
	FString Name;

	/* AISACコントロール値 */
	UPROPERTY(EditAnywhere, Category = "Aisac", meta = (ToolTip = "Value.", ClampMin = "0.0", ClampMax = "1.0"))
	float Value;
};

/* セレクタパラメータ */
USTRUCT(BlueprintType, meta = (ToolTip = "AtomAisacControlParam struct."))
struct FAtomSelectorParam
{
	GENERATED_USTRUCT_BODY()

	FAtomSelectorParam();

	/* セレクタ名 */
	UPROPERTY(EditAnywhere, Category = "Selector", meta = (ToolTip = "Name."))
	FString Selector;

	/* ラベル名 */
	UPROPERTY(EditAnywhere, Category = "Selector", meta = (ToolTip = "Name."))
	FString Label;
};

UCLASS(ClassGroup = (CRIWARE, Common),
	hidecategories = (Object, ActorComponent, Physics, Rendering, Mobility, LOD),
	ShowCategories = Trigger,
	meta = (BlueprintSpawnableComponent, ToolTip = "AtomComponent class.")
)
class CRIWARERUNTIME_API UAtomComponent : public USceneComponent
{
	GENERATED_UCLASS_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAudioFinished);
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAudioFinishedNative, class UAtomComponent*);

	/* 音声データ */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (ToolTip = "Sound data."))
	class USoundAtomCue* Sound;

	/* 再生完了と同時にコンポーネントを破棄するかどうか */
	UPROPERTY(meta = (ToolTip = "Auto destroy."))
	uint32 bAutoDestroy : 1;

	/* パーシスタントレベルをまたいで音声を再生するかどうか */
	UPROPERTY(meta = (ToolTip = "Is PersistAcrossLevelTransitionSound?."))
	bool bPersistAcrossLevelTransition;

	/* パーシスタントレベルをまたいで音声を再生するかどうか */
	bool bAddedAtomNonRegisteredComponentArray;

	/* オーナー破棄時に音声を停止するかどうか */
	UPROPERTY(meta = (ToolTip = "Stop when owner destroyed."))
	uint32 bStopWhenOwnerDestroyed : 1;

	/* ゲーム中でなくても、PersonaなどのUI向けに再生するかどうか */
	UPROPERTY(meta = (ToolTip = "Is UI sound?"))
	uint32 bIsUISound : 1;

	/* プレビューのみに使用する音声かどうか */
	bool bIsPreviewSound;

	/* デフォルトのボリューム値 */
	UPROPERTY(EditAnywhere, Category = "Sound", meta = (DisplayName = "Volume Multiplier", ToolTip = "Volume multiplier.", ClampMin = "0.0", ClampMax = "1.0"))
	float DefaultVolume;

	/* １つのコンポーネントで複数の音を同時に再生可能かどうか */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atom", meta = (ToolTip = "Enable multiple sound playback."))
	bool bEnableMultipleSoundPlayback;

	/* シームレス連結再生を使用するかどうか */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atom", meta = (ToolTip = "Use playlist."))
	bool bUsePlaylist;

	/* SoundObject */
	UPROPERTY(EditAnywhere, Category = "Atom", meta = (DisplayName = "Sound Object", ToolTip = "Sound object."))
	class UAtomSoundObject* DefaultSoundObject;

	/* デフォルトのブロックインデックス */
	UPROPERTY(EditAnywhere, Category = "Atom", meta = (DisplayName = "Block Index", ToolTip = "Initial block index.", ClampMin = "0"))
	int32 DefaultBlockIndex;

	/* デフォルトのAISAC設定 */
	UPROPERTY(EditAnywhere, Category = "Atom", meta = (DisplayName = "AISAC Control", ToolTip = "Initial AISAC control."))
	TArray<struct FAtomAisacControlParam> DefaultAisacControl;

	/* デフォルトのセレクタラベル設定 */
	UPROPERTY(EditAnywhere, Category = "Atom", meta = (DisplayName = "Selector Label", ToolTip = "Initial selector label."))
	TArray<struct FAtomSelectorParam> DefaultSelectorLabel;

	/** called when we finish playing audio, either because it played to completion or because a Stop() call turned it off early */
	UPROPERTY(BlueprintAssignable)
	FOnAudioFinished OnAudioFinished;

	/** A pointer to a UWorld that is the duplicated/saved-loaded to be played in with "Play From Here" 								*/
	UPROPERTY()
	class UWorld* PlayWorld;

	/** The view port representing the current game instance. Can be 0 so don't use without checking. */
	UPROPERTY()
	class UGameViewportClient* GameViewport;

	/** shadow delegate for non UObject subscribers */
	FOnAudioFinishedNative OnAudioFinishedNative;

	/* 音声データのセット */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set sound."))
	void SetSound(USoundAtomCue* NewSound);

	/* 音声データのキューイング */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set next sound."))
	void EnqueueSound(USoundAtomCue* NewSound);

	/* キューに残った音声の数をチェック */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set next sound."))
	int32 GetNumQueuedSounds();

	/* 再生開始 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Start playing."))
	void Play(float StartTime = 0.f);

	/* 再生停止 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Stop playing."))
	void Stop();

	/* フェードイン */
	/* 備考）FadeVolumeLevelの指定には未対応。						*/
	/* 　　　（指定された時間で必ずボリュームが1.0fになります。）	*/
	/* 　　　FadeInDurationに設定可能な値は2.0fが上限です。			*/
	UFUNCTION(BlueprintCallable, Category = "AtomSound")
	void FadeIn(float FadeInDuration, float FadeVolumeLevel = 1.f, float StartTime = 0.f);

	/* フェードアウトして停止 */
	/* 備考）FadeVolumeLevelの指定には未対応。						*/
	/* 　　　（指定された時間で必ずボリュームが0.0fになります。）	*/
	/* 　　　FadeOutDurationに設定可能な値は10.0fが上限です。		*/
	UFUNCTION(BlueprintCallable, Category = "AtomSound")
	void FadeOut(float FadeOutDuration, float FadeVolumeLevel = 0.f);

	/** 再生状態の取得 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Get playback status."))
	EAtomComponentStatus GetStatus();

	/* 一時停止 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Pause playing."))
	void Pause(bool bPause);

	/* 一時停止中かどうか */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Is paused?"))
	bool IsPaused();

	/* 再生中かどうか */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Is playing?"))
	bool IsPlaying();

	/* ボリュームの変更 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set volume."))
	void SetVolume(float Volume);

	/* サウンドオブジェクトの設定 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set SoundObject."))
	void SetSoundObject(UAtomSoundObject * SoundObject);

	/** Set a new pitch multiplier */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set pitch."))
	void SetPitchMultiplier(float NewPitchMultiplier);

	/* ピッチの変更（セント単位） */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set pitch in cent."))
	void SetPitch(float Pitch);

	/* AISACコントロール値の指定（名前指定） */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set Aisac by name."))
	void SetAisacByName(FString ControlName, float ControlValue);

	/* DEPRECATED - Use SetBusSendLevelByName instead. */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Use SetBusSendLevelByName instead."))
	void SetBusSendLevel(int32 BusId, float Level);

	/* バスセンドレベルの設定 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set bus send level."))
	void SetBusSendLevelByName(FString BusName, float Level);

	/* DEPRECATED - Use SetBusSendLevelOffsetByName instead. */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = " Use SetBusSendLevelOffsetByName instead."))
	void SetBusSendLevelOffset(int32 BusId, float LevelOffset);

	/* バスセンドレベルの設定（オフセット指定） */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set bus send level offset."))
	void SetBusSendLevelOffsetByName(FString BusName, float LevelOffset);

	/* ブロックの遷移 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set next block index."))
	void SetNextBlockIndex(int32 BlockIndex);

	/* セレクタラベルの設定 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set selector label."))
	void SetSelectorLabel(FString Selector, FString Label);

	/* ASR Rack IDの指定 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set ASR Rack ID."))
	void SetAsrRackID(int32 asr_rack_id = 0);

	/* ASR Rack IDの複数指定 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Set multiple ASR Rack ID."))
	void SetAsrRackIdArray(TArray<int32> AsrRackIDs);

	/** キューの再生時刻を取得します。単位は秒です。 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Get current playback time."))
	float GetTime();

	/** キューの再生位置を取得します。単位は秒です。 */
	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Get current playback position."))
	float GetSequencePosition();

	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Get Component ID."))
	int32 GetAtomComponentID() const { return AtomComponentID; }

	UFUNCTION(BlueprintCallable, Category = "AtomSound", meta = (ToolTip = "Get Cue Name."))
	FString GetCueName() const { return CueName; }

	UFUNCTION(BlueprintCallable, Category = "AtomSound")
	static void DestroyComponentByID(int32 TargetID);

	UFUNCTION(BlueprintCallable, Category = "AtomSound")
	static void SetDefaultAttenuationEnable(bool bEnable);

	UFUNCTION(BlueprintPure, Category = "AtomSound")
	static bool GetDefaultAttenuationEnable();

	/* AtomExプレーヤハンドルの取得 */
	CriAtomExPlayerHn GetAtomExPlayer();

	/* AtomEx3dSourceハンドルの取得 */
	CriAtomEx3dSourceHn GetAtomEx3dSource();

	/* コンポーネント単位で距離減衰を設定するかどうか */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attenuation, meta = (ToolTip = "Attenuation settings for asset."))
	uint32 bOverrideAttenuation : 1;

	/* 距離減衰設定（距離減衰アセットを使用） */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attenuation, meta = (EditCondition = "!bOverrideAttenuation", ToolTip = "Enable attenuation settings."))
	class USoundAttenuation* AttenuationSettings;

	/* 距離減衰設定（コンポーネント単位の上書き設定） */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attenuation, meta = (EditCondition = "bOverrideAttenuation", ToolTip = "Attenuation overrides."))
	struct FSoundAttenuationSettings AttenuationOverrides;

	/* C++呼び出し専用 */
	void SetSound(USoundAtomCueSheet* InCueSheet, FString InCueName);

	/* オブジェクト再利用時向け初期化処理 */
	void InitializePoolable() {};

	/* オブジェクト返却時向け終了処理 */
	void ShutdownPoolable() {};

#if WITH_EDITORONLY_DATA
	void RegisterAtomSoundInfoComponent();
#endif

	/* ルートオブジェクトとして登録されていることを通知 */
	void MarkAsRooted();

	/* 非レジスターAtomComponentのTick */
	static void TickNonRegisteredComponents();

	/* ルートオブジェクトのTick */
	static void TickRootedComponents();

public:
	// Begin UObject interface.
	virtual void PostInitProperties() override;
	virtual void BeginDestroy() override;
	virtual void DestroyComponent(bool bPromoteChildren = false) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	// End UObject interface.

	// Begin ActorComponent interface
#if WITH_EDITORONLY_DATA
	virtual void OnRegister() override;
#endif
	virtual void OnUnregister() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	// End ActorComponent interface

	// Begin USceneComponent Interface
	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;
	virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport = ETeleportType::None) override;
#if WITH_EDITOR
	/* 音源表示関連のコンポーネントを破棄する */
	virtual void OnAttachmentChanged() override;
#endif
	// End USceneComponent Interface

	/* AttenuationSettingsの取得 */
	const FSoundAttenuationSettings* GetAttenuationSettingsToApply() const;

	static UAtomComponent* GetAtomComponentFromID(int32 TargetID);
	static int32 AtomComponentIDCounter;
	static TMap<int32, UAtomComponent*> AtomIDToComponentMap;
	static TArray<UAtomComponent*> AtomRootedComponentArray;
	static TArray<UAtomComponent*> AtomNonRegisteredComponentArray;

	const UAtomSoundObject * GetAppliedSoundObject() const;

protected:
	/** Utility function called by Play and FadeIn to start a sound playing. */
	void PlayInternal(float StartTime, float FadeInDuration, float FadeVolumeLevel);

private:
	/** The play list to use, if any. */
	FAtomPlaylist* Playlist;

	int32 AtomComponentID;
	double CreatedTime;

	/* 音源 */
	static const uint32 PLAYER_WORK_SIZE = 1536;
	static const uint32 SOURCE_WORK_SIZE = 512;
	uint8 PlayerWork[PLAYER_WORK_SIZE];
	uint8 SourceWork[SOURCE_WORK_SIZE];
	CriAtomExPlayerHn Player;
	CriAtomEx3dSourceHn Source;

	CriAtomExVector PreviousSourceLocation;
	CriAtomExVector PreviousListenerLocation;
	bool bTransformUpdated;
	bool bIsEnableDoppler;

	/* リスナ */
	FAtomListener* Listener;

	/* 距離倍率 */
	float DistanceFactor;

	/* OcclusionのCollision判定などを行うための構造体 */
	FAtomActiveSound AtomActiveSound;
	float Filter_Frequency;

	/* キューシート */
	class USoundAtomCueSheet* CueSheet;

	/* キュー名 */
	FString CueName;

	/* 適用済みSoundObject */
	class UAtomSoundObject* AppliedSoundObject;

	/* 再生ID */
	uint32 PlaybackId;

	/* 再生要求の有無 */
	bool bIsPlayed;

	/* データ要求コールバック */
	static void CRIAPI OnDataRequest(
		void *Object, CriAtomExPlaybackId PlaybackId, CriAtomPlayerHn Player);

	/* リソースの確保 */
	void AllocateResource();

	/* リソースの解放 */
	void ReleaseResource();

	/* 定期処理 */
	void OnTickComponent(float DeltaTime = 0.0f);

	/* トランスフォームの更新 */
	void UpdateTransform(bool bHasOwner = false);

	/* 距離減衰の適用 */
	void ApplyAttenuation(float& Volume, float& FilterFrequency);

	/* サウンドオブジェクトの適用 */
	void ApplySoundObject(UAtomSoundObject * SoundObject);

#if WITH_EDITORONLY_DATA
	/* スピーカーアイコン表示 */
	void UpdateSpriteTexture();

	UPROPERTY(transient, meta = (ToolTip = "Maximum distance for Sphere Component."))
	class UDrawSphereComponent* MaxDistanceSphereComponent;

	UPROPERTY(transient, meta = (ToolTip = "Minimum distance for Sphere Component."))
	class UDrawSphereComponent* MinDistanceSphereComponent;
#endif

#if WITH_EDITOR
	/* 音源範囲の表示（距離減衰上書き時用） */
	void DrawDebugShape();
#endif

	/* 再生終了時のイベント通知 */
	void NotifyAudioFinished();

	/* プレビュー終了検知用デリゲート */
	void OnWorldCleanedUp(UWorld* World, bool bSessionEnded, bool bCleanupResources);

	/* デリゲートハンドル */
	FDelegateHandle OnWorldCleanedUpHandle;
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
