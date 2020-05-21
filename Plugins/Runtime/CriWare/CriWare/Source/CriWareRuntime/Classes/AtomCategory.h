/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2016-2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Atom Category
 * File     : AtomCategory.h
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
#include "Kismet/BlueprintFunctionLibrary.h"

/* CRIWAREプラグインヘッダ */
#include "AtomAisac.h"

/* モジュールヘッダ */
#include "AtomCategory.generated.h"

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
UCLASS(meta = (ToolTip = "AtomCategory class."))
class CRIWARERUNTIME_API UAtomCategory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* カテゴリボリュームの設定 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Set volume by name."))
		static void SetVolumeByName(FString CategoryName, float Volume);

	/* カテゴリボリュームの取得 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Get volume by name."))
		static float GetVolumeByName(FString CategoryName);

	/* カテゴリのポーズ／ポーズ解除 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Pause by name."))
		static void PauseByName(FString CategoryName, bool bPause);

	/* カテゴリがポーズ状態の取得 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Is paused by name."))
		static bool IsPausedByName(FString CategoryName);

	/* 任意のIDのカテゴリの全てのAISACコントロールをリセット */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Reset all AISAC control by id."))
		static bool ResetAllAisacControlById(int32 CategoryId);

	/* 任意の名前のカテゴリの全てのAISACコントロールをリセット */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Reset all AISAC control by name."))
		static bool ResetAllAisacControlByName(FString CategoryName);

	/* ID指定でカテゴリにアタッチされているAISAC数を取得 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Get number of attached AISACs by id."))
		static int32 GetNumAttachedAisacsById(int32 CategoryId);

	/* 名前指定でカテゴリにアタッチされているAISAC数を取得 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Get number of attached AISACs by name."))
		static int32 GetNumAttachedAisacsByName(FString CategoryName);

	/* ID指定でカテゴリにアタッチされているAISACの情報を取得 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Get attached AISAC info by id."))
		static void GetAttachedAisacInfoById(int32 CategoryId, int32 AisacAttachedIndex, bool & IsSuccess, FAtomAisacInfo & AisacInfo);

	/* 名前指定でカテゴリにアタッチされているAISACの情報を取得 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Get attached AISAC info by name."))
		static void GetAttachedAisacInfoByName(FString CategoryName, int32 AisacAttachedIndex, bool & IsSuccess, FAtomAisacInfo & AisacInfo);

	/* カテゴリAISACの設定 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Set AISAC control by name."))
		static void SetAisacControlByName(FString CategoryName, FString AisacName, float Value);

	/* ID指定でカテゴリAISACコントロールの現在値を取得 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Get current AISAC control value by id."))
		static float GetCurrentAisacControlValueById(int32 CategoryId, int32 AisacControlId);

	/* 名前指定でカテゴリAISACコントロールの現在値を取得 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Get current AISAC control value by name."))
		static float GetCurrentAisacControlValueByName(FString CategoryName, FString AisacControlName);

	/* 指定したカテゴリの音声を全て停止 */
	UFUNCTION(BlueprintCallable, Category = "AtomCategory", meta = (ToolTip = "Stop by name."))
		static void StopByName(FString CategoryName);
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
