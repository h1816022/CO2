/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2016 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Asset Type Action of Atom Cue Sheet
 * File     : AssetTypeActions_SoundAtomCueSheet.h
 *
 ****************************************************************************/

/* 多重定義防止 */
#pragma once

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* Unreal Engine 4関連ヘッダ */
#include "AssetTypeActions_Base.h"
#include "SoundAtomCueSheet.h"

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
class FAssetTypeActions_SoundAtomCueSheet : public FAssetTypeActions_Base
{
public:
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_SoundAtomCueSheet", "Atom Cue Sheet"); }
	virtual FColor GetTypeColor() const override { return FColor(255, 127, 39); }
	virtual UClass* GetSupportedClass() const override { return USoundAtomCueSheet::StaticClass(); }
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder) override;
	virtual bool CanFilter() override { return true; }
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Sounds; }
	// End IAssetTypeActions

private:
	/** Can we execute a reimport for the selected objects? */
	bool CanExecuteReimport(const TArray<TWeakObjectPtr<USoundAtomCueSheet>> Objects) const;

	/** Handler for when Reimport is selected */
	void ExecuteReimport(const TArray<TWeakObjectPtr<USoundAtomCueSheet>> Objects) const;
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
