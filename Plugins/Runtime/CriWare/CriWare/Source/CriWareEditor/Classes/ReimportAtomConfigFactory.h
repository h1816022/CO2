/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2015-2016 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Reimport Factory of Atom Config File
 * File     : ReimportAtomConfigFactory.h
 *
 ****************************************************************************/

/* 多重定義防止 */
#pragma once

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* CRIWAREプラグインヘッダ */
#include "AtomConfigFactory.h"

/* Unreal Engine 4関連ヘッダ */
#include "EditorReimportHandler.h"
#include "ReimportAtomConfigFactory.generated.h"

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
UCLASS()
class UReimportAtomConfigFactory : public UAtomConfigFactory, public FReimportHandler
{
	GENERATED_UCLASS_BODY()

	// Begin FReimportHandler interface
	virtual bool CanReimport( UObject* Obj, TArray<FString>& OutFilenames ) override;
	virtual void SetReimportPaths( UObject* Obj, const TArray<FString>& NewReimportPaths ) override;
	virtual EReimportResult::Type Reimport( UObject* Obj ) override;
	// End FReimportHandler interface
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
