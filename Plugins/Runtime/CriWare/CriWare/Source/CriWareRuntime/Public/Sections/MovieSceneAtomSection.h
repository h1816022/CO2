/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2017-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Movie Scene Atom Section
 * File     : MovieSceneAtomSection.h
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
#include "MovieSceneSection.h"
#include "Channels/MovieSceneFloatChannel.h"

/* CRIWAREプラグインヘッダ */
#include "SoundAtomCue.h"

/* モジュールヘッダ */
#include "MovieSceneAtomSection.generated.h"

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
 * Atom section, for use in the master audio, or by attached audio objects
 */
UCLASS(MinimalAPI)
class UMovieSceneAtomSection : public UMovieSceneSection
{
	GENERATED_UCLASS_BODY()

	/** Sets this section's sound */
	void SetSound(class USoundAtomCue* InSound) { Sound = InSound; }

	/** Gets the sound for this section */
	class USoundAtomCue* GetSound() const { return Sound; }

	/** Set the offset into the beginning of the audio clip */
	void SetStartOffset(float InStartOffset) {StartOffset = InStartOffset;}

	/** Get the offset into the beginning of the audio clip */
	float GetStartOffset() const {return StartOffset;}

	/**
	 * Gets the sound volume curve
	 *
	 * @return The rich curve for this sound volume
	 */
	const FMovieSceneFloatChannel& GetSoundVolumeChannel() const { return SoundVolume; }

	/**
	 * Gets the sound pitch curve
	 *
	 * @return The rich curve for this sound pitch
	 */
	const FMovieSceneFloatChannel& GetPitchMultiplierChannel() const { return PitchMultiplier; }

	/**
	 * Return the sound volume
	 *
	 * @param InTime	The position in time within the movie scene
	 * @return The volume the sound will be played with.
	 */
	float GetSoundVolume(FFrameTime InTime) const
	{
		float OutValue = 0.f;
		SoundVolume.Evaluate(InTime, OutValue);
		return OutValue;
	}

	/**
	 * Return the pitch multiplier
	 *
	 * @param Position	The position in time within the movie scene
	 * @return The pitch multiplier the sound will be played with.
	 */
	float GetPitchMultiplier(FFrameTime InTime) const
	{
		float OutValue = 0.f;
		PitchMultiplier.Evaluate(InTime, OutValue);
		return OutValue;
	}

	/**
	 * @return Whether subtitles should be suppressed
	 */
	bool GetSuppressSubtitles() const
	{
		return bSuppressSubtitles;
	}

public:
	// MovieSceneSection interface
	virtual TOptional<TRange<FFrameNumber>> GetAutoSizeRange() const override;
	virtual void TrimSection(FQualifiedFrameTime TrimTime, bool bTrimLeft) override;
	virtual UMovieSceneSection* SplitSection(FQualifiedFrameTime SplitTime) override;
	virtual TOptional<FFrameTime> GetOffsetTime() const override;
	virtual FMovieSceneEvalTemplatePtr GenerateTemplate() const override;

	//~ UObject interface
	virtual void Serialize(FArchive& Ar) override;

private:
	/** The sound cue or wave that this section plays */
	UPROPERTY(EditAnywhere, Category="Atom")
	USoundAtomCue* Sound;

	/** The offset into the beginning of the audio clip */
	UPROPERTY(EditAnywhere, Category="Atom")
	float StartOffset;

	/** The volume the sound will be played with. */
	UPROPERTY()
	FMovieSceneFloatChannel SoundVolume;

	/** The pitch multiplier the sound will be played with. */
	UPROPERTY()
	FMovieSceneFloatChannel PitchMultiplier;

	UPROPERTY(EditAnywhere, Category="Atom")
	bool bSuppressSubtitles;
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
