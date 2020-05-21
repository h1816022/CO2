/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Asset Type Action of Atom Cue
 * File     : AssetTypeActions_SoundAtomCue.h
 *
 ****************************************************************************/

/* 多重定義防止 */
#pragma once

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* Unreal Engine 4関連ヘッダ */
#include "SoundAtomCue.h"
#include "AssetTypeActions_Base.h"

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
class FAssetTypeActions_SoundAtomCue : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_SoundAtomCue() :SoundAtomCueAssetCategory(EAssetTypeCategories::Sounds) {}
	FAssetTypeActions_SoundAtomCue(EAssetTypeCategories::Type InAssetCategory) : SoundAtomCueAssetCategory(InAssetCategory) {}
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_SoundAtomCue", "Atom Cue"); }
	virtual FColor GetTypeColor() const override { return FColor(255, 201, 14); }
	virtual UClass* GetSupportedClass() const override;
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override { return true; }
	virtual void GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder ) override;
	virtual void AssetsActivated(const TArray<UObject*>& InObjects, EAssetTypeActivationMethod::Type ActivationType) override;
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Sounds; }
	virtual bool CanFilter() override { return true; }
	virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;

protected:
	/** Plays the specified sound wave */
	void PlaySound(USoundAtomCue* Sound) const;

	/** Stops any currently playing sounds */
	void StopSound() const;

	/** Return true if the specified sound is playing */
	bool IsSoundPlaying(USoundAtomCue* Sound) const;

private:
	/** Handler for when PlaySound is selected */
	void ExecutePlaySound(TArray<TWeakObjectPtr<USoundAtomCue>> Objects) const;

	/** Handler for when StopSound is selected */
	void ExecuteStopSound(TArray<TWeakObjectPtr<USoundAtomCue>> Objects) const;

	/** Returns true if only one sound is selected to play */
	bool CanExecutePlayCommand(TArray<TWeakObjectPtr<USoundAtomCue>> Objects) const;

private:
	EAssetTypeCategories::Type SoundAtomCueAssetCategory;
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
