/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2017-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Movie Scene Atom Track
 * File     : MovieSceneAtomTrack.h
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
#include "MovieSceneNameableTrack.h"
#include "Runtime/Launch/Resources/Version.h"

/* CRIWAREプラグインヘッダ */
#include "SoundAtomCue.h"

/* モジュールヘッダ */
#include "MovieSceneAtomTrack.generated.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
namespace AtomTrackConstants {
	/* シーケンサエディタでカーソルを移動させた際のプレビュー時間	*/
	/* 備考）ストリーム再生のバッファリング時間を考慮し、			*/
	/* 　　　UE4標準サウンドよりもプレビュー時間を長めに設定。		*/
	const float ScrubDuration = 0.200f;
}

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
 * Handles manipulation of audio.
 */
UCLASS(MinimalAPI)
class UMovieSceneAtomTrack : public UMovieSceneNameableTrack
{
	GENERATED_UCLASS_BODY()

	/** Adds a new sound cue to the audio */
	virtual UMovieSceneSection* AddNewSoundOnRow(USoundAtomCue* Sound, FFrameNumber Time, int32 RowIndex);

	/** Adds a new sound cue on the next available/non-overlapping row */
	virtual UMovieSceneSection* AddNewSound(USoundAtomCue* Sound, FFrameNumber Time) { return AddNewSoundOnRow(Sound, Time, INDEX_NONE); }

	/** @return The audio sections on this track */
	const TArray<UMovieSceneSection*>& GetAtomSections() const
	{
		return AtomSections;
	}

	/** @return true if this is a master audio track */
	bool IsAMasterTrack() const;

public:
	// UMovieSceneTrack interface
	virtual void RemoveAllAnimationData() override;
	virtual bool HasSection(const UMovieSceneSection& Section) const override;
	virtual void AddSection(UMovieSceneSection& Section) override;
	virtual void RemoveSection(UMovieSceneSection& Section) override;
	virtual bool IsEmpty() const override;
	virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;
	virtual bool SupportsMultipleRows() const override;
#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 19
	virtual FMovieSceneTrackRowSegmentBlenderPtr GetRowSegmentBlender() const override;
#else
	virtual TInlineValue<FMovieSceneSegmentCompilerRules> GetRowCompilerRules() const override;
#endif

private:
	/** List of all master audio sections */
	UPROPERTY()
	TArray<UMovieSceneSection*> AtomSections;

#if WITH_EDITORONLY_DATA
public:
	/**
	 * Get the height of this track's rows
	 */
	int32 GetRowHeight() const
	{
		return RowHeight;
	}

	/**
	 * Set the height of this track's rows
	 */
	void SetRowHeight(int32 NewRowHeight)
	{
		RowHeight = FMath::Max(16, NewRowHeight);
	}

private:
	/** The height for each row of this track */
	UPROPERTY()
	int32 RowHeight;
#endif
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
