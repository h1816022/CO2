/****************************************************************************
*
* CRI Middleware SDK
*
* Copyright (c) 2018 CRI Middleware Co., Ltd.
*
* Library  : CRIWARE plugin for Unreal Engine 4
* Module   : Sound Atom Cue Factory
* File     : SoundAtomCueFactory.h
*
****************************************************************************/

/* 多重定義防止 */
#pragma once

/***************************************************************************
*      インクルードファイル
*      Include files
***************************************************************************/
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Factories/Factory.h"

#include "SoundAtomCueFactory.generated.h"
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
UCLASS(hidecategories = Object, MinimalAPI)
class USoundAtomCueFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

	// Begin UFactory Interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	// Begin UFactory Interface	
};

/***************************************************************************
*      関数宣言
*      Prototype Functions
***************************************************************************/

/* --- end of file --- */
