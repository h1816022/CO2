/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2016-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Atom ASR Rack
 * File     : AtomAsrRack.h
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

/* モジュールヘッダ */
#include "AtomAsrRack.generated.h"

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
UCLASS(BlueprintType, meta = (ToolTip = "AtomAsrRack class."))
class CRIWARERUNTIME_API UAtomAsrRack : public UObject
{
	GENERATED_UCLASS_BODY()

	/* デフォルトASRラックの取得 */
	UFUNCTION(BlueprintCallable, Category="AtomAsrRack", meta = (ToolTip = "Get the default ASR rack."))
	static UAtomAsrRack* GetDefaultAsrRack();

	/* ASRラックの取得 */
	UFUNCTION(BlueprintCallable, Category="AtomAsrRack", meta = (ToolTip = "Get ASR rack."))
	static UAtomAsrRack* GetAsrRack(int32 AsrRackId);

	/* DSPバス設定の適用 */
	UFUNCTION(BlueprintCallable, Category="AtomAsrRack", meta = (ToolTip = "Attach DSP bus setting."))
	void AttachDspBusSetting(FString SettingName);

	/* DSPバス設定の無効化 */
	UFUNCTION(BlueprintCallable, Category="AtomAsrRack", meta = (ToolTip = "Detach DSP bus setting."))
	void DetachDspBusSetting();

	/* DSPバススナップショットの適用 */
	UFUNCTION(BlueprintCallable, Category="AtomAsrRack", meta = (ToolTip = "Apply DSP bus snapshot."))
	void ApplyDspBusSnapshot(FString SnapshotName, int32 Milliseconds);

	/* DSPバスボリュームの設定 */
	UFUNCTION(BlueprintCallable, Category="AtomAsrRack", meta = (ToolTip = "Set bus volume."))
	void SetBusVolumeByName(FString BusName, float Volume);

	/* DSPバスセンドレベルの設定 */
	UFUNCTION(BlueprintCallable, Category="AtomAsrRack", meta = (ToolTip = "Set bus send level."))
	void SetBusSendLevelByName(FString SourceBusName, FString DestBusName, float Level);

	/* エフェクトのバイパス設定 */
	UFUNCTION(BlueprintCallable, Category="AtomAsrRack", meta = (ToolTip = "Set effect bypass."))
	void SetEffectBypass(FString BusName, FString EffectName, bool Bypasses);

	/* レベル測定結果の取得 */
	UFUNCTION(BlueprintCallable, Category = "AtomAsrRack", meta = (ToolTip = "Set bus send level."))
	bool GetBusAnalyzerInfo(FString DspBusName, int32& num_channels, TArray<float>& rms_levels, TArray<float>& peak_levels, TArray<float>& peak_hold_levels);

	/* ASRラックID */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="AtomAsrRack", meta = (ToolTip = "Rack ID."))
	int32 RackId;
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
