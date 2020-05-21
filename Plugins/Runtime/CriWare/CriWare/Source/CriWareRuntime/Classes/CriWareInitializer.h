/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Initializer
 * File     : CriWareInitializer.h
 *
 ****************************************************************************/

/* 多重定義防止 */
#pragma once

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* Unreal Engine 4関連ヘッダ */
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#include "CriWareApi.h"
#include "AtomComponent.h"
#include "AtomSoundConcurrency.h"
#include "CriWarePlatform.h"

/* モジュールヘッダ */
#include "CriWareInitializer.generated.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
/* バージョン情報 */
/* Version informaiton */
#define CRIWARE_UE4_PLUGIN_VERSION		"1.26.03.04"

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/

 /***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define FS_NUM_BINDERS                                 CRIFS_CONFIG_DEFAULT_NUM_BINDERS
#define FS_MAX_BINDS                                   CRIFS_CONFIG_DEFAULT_MAX_BINDS
#define FS_NUM_LOADERS                                 CRIFS_CONFIG_DEFAULT_NUM_LOADERS
#define FS_MAX_PATH                                    1024
#define FS_OUTPUT_LOG                                  false
#define ATOM_AUTOMATICALLY_CREATE_CUE_ASSET            true
#define ATOM_USES_INGAME_PREVIEW                       false
#define ATOM_OUTPUT_LOG                                false
#define ATOM_MAX_VIRTUAL_VOICES                        32
#define ATOM_NUM_STANDARD_MEMORY_VOICES                16
#define ATOM_STANDARD_MEMORY_VOICE_NUM_CHANNELS        CRIATOM_DEFAULT_INPUT_MAX_CHANNELS
#define ATOM_STANDARD_MEMORY_VOICE_SAMPLING_RATE       CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE
#define ATOM_NUM_STANDARD_STREAMING_VOICES             8
#define ATOM_STANDARD_STREAMING_VOICE_NUM_CHANNELS     CRIATOM_DEFAULT_INPUT_MAX_CHANNELS
#define ATOM_STANDARD_STREAMING_VOICE_SAMPLING_RATE    CRIATOM_DEFAULT_INPUT_MAX_SAMPLING_RATE
#define ATOM_DISTANCE_FACTOR                           1.0f
#if !defined(CRIWARE_UE4_LE)	/* <cri_delete_if_LE> */
#endif	/* </cri_delete_if_LE> */

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/

/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/
/* UE4プロファイラ用 */
#if STATS
DECLARE_STATS_GROUP(TEXT("CRIWARE"), STATGROUP_CriWare, STATCAT_Advanced);
#endif

/***************************************************************************
 *      クラス宣言
 *      Prototype Classes
 ***************************************************************************/
UCLASS(meta=(ToolTip="CriWareInitializer class."))
class CRIWARERUNTIME_API UCriWareInitializer : public UObject
{
	GENERATED_BODY()

public:
	UCriWareInitializer(const FObjectInitializer& ObjectInitializer);

	/* コンテンツパスの取得 */
	static FString GetContentDir();

	/* 絶対パスの取得 */
	static FString ConvertToAbsolutePathForExternalAppForRead(const TCHAR* Filename);

	/* リスナの取得 */
	static CriAtomEx3dListenerHn GetListener(int32 PlayerIndex = 0);

	/* 距離係数の取得 */
	static float GetDistanceFactor();

	/* メモリ再生ボイスプールの取得 */
	static CriAtomExVoicePoolHn GetMemoryVoicePool();

	/* ストリーム再生ボイスプールの取得 */
	static CriAtomExVoicePoolHn GetStreamingVoicePool();

	/* ACFアセットパスの取得 */
	static FSoftObjectPath GetAtomConfigAssetReference();

	/* リスナの有効化／無効化 */
	static void SetListenerAutoUpdateEnabled(bool bEnabled, int32 PlayerIndex = 0);

	/* リスナ位置の指定 */
	static void SetListenerLocation(FVector Location, int32 PlayerIndex = 0);

	/* リスナの向きの指定 */
	static void SetListenerRotation(FRotator Rotation, int32 PlayerIndex = 0);

	/* リスナ位置の取得 */
	static FVector GetListenerLocation(int32 PlayerIndex = 0);

	/* リスニングポイントの取得 */
	static FVector GetListeningPoint(int32 PlayerIndex = 0);

	/* ACFがロード済みかどうか */
	static bool IsAcfLoaded();

	/* モニタライブラリの処理を無効化 */
	static void DisableMonitor();

	/** Access to platform specific functions. */
	static FCriWarePlatform Platform;

	// Begin UObject interface.
	virtual void PostInitProperties() override;
	virtual void BeginDestroy() override;
	// End  UObject interface

#if defined(CRIWARE_UE4_LE)
	static void* CriWareDllHandle;
	static uint32 NumInstances;
#endif

	static FSoftObjectPath AcfAssetReference;
	static uint8* AcfData;
	static CriAtomDspSpectraHn dsp_hn;
	static TArray<FString> bus_name;
	static TArray<int32> asr_rack_id;

	static class FAtomSoundConcurrencyManager* ConcurrencyManager;
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
