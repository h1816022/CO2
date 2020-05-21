/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Base CriFsBinder Component
 * File     : CriFsBinderComponent.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "CriFsBinderComponent.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareRuntimePrivatePCH.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "CriFsBinderComponent"

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
/* File Systemライブラリの終了判定用 */
extern "C" CriBool CRIAPI criFs_IsInitialized(void);

/***************************************************************************
 *      変数定義
 *      Variable Definition
 ***************************************************************************/

/***************************************************************************
 *      クラス定義
 *      Class Definition
 ***************************************************************************/
UCriFsBinderComponent::UCriFsBinderComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* stub */
}

void UCriFsBinderComponent::PostLoad()
{
	Super::PostLoad();
}

void UCriFsBinderComponent::BeginDestroy()
{
	Super::BeginDestroy();
}

void UCriFsBinderComponent::Bind()
{
	/* stub */
}

void UCriFsBinderComponent::Stop()
{
	/* stub */
}

ECriFsBinderStatus UCriFsBinderComponent::GetStatus()
{
	return ECriFsBinderStatus::Error;
}

void UCriFsBinderComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/* stub */
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/
#undef LOCTEXT_NAMESPACE

/* --- end of file --- */
