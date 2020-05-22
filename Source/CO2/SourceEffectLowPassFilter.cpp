// Fill out your copyright notice in the Description page of Project Settings.


#include "SourceEffectLowPassFilter.h"

// Useful header for various DSP-related utility functions.
#include "DSP/Dsp.h"

void FSourceEffectLowPassFilter::Init(const FSoundEffectSourceInitData& InInitData)
{
	// Use InitData to setup DSP effects that depend on sample rate, etc.
	bIsActive = true;
	VolumeScale = 1.0f;
	NumChannels = InInitData.NumSourceChannels;
}

void FSourceEffectLowPassFilter::OnPresetChanged()
{
	// Macro to retrieve the current settings value of the parent preset asset.
	GET_EFFECT_SETTINGS(SourceEffectLowPassFilter);

	// Update the instance's variables based on the settings values. 
	// Note that Settings variable was created by the GET_EFFECT_SETTINGS macro.
	VolumeScale = Audio::ConvertToLinear(Settings.VolumeAttenuationDb);
}

void FSourceEffectLowPassFilter::ProcessAudio(const FSoundEffectSourceInputData& InData, float* OutAudioBufferData)
{
	// Use the volume scale value to scale the input audio frame data.
	for (int32 Index = 0; Index < InData.NumSamples; ++Index)
	{
		OutAudioBufferData[Index] = VolumeScale * InData.InputSourceEffectBufferPtr[Index];
	}
}

void USourceEffectLowPassFilterPreset::SetSettings(const FSourceEffectLowPassFilterSettings& InSettings)
{
	// Performs necessary broadcast to effect instances
	UpdateSettings(InSettings);
}