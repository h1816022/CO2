/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Atom Thumbnail
 * File     : AtomThumbnail.h
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
#include "Rendering/RenderingCommon.h"
#include "MovieSceneSection.h"

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
class FAtomThumbnail
	: public ISlateViewport
	, public TSharedFromThis<FAtomThumbnail>
{
public:
	FAtomThumbnail(UMovieSceneSection& InSection, TRange<float> DrawRange, int InTextureSize, const FLinearColor& BaseColor, float DisplayScale);
	~FAtomThumbnail();

	/* ISlateViewport interface */
	virtual FIntPoint GetSize() const override;
	virtual class FSlateShaderResource* GetViewportRenderTargetTexture() const override;
	virtual bool RequiresVsync() const override;

	/** Returns whether this thumbnail has a texture to render */
	virtual bool ShouldRender() const { return TextureSize > 0; }

private:
	/** Generates the waveform preview and dumps it out to the OutBuffer */
	void GenerateWaveformPreview(TArray<uint8>& OutBuffer, TRange<float> DrawRange, float DisplayScale);

private:
	/** The section we are visualizing */
	UMovieSceneSection& Section;

	/** The Texture RHI that holds the thumbnail */
	class FSlateTexture2DRHIRef* Texture;

	/** Size of the texture */
	int32 TextureSize;

	/** Waveform colors */
	FLinearColor FillColor;
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
