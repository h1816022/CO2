/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2015-2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Asset Type Action of Atom Cue Sheet
 * File     : AssetTypeActions_SoundAtomCueSheet.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "AssetTypeActions_SoundAtomCueSheet.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareEditorPrivatePCH.h"
#include "AtomSoundData.h"
#include "SoundAtomCueSheet.h"

/* Unreal Engine 4関連ヘッダ */
#include "EditorStyleSet.h"
#include "EditorReimportHandler.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "AssetTypeActions"

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
void FAssetTypeActions_SoundAtomCueSheet::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	auto AtomCueSheets = GetTypedWeakObjectPtrs<USoundAtomCueSheet>(InObjects);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("ReimportAtomCueSheetLabel", "Reimport"),
		LOCTEXT("ReimportAtomCueSheetTooltip", "Reimport the selected AtomCueSheet(s)."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "ContentBrowser.AssetActions.ReimportAsset"),
		FUIAction(
			FExecuteAction::CreateSP(this, &FAssetTypeActions_SoundAtomCueSheet::ExecuteReimport, AtomCueSheets),
			FCanExecuteAction::CreateSP(this, &FAssetTypeActions_SoundAtomCueSheet::CanExecuteReimport, AtomCueSheets)
			)
		);
}

bool FAssetTypeActions_SoundAtomCueSheet::CanExecuteReimport(const TArray<TWeakObjectPtr<USoundAtomCueSheet>> Objects) const
{
	for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt) {
		auto Object = (*ObjIt).Get();
		if (Object) {
			return true;
		}
	}

	return false;
}

void FAssetTypeActions_SoundAtomCueSheet::ExecuteReimport(const TArray<TWeakObjectPtr<USoundAtomCueSheet>> Objects) const
{
	for (auto ObjIt = Objects.CreateConstIterator(); ObjIt; ++ObjIt) {
		auto Object = (*ObjIt).Get();
		if (Object) {
			FReimportManager::Instance()->Reimport(Object, false);
		}
	}
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/

#undef LOCTEXT_NAMESPACE

/* --- end of file --- */
