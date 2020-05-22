// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundEffectSource.h"
#include "SourceEffectLowPassFilter.generated.h"

// ========================================================================
// FSourceEffectLowPassFilterSettings
// This is the source effect's setting struct. 
// ========================================================================

USTRUCT(BlueprintType)
struct CO2_API FSourceEffectLowPassFilterSettings
{
	GENERATED_USTRUCT_BODY()

	// Volume attenuation in dB. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SourceEffect|Preset", meta = (ClampMin = "-96.0", UIMin = "-96.0", UIMax = "10.0"))
	float VolumeAttenuationDb;

	FSourceEffectLowPassFilterSettings()
		: VolumeAttenuationDb(0.0f)
	{}
};

// ========================================================================
// FSourceEffectLowPassFilter
// This is the instance of the source effect. Performs DSP calculations.
// ========================================================================

class CO2_API FSourceEffectLowPassFilter : public FSoundEffectSource
{
public:
	// Called on an audio effect at initialization on main thread before audio processing begins.
	virtual void Init(const FSoundEffectSourceInitData& InInitData) override;
	
	// Called when an audio effect preset is changed
	virtual void OnPresetChanged() override;

	// Process the input block of audio. Called on audio thread.
	virtual void ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData) override;

protected:
	// Attenuation of sound in linear units
	float VolumeScale;

	int32 NumChannels;
};

// ========================================================================
// USourceEffectLowPassFilterPreset
// This code exposes your preset settings and effect class to the editor.
// And allows for a handle to setting/updating effect settings dynamically.
// ========================================================================

UCLASS(ClassGroup = AudioSourceEffect, meta = (BlueprintSpawnableComponent))
class CO2_API USourceEffectLowPassFilterPreset : public USoundEffectSourcePreset
{
	GENERATED_BODY()

public:
	// Macro which declares and implements useful functions.
	EFFECT_PRESET_METHODS(SourceEffectLowPassFilter)

	// Allows you to customize the color of the preset in the editor.
	virtual FColor GetPresetColor() const override { return FColor(196.0f, 185.0f, 121.0f); }

	// Change settings of your effect from blueprints. Will broadcast changes to active instances.
	UFUNCTION(BlueprintCallable, Category = "Audio|Effects")
	void SetSettings(const FSourceEffectLowPassFilterSettings& InSettings);
	
	// The copy of the settings struct. Can't be written to in BP, but can be read.
	// Note that the value read in BP is the serialized settings, will not reflect dynamic changes made in BP.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio|Effects")
	FSourceEffectLowPassFilterSettings Settings;
};
