/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Base CriFsBinder Component
 * File     : CriFsBinderComponent.h
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
#include "GameFramework/Actor.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareApi.h"

/* モジュールヘッダ */
#include "CriFsBinderComponent.generated.h"

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
UENUM()
enum class ECriFsBinderStatus : uint8
{
	Stop,				/** 停止中 */
	Binding,			/** バインド中 */
	Complete,			/** バインド完了 */
	Error				/** エラー */
};

/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      クラス宣言
 *      Prototype Classes
 ***************************************************************************/
UCLASS(ClassGroup=CRIWARE, BlueprintType,
	meta=(BlueprintSpawnableComponent, DisplayName = "Cri Fs Binder", ToolTip = "Cri Fs Binder Component"))
class CRIWARERUNTIME_API UCriFsBinderComponent : public USceneComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBindCompleted);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBindError);

public:
	UCriFsBinderComponent(const FObjectInitializer& ObjectInitializer);

	/* ファイルパス */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FilePath")
	FString FilePath;

	/* バインド完了時に呼び出されるデリゲート */
	UPROPERTY(BlueprintAssignable, Category="CriFsBinderComponent")
	FOnBindCompleted OnBindCompleted;

	/* バインド失敗時に呼び出されるデリゲート */
	UPROPERTY(BlueprintAssignable, Category="CriFsBinderComponent")
	FOnBindError OnBindError;

	/* バインド */
	UFUNCTION(BlueprintCallable, Category="CriFsBinderComponent")
	void Bind();

	/* 停止 */
	UFUNCTION(BlueprintCallable, Category="CriFsBinderComponent")
	void Stop();

	/* ステータスの取得 */
	UFUNCTION(BlueprintCallable, Category="CriFsBinderComponent")
	ECriFsBinderStatus GetStatus();

	/* バインダハンドルの取得 */
	CriFsBinderHn GetBinder() { return Binder; }

	// Begin UObject interface.
	virtual void PostLoad() override;
	virtual void BeginDestroy() override;
	// End of UObject interface

	// UActorComponent interface
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// End of UActorComponent interface

private:
	CriFsBinderHn Binder;
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
