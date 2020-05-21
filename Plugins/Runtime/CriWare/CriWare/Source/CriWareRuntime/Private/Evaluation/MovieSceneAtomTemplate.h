/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2017-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Movie Scene Atom Template
 * File     : MovieSceneAtomTemplate.h
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
#include "UObject/ObjectMacros.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "Channels/MovieSceneFloatChannel.h"

/* CRIWAREプラグインヘッダ */
#include "AtomComponent.h"
#include "SoundAtomCue.h"
#include "Sections/MovieSceneAtomSection.h"

/* モジュールヘッダ */
#include "MovieSceneAtomTemplate.generated.h"

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
USTRUCT()
struct FMovieSceneAtomSectionTemplateData
{
	GENERATED_BODY()

	FMovieSceneAtomSectionTemplateData();
	FMovieSceneAtomSectionTemplateData(const UMovieSceneAtomSection& Section);

	/** Ensure that the sound is playing for the specified audio component and data */
	void EnsureAtomIsPlaying(UAtomComponent& AtomComponent, FPersistentEvaluationData& PersistentData, const FMovieSceneContext& Context, bool bAllowSpatialization, IMovieScenePlayer& Player) const;

	/** The sound cue or wave that this template plays. Not to be dereferenced on a background thread */
	UPROPERTY()
	USoundAtomCue* Sound;

	/** The offset into the beginning of the audio clip */
	UPROPERTY()
	float AtomStartOffset;

	/** The frame number at which the audio starts playing */
	UPROPERTY()
	double SectionStartTimeSeconds;

	/** The amount which this audio is time dilated by */
	UPROPERTY()
	FMovieSceneFloatChannel AtomPitchMultiplierCurve;

	/** The volume the sound will be played with. */
	UPROPERTY()
	FMovieSceneFloatChannel AtomVolumeCurve;

	/** The row index of the section */
	UPROPERTY()
	int32 RowIndex;
};

USTRUCT()
struct FMovieSceneAtomSectionTemplate : public FMovieSceneEvalTemplate
{
	GENERATED_BODY()

	FMovieSceneAtomSectionTemplate() {}
	FMovieSceneAtomSectionTemplate(const UMovieSceneAtomSection& Section);

	UPROPERTY()
	FMovieSceneAtomSectionTemplateData AtomData;

private:

	virtual UScriptStruct& GetScriptStructImpl() const override { return *StaticStruct(); }
	virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
