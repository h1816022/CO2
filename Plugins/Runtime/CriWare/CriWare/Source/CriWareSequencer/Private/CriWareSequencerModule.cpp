/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2017-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : CriWareSequencer Module Implementation
 * File     : CriWareSequencerModule.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
 /* CRIWAREプラグインヘッダ */
#include "AtomTrackEditor.h"

/* モジュールヘッダ */
#include "CriWareSequencerPrivatePCH.h"
#include "ICriWareSequencer.h"

/* Unreal Engine 4関連ヘッダ */
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "ISequencer.h"
#include "ISequencerModule.h"

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

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/***************************************************************************
 *      変数定義
 *      Variable Definition
 ***************************************************************************/

/***************************************************************************
 *      クラス定義
 *      Class Definition
 ***************************************************************************/
/**
 * CriWareSequencer module implementation (private)
 */
class FCriWareSequencerModule : public ICriWareSequencer
{
public:
	/** IModuleInterface */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	/** Registered delegate handles */
	FDelegateHandle AtomTrackCreateEditorHandle;
};

IMPLEMENT_MODULE(FCriWareSequencerModule, CriWareSequencer);

void FCriWareSequencerModule::StartupModule()
{
	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	AtomTrackCreateEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FAtomTrackEditor::CreateTrackEditor));
}

void FCriWareSequencerModule::ShutdownModule()
{
	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	SequencerModule.UnRegisterTrackEditor(AtomTrackCreateEditorHandle);
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/

/* --- end of file --- */
