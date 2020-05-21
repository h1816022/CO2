/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2017-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Module Interface of CriWareSequencer
 * File     : ICriWareSequencer.h
 *
 ****************************************************************************/

/* 多重定義防止 */
#pragma once

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"		// For inline LoadModuleChecked()

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
/**
 * The public interface of the CriWareSequencer module
 */
class ICriWareSequencer : public IModuleInterface
{
public:
	/**
	 * Singleton-like access to ICriWareSequencer
	 *
	 * @return Returns CriWareSequencer singleton instance, loading the module on demand if needed
	 */
	static inline ICriWareSequencer& Get()
	{
		return FModuleManager::LoadModuleChecked<ICriWareSequencer>("CriWareSequencer");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("CriWareSequencer");
	}
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
