/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Previewer
 * File     : CriWarePreviewer.h
 *
 ****************************************************************************/

/* 多重定義防止 */
#pragma once

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* CRIWAREプラグインヘッダ */
#include "SoundAtomCue.h"
#include "AtomComponent.h"

/* Unreal Engine 4関連ヘッダ */
#include "CriWarePreviewer.generated.h"

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
class UCriWarePreviewer : public UObject
{
	GENERATED_BODY()

public:
	/* エディタプレビュー用 */
	static void PlayPreviewSound(USoundAtomCue* Sound);
	static bool IsPreviewing(USoundAtomCue* Sound);
	static void StopPreviewing();

	// Begin UObject interface.
	virtual void PostInitProperties() override;
	virtual void BeginDestroy() override;
	// End  UObject interface
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
