/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Atom Sound Data (Cue)
 * File     : SoundAtomCue.h
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
#include "Sound/SoundConcurrency.h"

/* CRIWAREプラグインヘッダ */
#include "SoundAtomCueSheet.h"

/* モジュールヘッダ */
#include "SoundAtomCue.generated.h"

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
UCLASS(hidecategories=Object, editinlinenew, BlueprintType, meta = (ToolTip = "SoundAtomCue class."))
class CRIWARERUNTIME_API USoundAtomCue : public UObject
{
	GENERATED_BODY()

public:
	USoundAtomCue(const FObjectInitializer& ObjectInitializer);

	/** (DEPRECATED) CueSheet name is not available. */
	FString CueSheetName;

	/* キューシートオブジェクト */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Reference", meta = (ToolTip = "Cue sheet."))
	USoundAtomCueSheet* CueSheet;

	/* キュー名 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Target", meta = (ToolTip = "Cue name."))
	FString CueName;

	/* Atomパラメータを検索して適用するかどうか */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atom", meta = (ToolTip = "Searches AtomParameterComponent of the owner actor and applies it on play."))
	bool bApplyAtomParameter;

	/** Whether or not to override the sound concurrency object with local concurrency settings. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Concurrency)
	uint32 bOverrideConcurrency : 1;

	/** If Override Concurrency is false, the sound concurrency settings to use for this sound. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Concurrency, meta = (EditCondition = "!bOverrideConcurrency"))
	class USoundConcurrency* SoundConcurrencySettings;

	/** If Override Concurrency is true, concurrency settings to use. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Concurrency, meta = (EditCondition = "bOverrideConcurrency"))
	struct FSoundConcurrencySettings ConcurrencyOverrides;

	/** Sound priority (higher value is higher priority) used for concurrency resolution. This priority value is weighted against the final volume of the sound. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Concurrency, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "100.0", UIMax = "100.0"))
	float Priority;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attenuation")
	class USoundAttenuation* DefaultAttenuation;

#if WITH_EDITORONLY_DATA
	/** Duration of sound in seconds. */
	UPROPERTY(Category=Info, VisibleAnywhere)
	float Duration;

	/* ユーザデータ */
	UPROPERTY(Category=Info, VisibleAnywhere)
	FString UserData;

	/* カテゴリ名一覧 */
	UPROPERTY(Category=Info, VisibleAnywhere)
	TArray<FString> CategoryName;

	/* AISACコントロール名一覧 */
	UPROPERTY(Category=Info, VisibleAnywhere)
	TArray<FString> AisacControlName;
#endif

	UFUNCTION(BlueprintCallable, Category="Sound Atom Cue", meta = (ToolTip = "Get the length of the cue sheet."))
	int32 GetLength();

	UFUNCTION(BlueprintCallable, Category="Sound Atom Cue", meta = (ToolTip = "Get user data of the cue sheet."))
	FString GetUserData();

	// Begin UObject interface.
	virtual void PostLoad() override;
	virtual void Serialize(FArchive& Ar) override;
	virtual void BeginDestroy() override;
	// End UObject interface.

	/* 展開済みPCMデータ */
	uint8* RawPCMData;
	int32 RawPCMDataChannels;
	int32 RawPCMDataSamplingRate;
	int32 RawPCMDataSamples;

#if WITH_EDITOR
	/* エディタ上に描画するため、最大、最小減衰距離を返す */
	float GetMaxAttenuationDistance();
	float GetMinAttenuationDistance();
#endif

	/** Gets the sound concurrency to apply on this active sound instance */
	const struct FSoundConcurrencySettings* GetSoundConcurrencySettingsToApply() const;

	/** Returns the sound concurrency object ID if it exists. If it doesn't exist, returns 0. */
	uint32 GetSoundConcurrencyObjectID() const;

	float GetPriority() const { return Priority; }

private:
#if WITH_EDITOR
	/* エディタ上に描画するため、最大、最小減衰距離を保持しておく */

	/* CueInfoを読みこんで、最大、最小減衰距離を保持する。
	 * CueInfo読み込みに成功: true
	 * CueInfo読み込みに失敗: false
	 */
	bool ReadCueInfo();
	float MinAttenuationDistance;
	float MaxAttenuationDistance;
#endif

private:
	/* 旧データの読み込み */
	void SerializeOldVersion(FArchive& Ar);
};

/* AtomCueアセットのバージョン管理用 */
struct FAtomCueVersion
{
	/* バージョン番号 */
	static const int32 AssetVersion;

	/* GUID */
	static const FGuid AssetGuid;
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
