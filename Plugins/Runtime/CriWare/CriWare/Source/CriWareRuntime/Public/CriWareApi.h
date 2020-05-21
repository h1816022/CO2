/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2012-2017 CRI Middleware Co., Ltd.
 *
 * Library      : CRIWARE plugin for Unreal Engine 4
 * Module       : Library user's header
 * File         : CriWareApi.h
 * Generator    : CriWareExporterForUE4.exe (Dec 25 2018)
 * Date         : Tue Dec 25 16:15:15 2018
 *
 ****************************************************************************/
#pragma once

/***************************************************************************
 *      Include files
 ***************************************************************************/
#define CRI_XPT_DISABLE_UNPREFIXED_TYPE
#include <CoreTypes.h>
#include <Misc/Build.h>

#if defined(_WIN32) || defined(_WIN64)
#include "AllowWindowsPlatformTypes.h"
#endif
THIRD_PARTY_INCLUDES_START
#include <cri_adx2le.h>
THIRD_PARTY_INCLUDES_END
#if defined(_WIN32) || defined(_WIN64)
#include "HideWindowsPlatformTypes.h"
#endif

#ifndef CRIWARE_USE_ATOM_MONITOR
#if !UE_BUILD_SHIPPING && !defined(XPT_TGT_LINUX)
#define CRIWARE_USE_ATOM_MONITOR	1
#else
#define CRIWARE_USE_ATOM_MONITOR	0
#endif
#endif

/***************************************************************************
 *      Function Types
 ***************************************************************************/
typedef const CriChar8* (CRIAPI *criErr_ConvertIdToMsg_TYPE)(const CriChar8 *errid);
typedef const CriChar8* (CRIAPI *criErr_ConvertIdToMessage_TYPE)(const CriChar8 *errid, CriUint32 p1, CriUint32 p2);
typedef void (CRIAPI *criErr_SetCallback_TYPE)(CriErrCbFunc cbf);
typedef void (CRIAPI *criErr_SetErrorNotificationLevel_TYPE)(CriErrorNotificationLevel level);
typedef CriUint32 (CRIAPI *criErr_GetErrorCount_TYPE)(CriErrorLevel level);
typedef void (CRIAPI *criErr_ResetErrorCount_TYPE)(CriErrorLevel level);
typedef void (CRIAPI *criFs_SetUserMallocFunction_TYPE)(CriFsMallocFunc func, void *obj);
typedef void (CRIAPI *criFs_SetUserFreeFunction_TYPE)(CriFsFreeFunc func, void *obj);
typedef CriError (CRIAPI *criFs_SetSelectIoCallback_TYPE)(CriFsSelectIoCbFunc func);
typedef CriUint32 (CRIAPI *criAtom_GetVersionNumber_TYPE)(void);
typedef CriSint32 (CRIAPI *criAtom_CalculateWorkSize_TYPE)(const CriAtomConfig *config);
typedef void (CRIAPI *criAtom_Initialize_TYPE)(const CriAtomConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtom_Finalize_TYPE)(void);
typedef CriBool (CRIAPI *criAtom_IsInitialized_TYPE)(void);
typedef CriBool (CRIAPI *criAtom_IsAudioOutputActive_TYPE)(void);
typedef void (CRIAPI *criAtom_ExecuteMain_TYPE)(void);
typedef void (CRIAPI *criAtom_ExecuteAudioProcess_TYPE)(void);
typedef void (CRIAPI *criAtom_SetUserMallocFunction_TYPE)(CriAtomMallocFunc func, void *obj);
typedef void (CRIAPI *criAtom_SetUserFreeFunction_TYPE)(CriAtomFreeFunc func, void *obj);
typedef void (CRIAPI *criAtom_SetAudioFrameStartCallback_TYPE)( CriAtomAudioFrameStartCbFunc func, void *obj);
typedef void (CRIAPI *criAtom_SetAudioFrameEndCallback_TYPE)( CriAtomAudioFrameEndCbFunc func, void *obj);
typedef void (CRIAPI *criAtom_Lock_TYPE)(void);
typedef void (CRIAPI *criAtom_Unlock_TYPE)(void);
typedef void (CRIAPI *criAtom_SetChannelMapping_TYPE)(CriSint32 nch, CriUint32 type);
typedef void (CRIAPI *criAtom_AttachPerformanceMonitor_TYPE)(void);
typedef void (CRIAPI *criAtom_DetachPerformanceMonitor_TYPE)(void);
typedef void (CRIAPI *criAtom_ResetPerformanceMonitor_TYPE)(void);
typedef void (CRIAPI *criAtom_GetPerformanceInfo_TYPE)(CriAtomPerformanceInfo *info);
typedef CriSint32 (CRIAPI *criAtom_CalculateAdxBitrate_TYPE)( CriSint32 num_channels, CriSint32 sampling_rate);
typedef CriSint32 (CRIAPI *criAtom_CalculateHcaBitrate_TYPE)( CriSint32 num_channels, CriSint32 sampling_rate, CriAtomEncodeQuality quality);
typedef CriSint32 (CRIAPI *criAtom_CalculateHcaMxBitrate_TYPE)( CriSint32 num_channels, CriSint32 sampling_rate, CriAtomEncodeQuality quality);
typedef CriBool (CRIAPI *criAtom_GetStreamingInfo_TYPE)(CriAtomStreamingInfo* streaming_info);
typedef CriBool (CRIAPI *criAtom_SetFreeTimeBufferingFlagForDefaultDevice_TYPE)(CriBool flag);
typedef CriSint32 (CRIAPI *criAtomHcaMx_CalculateWorkSize_TYPE)(const CriAtomHcaMxConfig *config);
typedef void (CRIAPI *criAtomHcaMx_SetConfigForWorkSizeCalculation_TYPE)(const CriAtomHcaMxConfig *config);
typedef void (CRIAPI *criAtomHcaMx_Initialize_TYPE)( const CriAtomHcaMxConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomHcaMx_Finalize_TYPE)(void);
typedef void (CRIAPI *criAtomHcaMx_SetBusSendLevelByName_TYPE)( CriSint32 mixer_id, const CriChar8* bus_name, CriFloat32 level);
typedef void (CRIAPI *criAtomHcaMx_SetFrequencyRatio_TYPE)(CriSint32 mixer_id, CriFloat32 ratio);
typedef CriSint32 (CRIAPI *criAtomAwb_CalculateWorkSizeForLoadToc_TYPE)(CriSint32 num);
typedef CriAtomAwbHn (CRIAPI *criAtomAwb_LoadToc_TYPE)( CriFsBinderHn binder, const CriChar8 *path, void *work, CriSint32 work_size);
typedef CriAtomAwbHn (CRIAPI *criAtomAwb_LoadTocById_TYPE)( CriFsBinderHn binder, CriUint16 id, void *work, CriSint32 work_size);
typedef CriAtomAwbHn (CRIAPI *criAtomAwb_LoadTocAsync_TYPE)( CriFsBinderHn binder, const CriChar8 *path, void *work, CriSint32 work_size);
typedef CriAtomAwbHn (CRIAPI *criAtomAwb_LoadTocAsyncById_TYPE)( CriFsBinderHn binder, CriUint16 id, void *work, CriSint32 work_size);
typedef CriAtomAwbHn (CRIAPI *criAtomAwb_LoadFromMemory_TYPE)( void *awb_mem, CriSint32 awb_mem_size, void *work, CriSint32 work_size);
typedef CriAtomAwbType (CRIAPI *criAtomAwb_GetType_TYPE)(CriAtomAwbHn awb);
typedef CriBool (CRIAPI *criAtomAwb_GetWaveFileInfo_TYPE)( CriAtomAwbHn awb, CriSint32 id, CriSint64 *offset, CriUint32 *size);
typedef void (CRIAPI *criAtomAwb_GetWaveDataInfo_TYPE)(CriAtomAwbHn awb, CriSint32 id, void **wave_data_start, CriUint32 *size);
typedef CriUint16 (CRIAPI *criAtomAwb_GetNumContents_TYPE)(CriAtomAwbHn awb);
typedef void (CRIAPI *criAtomAwb_Release_TYPE)(CriAtomAwbHn awb);
typedef CriBool (CRIAPI *criAtomAwb_IsReadyToRelease_TYPE)(CriAtomAwbHn awb);
typedef CriAtomAwbStatus (CRIAPI *criAtomAwb_GetStatus_TYPE)(CriAtomAwbHn awb);
typedef CriSint32 (CRIAPI *criAtomPlayer_CalculateWorkSizeForStandardPlayer_TYPE)( const CriAtomStandardPlayerConfig *config);
typedef CriAtomPlayerHn (CRIAPI *criAtomPlayer_CreateStandardPlayer_TYPE)( const CriAtomStandardPlayerConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomPlayer_CalculateWorkSizeForAdxPlayer_TYPE)( const CriAtomAdxPlayerConfig *config);
typedef CriAtomPlayerHn (CRIAPI *criAtomPlayer_CreateAdxPlayer_TYPE)( const CriAtomAdxPlayerConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomPlayer_CalculateWorkSizeForHcaPlayer_TYPE)( const CriAtomHcaPlayerConfig *config);
typedef CriAtomPlayerHn (CRIAPI *criAtomPlayer_CreateHcaPlayer_TYPE)( const CriAtomHcaPlayerConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomPlayer_CalculateWorkSizeForHcaMxPlayer_TYPE)( const CriAtomHcaMxPlayerConfig *config);
typedef CriAtomPlayerHn (CRIAPI *criAtomPlayer_CreateHcaMxPlayer_TYPE)( const CriAtomHcaMxPlayerConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomPlayer_CalculateWorkSizeForWavePlayer_TYPE)( const CriAtomWavePlayerConfig *config);
typedef CriAtomPlayerHn (CRIAPI *criAtomPlayer_CreateWavePlayer_TYPE)( const CriAtomWavePlayerConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomPlayer_CalculateWorkSizeForAiffPlayer_TYPE)( const CriAtomAiffPlayerConfig *config);
typedef CriAtomPlayerHn (CRIAPI *criAtomPlayer_CreateAiffPlayer_TYPE)( const CriAtomAiffPlayerConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomPlayer_CalculateWorkSizeForRawPcmPlayer_TYPE)( const CriAtomRawPcmPlayerConfig *config);
typedef CriAtomPlayerHn (CRIAPI *criAtomPlayer_CreateRawPcmPlayer_TYPE)( const CriAtomRawPcmPlayerConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomPlayer_Destroy_TYPE)(CriAtomPlayerHn player);
typedef void (CRIAPI *criAtomPlayer_SetData_TYPE)( CriAtomPlayerHn player, void *buffer, CriSint32 buffer_size);
typedef void (CRIAPI *criAtomPlayer_SetFile_TYPE)( CriAtomPlayerHn player, CriFsBinderHn binder, const CriChar8 *path);
typedef void (CRIAPI *criAtomPlayer_SetContentId_TYPE)( CriAtomPlayerHn player, CriFsBinderHn binder, CriSint32 id);
typedef void (CRIAPI *criAtomPlayer_SetWaveId_TYPE)( CriAtomPlayerHn player, CriAtomAwbHn awb, CriSint32 id);
typedef void (CRIAPI *criAtomPlayer_SetPreviousDataAgain_TYPE)(CriAtomPlayerHn player);
typedef void (CRIAPI *criAtomPlayer_DeferCallback_TYPE)(CriAtomPlayerHn player);
typedef void (CRIAPI *criAtomPlayer_Start_TYPE)(CriAtomPlayerHn player);
typedef void (CRIAPI *criAtomPlayer_Stop_TYPE)(CriAtomPlayerHn player);
typedef void (CRIAPI *criAtomPlayer_Pause_TYPE)(CriAtomPlayerHn player, CriBool flag);
typedef CriBool (CRIAPI *criAtomPlayer_IsPaused_TYPE)(CriAtomPlayerHn player);
typedef CriAtomPlayerStatus (CRIAPI *criAtomPlayer_GetStatus_TYPE)(CriAtomPlayerHn player);
typedef CriSint32 (CRIAPI *criAtomPlayer_GetNumChannels_TYPE)(CriAtomPlayerHn player);
typedef CriBool (CRIAPI *criAtomPlayer_GetNumPlayedSamples_TYPE)( CriAtomPlayerHn player, CriSint64 *num_played, CriSint32 *sampling_rate);
typedef CriSint64 (CRIAPI *criAtomPlayer_GetDecodedDataSize_TYPE)(CriAtomPlayerHn player);
typedef CriSint64 (CRIAPI *criAtomPlayer_GetNumDecodedSamples_TYPE)(CriAtomPlayerHn player);
typedef CriSint64 (CRIAPI *criAtomPlayer_GetTime_TYPE)(CriAtomPlayerHn player);
typedef CriBool (CRIAPI *criAtomPlayer_GetFormatInfo_TYPE)( CriAtomPlayerHn player, CriAtomFormatInfo *info);
typedef CriSint32 (CRIAPI *criAtomPlayer_GetInputBufferRemainSize_TYPE)(CriAtomPlayerHn player);
typedef CriSint32 (CRIAPI *criAtomPlayer_GetOutputBufferRemainSamples_TYPE)(CriAtomPlayerHn player);
typedef void (CRIAPI *criAtomPlayer_SetStartTime_TYPE)(CriAtomPlayerHn player, CriSint64 start_time_ms);
typedef void (CRIAPI *criAtomPlayer_SetVolume_TYPE)(CriAtomPlayerHn player, CriFloat32 vol);
typedef CriFloat32 (CRIAPI *criAtomPlayer_GetVolume_TYPE)(CriAtomPlayerHn player);
typedef void (CRIAPI *criAtomPlayer_SetChannelVolume_TYPE)( CriAtomPlayerHn player, CriSint32 ch, CriFloat32 vol);
typedef void (CRIAPI *criAtomPlayer_SetSendLevel_TYPE)( CriAtomPlayerHn player, CriSint32 ch, CriAtomSpeakerId spk, CriFloat32 level);
typedef void (CRIAPI *criAtomPlayer_ResetSendLevel_TYPE)(CriAtomPlayerHn player);
typedef void (CRIAPI *criAtomPlayer_SetPanAdx1Compatible_TYPE)( CriAtomPlayerHn player, CriSint32 ch, CriFloat32 pan);
typedef void (CRIAPI *criAtomPlayer_ResetPan_TYPE)(CriAtomPlayerHn player);
typedef void (CRIAPI *criAtomPlayer_SetFrequencyRatio_TYPE)(CriAtomPlayerHn player, CriFloat32 ratio);
typedef void (CRIAPI *criAtomPlayer_SetMaxFrequencyRatio_TYPE)(CriAtomPlayerHn player, CriFloat32 ratio);
typedef void (CRIAPI *criAtomPlayer_LimitLoopCount_TYPE)(CriAtomPlayerHn player, CriSint32 count);
typedef void (CRIAPI *criAtomPlayer_SetHcaMxMixerId_TYPE)(CriAtomPlayerHn player, CriSint32 mixer_id);
typedef void (CRIAPI *criAtomPlayer_SetAsrRackId_TYPE)(CriAtomPlayerHn player, CriSint32 rack_id);
typedef void (CRIAPI *criAtomPlayer_SetRawPcmFormat_TYPE)(CriAtomPlayerHn player, CriAtomPcmFormat pcm_format, CriSint32 num_channels, CriSint32 sampling_rate);
typedef void (CRIAPI *criAtomPlayer_SetDataRequestCallback_TYPE)( CriAtomPlayerHn player, CriAtomPlayerDataRequestCbFunc func, void *obj);
typedef void (CRIAPI *criAtomPlayer_SetStatusChangeCallback_TYPE)( CriAtomPlayerHn player, CriAtomPlayerStatusChangeCbFunc func, void *obj);
typedef void (CRIAPI *criAtomPlayer_SetParameterChangeCallback_TYPE)( CriAtomPlayerHn player, CriAtomPlayerParameterChangeCbFunc func, void *obj);
typedef void (CRIAPI *criAtomPlayer_SetFilterCallback_TYPE)( CriAtomPlayerHn player, CriAtomPlayerFilterCbFunc func, void *obj);
typedef void (CRIAPI *criAtomPlayer_SetLoadRequestCallback_TYPE)( CriAtomPlayerHn player, CriAtomPlayerLoadRequestCbFunc func, void *obj);
typedef void (CRIAPI *criAtomPlayer_SetHcaFormat_TYPE)(CriAtomPlayerHn player, CriSint32 num_channels, CriSint32 sampling_rate, CriSint32 bitrate);
typedef CriSint32 (CRIAPI *criAtomDbas_CalculateWorkSize_TYPE)(const CriAtomDbasConfig *config);
typedef CriAtomDbasId (CRIAPI *criAtomDbas_Create_TYPE)( const CriAtomDbasConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomDbas_Destroy_TYPE)(CriAtomDbasId atom_dbas_id);
typedef CriSint32 (CRIAPI *criAtomDbas_GetStreamingPlayerHandles_TYPE)( CriAtomDbasId dbas_id, CriAtomPlayerHn *players, CriSint32 length);
typedef CriSint32 (CRIAPI *criAtomStreamingCache_CalculateWorkSize_TYPE)( const CriAtomStreamingCacheConfig* config);
typedef CriAtomStreamingCacheId (CRIAPI *criAtomStreamingCache_Create_TYPE)( const CriAtomStreamingCacheConfig* config, void* work, CriSint32 work_size);
typedef void (CRIAPI *criAtomStreamingCache_Destroy_TYPE)(CriAtomStreamingCacheId stm_cache_id);
typedef void (CRIAPI *criAtomStreamingCache_Clear_TYPE)(CriAtomStreamingCacheId cache_id);
typedef CriBool (CRIAPI *criAtomStreamingCache_IsCachedWaveId_TYPE)( CriAtomStreamingCacheId stm_cache_id, CriAtomAwbHn awb, CriSint32 id);
typedef CriBool (CRIAPI *criAtomStreamingCache_IsCachedFile_TYPE)( CriAtomStreamingCacheId stm_cache_id, CriFsBinderHn src_binder, const CriChar8 *path);
typedef CriSint32 (CRIAPI *criAtomMeter_CalculateWorkSizeForLevelMeter_TYPE)( const CriAtomLevelMeterConfig *config);
typedef void (CRIAPI *criAtomMeter_AttachLevelMeter_TYPE)( const CriAtomLevelMeterConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomMeter_DetachLevelMeter_TYPE)(void);
typedef void (CRIAPI *criAtomMeter_GetLevelInfo_TYPE)(CriAtomLevelInfo *info);
typedef CriSint32 (CRIAPI *criAtomMeter_CalculateWorkSizeForLoudnessMeter_TYPE)(const CriAtomLoudnessMeterConfig *config);
typedef void (CRIAPI *criAtomMeter_AttachLoudnessMeter_TYPE)(const CriAtomLoudnessMeterConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomMeter_DetachLoudnessMeter_TYPE)(void);
typedef void (CRIAPI *criAtomMeter_GetLoudnessInfo_TYPE)(CriAtomLoudnessInfo *info);
typedef void (CRIAPI *criAtomMeter_ResetLoudnessMeter_TYPE)(void);
typedef CriSint32 (CRIAPI *criAtomMeter_CalculateWorkSizeForTruePeakMeter_TYPE)(const CriAtomTruePeakMeterConfig *config);
typedef void (CRIAPI *criAtomMeter_AttachTruePeakMeter_TYPE)(const CriAtomTruePeakMeterConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomMeter_DetachTruePeakMeter_TYPE)(void);
typedef void (CRIAPI *criAtomMeter_GetTruePeakInfo_TYPE)(CriAtomTruePeakInfo *info);
typedef void (CRIAPI *criAtomPlayer_SetDecodeCallback_TYPE)( CriAtomPlayerHn player, CriAtomPlayerDecodeCbFunc func, void *obj);
typedef void (CRIAPI *criAtomPlayer_DiscardSamples_TYPE)(CriAtomPlayerHn player, CriSint32 num_discard);
typedef CriSint32 (CRIAPI *criAtomExAsr_CalculateWorkSize_TYPE)(const CriAtomExAsrConfig *config);
typedef void (CRIAPI *criAtomExAsr_SetConfigForWorkSizeCalculation_TYPE)(const CriAtomExAsrConfig *config);
typedef void (CRIAPI *criAtomExAsr_Initialize_TYPE)( const CriAtomExAsrConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExAsr_Finalize_TYPE)(void);
typedef void (CRIAPI *criAtomExAsr_SetBusVolumeByName_TYPE)(const CriChar8* bus_name, CriFloat32 volume);
typedef void (CRIAPI *criAtomExAsr_GetBusVolumeByName_TYPE)(const CriChar8* bus_name, CriFloat32 *volume);
typedef void (CRIAPI *criAtomExAsr_SetBusPan3dByName_TYPE)(const CriChar8* bus_name,  CriFloat32 pan3d_angle, CriFloat32 pan3d_distance, CriFloat32 pan3d_volume);
typedef void (CRIAPI *criAtomExAsr_GetBusPan3dByName_TYPE)(const CriChar8* bus_name,  CriFloat32 *pan3d_angle, CriFloat32 *pan3d_distance, CriFloat32 *pan3d_volume);
typedef void (CRIAPI *criAtomExAsr_SetBusMatrixByName_TYPE)(const CriChar8* bus_name,  CriSint32 input_channels, CriSint32 output_channels, const CriFloat32 matrix[]);
typedef void (CRIAPI *criAtomExAsr_SetBusSendLevelByName_TYPE)( const CriChar8* bus_name, const CriChar8* sendto_bus_name, CriFloat32 level);
typedef void (CRIAPI *criAtomExAsr_SetEffectParameter_TYPE)( const CriChar8* bus_name, const CriChar8* effect_name,  const CriUint32 parameter_index, const CriFloat32 parameter_value);
typedef void (CRIAPI *criAtomExAsr_UpdateEffectParameters_TYPE)(const CriChar8* bus_name, const CriChar8* effect_name);
typedef CriFloat32 (CRIAPI *criAtomExAsr_GetEffectParameter_TYPE)( const CriChar8* bus_name, const CriChar8* effect_name,  const CriUint32 parameter_index);
typedef void (CRIAPI *criAtomExAsr_SetEffectBypass_TYPE)( const CriChar8* bus_name, const CriChar8* effect_name,  const CriBool bypass);
typedef void (CRIAPI *criAtomExAsr_AttachBusAnalyzerByName_TYPE)( const CriChar8* bus_name, const CriAtomExAsrBusAnalyzerConfig* config);
typedef void (CRIAPI *criAtomExAsr_DetachBusAnalyzerByName_TYPE)(const CriChar8* bus_name);
typedef void (CRIAPI *criAtomExAsr_GetBusAnalyzerInfoByName_TYPE)( const CriChar8* bus_name, CriAtomExAsrBusAnalyzerInfo *info);
typedef void (CRIAPI *criAtomExAsr_SetBusFilterCallbackByName_TYPE)(const CriChar8* bus_name,  CriAtomExAsrBusFilterCbFunc pre_func, CriAtomExAsrBusFilterCbFunc post_func, void *obj);
typedef CriSint32 (CRIAPI *criAtomExAsr_GetNumBuses_TYPE)(void);
typedef CriBool (CRIAPI *criAtomExAsr_RegisterEffectInterface_TYPE)(CriAtomExAsrAfxInterfaceWithVersionPtr afx_interface);
typedef void (CRIAPI *criAtomExAsr_UnregisterEffectInterface_TYPE)(CriAtomExAsrAfxInterfaceWithVersionPtr afx_interface);
typedef CriSint32 (CRIAPI *criAtomExAsrRack_CalculateWorkSize_TYPE)(const CriAtomExAsrRackConfig *config);
typedef CriSint32 (CRIAPI *criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromConfig_TYPE)( const CriAtomExAsrRackConfig *config, const CriChar8 *setting);
typedef CriSint32 (CRIAPI *criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromAcfDataAndConfig_TYPE)( void *acf_data, CriSint32 acf_data_size, const CriAtomExAsrRackConfig *rack_config, const CriChar8 *setting);
typedef CriAtomExAsrRackId (CRIAPI *criAtomExAsrRack_Create_TYPE)( const CriAtomExAsrRackConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExAsrRack_Destroy_TYPE)(CriAtomExAsrRackId rack_id);
typedef CriSint32 (CRIAPI *criAtomExAsrRack_CalculateWorkSizeForDspBusSetting_TYPE)( CriAtomExAsrRackId rack_id, const CriChar8 *setting);
typedef void (CRIAPI *criAtomExAsrRack_AttachDspBusSetting_TYPE)(CriAtomExAsrRackId rack_id, const CriChar8 *setting, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExAsrRack_DetachDspBusSetting_TYPE)(CriAtomExAsrRackId rack_id);
typedef void (CRIAPI *criAtomExAsrRack_ApplyDspBusSnapshot_TYPE)(CriAtomExAsrRackId rack_id, const CriChar8 *snapshot_name, CriSint32 time_ms);
typedef const CriChar8* (CRIAPI *criAtomExAsrRack_GetAppliedDspBusSnapshotName_TYPE)(CriAtomExAsrRackId rack_id);
typedef void (CRIAPI *criAtomExAsrRack_SetBusVolumeByName_TYPE)(CriAtomExAsrRackId rack_id,  const CriChar8* bus_name, CriFloat32 volume);
typedef void (CRIAPI *criAtomExAsrRack_GetBusVolumeByName_TYPE)(CriAtomExAsrRackId rack_id,  const CriChar8* bus_name, CriFloat32* volume);
typedef void (CRIAPI *criAtomExAsrRack_SetBusPan3dByName_TYPE)(CriAtomExAsrRackId rack_id, const CriChar8* bus_name,  CriFloat32 pan3d_angle, CriFloat32 pan3d_distance, CriFloat32 pan3d_volume);
typedef void (CRIAPI *criAtomExAsrRack_GetBusPan3dByName_TYPE)(CriAtomExAsrRackId rack_id, const CriChar8* bus_name,  CriFloat32 *pan3d_angle, CriFloat32 *pan3d_distance, CriFloat32 *pan3d_volume);
typedef void (CRIAPI *criAtomExAsrRack_SetBusMatrixByName_TYPE)( CriAtomExAsrRackId rack_id, const CriChar8* bus_name, CriSint32 input_channels,  CriSint32 output_channels, const CriFloat32 matrix[]);
typedef void (CRIAPI *criAtomExAsrRack_SetBusSendLevelByName_TYPE)(CriAtomExAsrRackId rack_id, const CriChar8* bus_name, const CriChar8* sendto_bus_name, CriFloat32 level);
typedef void (CRIAPI *criAtomExAsrRack_SetEffectParameter_TYPE)(CriAtomExAsrRackId rack_id, const CriChar8* bus_name, const CriChar8* effect_name,  const CriUint32 parameter_index, const CriFloat32 parameter_value);
typedef void (CRIAPI *criAtomExAsrRack_UpdateEffectParameters_TYPE)(CriAtomExAsrRackId rack_id, const CriChar8* bus_name, const CriChar8* effect_name);
typedef CriFloat32 (CRIAPI *criAtomExAsrRack_GetEffectParameter_TYPE)(CriAtomExAsrRackId rack_id, const CriChar8* bus_name, const CriChar8* effect_name,  const CriUint32 parameter_index);
typedef void (CRIAPI *criAtomExAsrRack_SetEffectBypass_TYPE)(CriAtomExAsrRackId rack_id, const CriChar8* bus_name, const CriChar8* effect_name, const CriBool bypass);
typedef void (CRIAPI *criAtomExAsrRack_AttachBusAnalyzerByName_TYPE)(CriAtomExAsrRackId rack_id,  const CriChar8* bus_name, const CriAtomExAsrBusAnalyzerConfig* config);
typedef void (CRIAPI *criAtomExAsrRack_DetachBusAnalyzerByName_TYPE)( CriAtomExAsrRackId rack_id, const CriChar8* bus_name);
typedef void (CRIAPI *criAtomExAsrRack_GetBusAnalyzerInfoByName_TYPE)(CriAtomExAsrRackId rack_id,  const CriChar8* bus_name, CriAtomExAsrBusAnalyzerInfo *info);
typedef void (CRIAPI *criAtomExAsrRack_SetBusFilterCallbackByName_TYPE)(CriAtomExAsrRackId rack_id,  const CriChar8* bus_name, CriAtomExAsrBusFilterCbFunc pre_func,  CriAtomExAsrBusFilterCbFunc post_func, void *obj);
typedef void (CRIAPI *criAtomExAsrRack_SetAlternateRackId_TYPE)( CriAtomExAsrRackId rack_id, CriAtomExAsrRackId alt_rack_id);
typedef CriSint32 (CRIAPI *criAtomExAsrRack_GetNumBuses_TYPE)(CriAtomExAsrRackId rack_id);
typedef CriSint32 (CRIAPI *criAtomExAsr_GetPcmDataFloat32_TYPE)( CriSint32 output_channels, CriSint32 output_samples, CriFloat32 *output_buffer[]);
typedef CriSint32 (CRIAPI *criAtomExAsr_GetNumBufferedSamples_TYPE)(void);
typedef void (CRIAPI *criAtomExAsr_SetPcmBufferSize_TYPE)(CriSint32 num_samples);
typedef CriSint32 (CRIAPI *criAtomAsr_CalculateWorkSize_TYPE)(const CriAtomAsrConfig *config);
typedef void (CRIAPI *criAtomAsr_Initialize_TYPE)( const CriAtomAsrConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomAsr_Finalize_TYPE)(void);
typedef CriSint32 (CRIAPI *criAtomEx_CalculateWorkSizeForUserPcmOutput_TYPE)( const CriAtomExConfigForUserPcmOutput *config);
typedef void (CRIAPI *criAtomEx_InitializeForUserPcmOutput_TYPE)( const CriAtomExConfigForUserPcmOutput *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExAsr_PauseOutputVoice_TYPE)(CriBool sw);
typedef CriBool (CRIAPI *criAtomExAsrRack_GetNumOutputSamples_TYPE)( CriAtomExAsrRackId rack_id, CriSint64 *num_samples, CriSint32 *sampling_rate);
typedef CriSint32 (CRIAPI *criAtomExAsrRack_GetOutputChannels_TYPE)(CriAtomExAsrRackId rack_id);
typedef CriUint16 (CRIAPI *criAtomExAsrRack_GetBusNumber_TYPE)( CriAtomExAsrRackId rack_id, const CriChar8 *bus_name);
typedef void (CRIAPI *criAtomAsr_PauseOutputVoice_TYPE)(CriBool sw);
typedef CriSint32 (CRIAPI *criAtomExAsrRack_GetAmbisonicRackId_TYPE)(void);
typedef void (CRIAPI *criAtomExAsr_SetDspParameter_TYPE)( CriSint32 bus_no, CriAtomExAsrDspId dsp_id, const void* parameter);
typedef void (CRIAPI *criAtomExAsr_SetDspParameterByName_TYPE)( const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, const void* parameter);
typedef void (CRIAPI *criAtomExAsr_GetDspParameter_TYPE)( CriSint32 bus_no, CriAtomExAsrDspId dsp_id, void* parameter_buf, CriSint32 parameter_size);
typedef void (CRIAPI *criAtomExAsr_GetDspParameterByName_TYPE)( const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, void* parameter_buf, CriSint32 parameter_size);
typedef void (CRIAPI *criAtomExAsr_SetDspBypass_TYPE)( CriSint32 bus_no, CriAtomExAsrDspId dsp_id, CriBool bypass);
typedef void (CRIAPI *criAtomExAsr_SetDspBypassByName_TYPE)( const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, CriBool bypass);
typedef void (CRIAPI *criAtomExAsr_SetBusVolume_TYPE)(CriSint32 bus_no, CriFloat32 volume);
typedef void (CRIAPI *criAtomExAsr_GetBusVolume_TYPE)(CriSint32 bus_no, CriFloat32 *volume);
typedef void (CRIAPI *criAtomExAsr_SetBusPan3d_TYPE)(CriSint32 bus_no,  CriFloat32 pan3d_angle, CriFloat32 pan3d_distance, CriFloat32 pan3d_volume);
typedef void (CRIAPI *criAtomExAsr_GetBusPan3d_TYPE)(CriSint32 bus_no,  CriFloat32 *pan3d_angle, CriFloat32 *pan3d_distance, CriFloat32 *pan3d_volume);
typedef void (CRIAPI *criAtomExAsr_SetBusMatrix_TYPE)(CriSint32 bus_no,  CriSint32 input_channels, CriSint32 output_channels, const CriFloat32 matrix[]);
typedef void (CRIAPI *criAtomExAsr_SetBusSendLevel_TYPE)( CriSint32 bus_no, CriSint32 sendto_no, CriFloat32 level);
typedef void (CRIAPI *criAtomExAsr_AttachBusAnalyzer_TYPE)( CriSint32 bus_no, const CriAtomExAsrBusAnalyzerConfig* config);
typedef void (CRIAPI *criAtomExAsr_DetachBusAnalyzer_TYPE)(CriSint32 bus_no);
typedef void (CRIAPI *criAtomExAsr_GetBusAnalyzerInfo_TYPE)( CriSint32 bus_no, CriAtomExAsrBusAnalyzerInfo *info);
typedef void (CRIAPI *criAtomExAsr_SetBusFilterCallback_TYPE)(CriSint32 bus_no,  CriAtomExAsrBusFilterCbFunc pre_func, CriAtomExAsrBusFilterCbFunc post_func, void *obj);
typedef void (CRIAPI *criAtomExAsrRack_SetDspParameter_TYPE)(CriAtomExAsrRackId rack_id,  CriSint32 bus_no, CriAtomExAsrDspId dsp_id, const void* parameter);
typedef void (CRIAPI *criAtomExAsrRack_SetDspParameterByName_TYPE)(CriAtomExAsrRackId rack_id,  const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, const void* parameter);
typedef void (CRIAPI *criAtomExAsrRack_GetDspParameter_TYPE)(CriAtomExAsrRackId rack_id,  CriSint32 bus_no, CriAtomExAsrDspId dsp_id, void* parameter_buf, CriSint32 parameter_size);
typedef void (CRIAPI *criAtomExAsrRack_GetDspParameterByName_TYPE)(CriAtomExAsrRackId rack_id,  const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, void* parameter_buf, CriSint32 parameter_size);
typedef void (CRIAPI *criAtomExAsrRack_SetDspBypass_TYPE)(CriAtomExAsrRackId rack_id,  CriSint32 bus_no, CriAtomExAsrDspId dsp_id, CriBool bypass);
typedef void (CRIAPI *criAtomExAsrRack_SetDspBypassByName_TYPE)(CriAtomExAsrRackId rack_id,  const CriChar8* bus_name, CriAtomExAsrDspId dsp_id, CriBool bypass);
typedef void (CRIAPI *criAtomExAsrRack_SetBusVolume_TYPE)(CriAtomExAsrRackId rack_id,  CriSint32 bus_no, CriFloat32 volume);
typedef void (CRIAPI *criAtomExAsrRack_GetBusVolume_TYPE)(CriAtomExAsrRackId rack_id,  CriSint32 bus_no, CriFloat32* volume);
typedef void (CRIAPI *criAtomExAsrRack_SetBusPan3d_TYPE)(CriAtomExAsrRackId rack_id, CriSint32 bus_no,  CriFloat32 pan3d_angle, CriFloat32 pan3d_distance, CriFloat32 pan3d_volume);
typedef void (CRIAPI *criAtomExAsrRack_GetBusPan3d_TYPE)(CriAtomExAsrRackId rack_id, CriSint32 bus_no,  CriFloat32 *pan3d_angle, CriFloat32 *pan3d_distance, CriFloat32 *pan3d_volume);
typedef void (CRIAPI *criAtomExAsrRack_SetBusMatrix_TYPE)( CriAtomExAsrRackId rack_id, CriSint32 bus_no, CriSint32 input_channels,  CriSint32 output_channels, const CriFloat32 matrix[]);
typedef void (CRIAPI *criAtomExAsrRack_SetBusSendLevel_TYPE)(CriAtomExAsrRackId rack_id, CriSint32 bus_no, CriSint32 sendto_no, CriFloat32 level);
typedef void (CRIAPI *criAtomExAsrRack_AttachBusAnalyzer_TYPE)(CriAtomExAsrRackId rack_id,  CriSint32 bus_no, const CriAtomExAsrBusAnalyzerConfig* config);
typedef void (CRIAPI *criAtomExAsrRack_DetachBusAnalyzer_TYPE)( CriAtomExAsrRackId rack_id, CriSint32 bus_no);
typedef void (CRIAPI *criAtomExAsrRack_GetBusAnalyzerInfo_TYPE)(CriAtomExAsrRackId rack_id,  CriSint32 bus_no, CriAtomExAsrBusAnalyzerInfo *info);
typedef void (CRIAPI *criAtomExAsrRack_SetBusFilterCallback_TYPE)(CriAtomExAsrRackId rack_id,  CriSint32 bus_no, CriAtomExAsrBusFilterCbFunc pre_func,  CriAtomExAsrBusFilterCbFunc post_func, void *obj);
typedef CriSint32 (CRIAPI *criAtomEx_CalculateWorkSize_TYPE)(const CriAtomExConfig *config);
typedef CriBool (CRIAPI *criAtomEx_Initialize_TYPE)( const CriAtomExConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomEx_Finalize_TYPE)(void);
typedef CriBool (CRIAPI *criAtomEx_IsInitialized_TYPE)(void);
typedef void (CRIAPI *criAtomEx_ExecuteMain_TYPE)(void);
typedef void (CRIAPI *criAtomEx_ExecuteAudioProcess_TYPE)(void);
typedef void (CRIAPI *criAtomEx_Lock_TYPE)(void);
typedef void (CRIAPI *criAtomEx_Unlock_TYPE)(void);
typedef CriUint64 (CRIAPI *criAtomEx_GetTimeMicro_TYPE)(void);
typedef void (CRIAPI *criAtomEx_ResetTimer_TYPE)(void);
typedef void (CRIAPI *criAtomEx_PauseTimer_TYPE)(CriBool sw);
typedef void (CRIAPI *criAtomEx_SetConfigForWorkSizeCalculation_TYPE)(const CriAtomExConfig *config);
typedef CriSint32 (CRIAPI *criAtomEx_CalculateWorkSizeForRegisterAcfData_TYPE)( void *acf_data, CriSint32 acf_data_size);
typedef void (CRIAPI *criAtomEx_RegisterAcfData_TYPE)( void *acf_data, CriSint32 acf_data_size, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomEx_CalculateWorkSizeForRegisterAcfFile_TYPE)( CriFsBinderHn binder, const CriChar8 *path);
typedef CriSint32 (CRIAPI *criAtomEx_CalculateWorkSizeForRegisterAcfFileById_TYPE)( CriFsBinderHn binder, CriUint16 id);
typedef CriBool (CRIAPI *criAtomEx_RegisterAcfFile_TYPE)( CriFsBinderHn binder, const CriChar8 *path, void *work, CriSint32 work_size);
typedef CriBool (CRIAPI *criAtomEx_RegisterAcfFileById_TYPE)( CriFsBinderHn binder, CriUint16 id, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomEx_UnregisterAcf_TYPE)(void);
typedef CriUint32 (CRIAPI *criAtomEx_GetAcfVersion_TYPE)( void *acf_data, CriSint32 acf_data_size, CriBool *flag);
typedef CriUint32 (CRIAPI *criAtomEx_GetAcfVersionFromFile_TYPE)( CriFsBinderHn binder, const CriChar8 *path, void *work, CriSint32 work_size, CriBool *flag);
typedef CriUint32 (CRIAPI *criAtomEx_GetAcfVersionFromFileById_TYPE)( CriFsBinderHn binder, CriUint16 id, void *work, CriSint32 work_size, CriBool *flag);
typedef void (CRIAPI *criAtomEx_GetSupportedAcfVersion_TYPE)( CriUint32 *version_low, CriUint32 *version_high);
typedef CriBool (CRIAPI *criAtomEx_AnalyzeAudioHeader_TYPE)( const void *buffer, CriSint32 buffer_size, CriAtomExFormatInfo *info);
typedef void (CRIAPI *criAtomEx_SetRandomSeed_TYPE)(CriUint32 seed);
typedef CriBool (CRIAPI *criAtomEx_IsDataPlaying_TYPE)(void *buffer, CriSint32 size);
typedef CriSint32 (CRIAPI *criAtomEx_CalculateWorkSizeForDspBusSetting_TYPE)( const CriChar8 *setting);
typedef CriSint32 (CRIAPI *criAtomEx_CalculateWorkSizeForDspBusSettingFromAcfData_TYPE)( void *acf_data, CriSint32 acf_buffer_size, const CriChar8 *setting_name);
typedef void (CRIAPI *criAtomEx_AttachDspBusSetting_TYPE)( const CriChar8 *setting, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomEx_DetachDspBusSetting_TYPE)(void);
typedef void (CRIAPI *criAtomEx_ApplyDspBusSnapshot_TYPE)(const CriChar8 *snapshot_name, CriSint32 time_ms);
typedef const CriChar8* (CRIAPI *criAtomEx_GetAppliedDspBusSnapshotName_TYPE)(void);
typedef void (CRIAPI *criAtomEx_SetCueLinkCallback_TYPE)(CriAtomExCueLinkCbFunc func, void* obj);
typedef void (CRIAPI *criAtomEx_SetSpeakerAngles_TYPE)(CriFloat32 angle_l, CriFloat32 angle_r, CriFloat32 angle_sl, CriFloat32 angle_sr);
typedef void (CRIAPI *criAtomEx_SetSpeakerAngleArray_TYPE)(CriAtomExSpeakerSystem speaker_system, const CriFloat32 *angle_array);
typedef void (CRIAPI *criAtomEx_SetVirtualSpeakerAngleArray_TYPE)(CriAtomExSpeakerSystem speaker_system, const CriFloat32 *angle_array);
typedef void (CRIAPI *criAtomEx_ControlVirtualSpeakerSetting_TYPE)(CriBool sw);
typedef CriSint32 (CRIAPI *criAtomEx_GetNumGameVariables_TYPE)(void);
typedef CriBool (CRIAPI *criAtomEx_GetGameVariableInfo_TYPE)(CriUint16 index, CriAtomExGameVariableInfo* info);
typedef CriFloat32 (CRIAPI *criAtomEx_GetGameVariableById_TYPE)(CriAtomExGameVariableId id);
typedef CriFloat32 (CRIAPI *criAtomEx_GetGameVariableByName_TYPE)(const CriChar8* name);
typedef void (CRIAPI *criAtomEx_SetGameVariableById_TYPE)(CriAtomExGameVariableId id, CriFloat32 value);
typedef void (CRIAPI *criAtomEx_SetGameVariableByName_TYPE)(const CriChar8* name, CriFloat32 value);
typedef void (CRIAPI *criAtomEx_SetPlaybackCancelCallback_TYPE)(CriAtomExPlaybackCancelCbFunc func, void* obj);
typedef void (CRIAPI *criAtomEx_ControlAcfConsistencyCheck_TYPE)(CriBool sw);
typedef void (CRIAPI *criAtomEx_SetAcfConsistencyCheckErrorLevel_TYPE)(CriErrorLevel level);
typedef void (CRIAPI *criAtomEx_SetTrackTransitionBySelectorCallback_TYPE)(CriAtomExTrackTransitionBySelectorCbFunc func, void* obj);
typedef void (CRIAPI *criAtomExDebug_GetResourcesInfo_TYPE)(CriAtomExDebugResourcesInfo *resources_info);
typedef CriSint32 (CRIAPI *criAtomExHcaMx_CalculateWorkSize_TYPE)(const CriAtomExHcaMxConfig *config);
typedef void (CRIAPI *criAtomExHcaMx_SetConfigForWorkSizeCalculation_TYPE)(const CriAtomExHcaMxConfig *config);
typedef void (CRIAPI *criAtomExHcaMx_Initialize_TYPE)( const CriAtomExHcaMxConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExHcaMx_Finalize_TYPE)(void);
typedef void (CRIAPI *criAtomExHcaMx_SetBusSendLevelByName_TYPE)( CriSint32 mixer_id, const CriChar8* bus_name, CriFloat32 level);
typedef void (CRIAPI *criAtomExHcaMx_SetFrequencyRatio_TYPE)(CriSint32 mixer_id, CriFloat32 ratio);
typedef void (CRIAPI *criAtomExHcaMx_SetAsrRackId_TYPE)(CriSint32 mixer_id, CriSint32 rack_id);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetNumAisacControls_TYPE)(void);
typedef CriBool (CRIAPI *criAtomExAcf_GetAisacControlInfo_TYPE)(CriUint16 index, CriAtomExAisacControlInfo* info);
typedef CriAtomExAisacControlId (CRIAPI *criAtomExAcf_GetAisacControlIdByName_TYPE)(const CriChar8* name);
typedef const CriChar8 * (CRIAPI *criAtomExAcf_GetAisacControlNameById_TYPE)(CriAtomExAisacControlId id);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetNumDspSettings_TYPE)(void);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetNumDspSettingsFromAcfData_TYPE)( void *acf_data, CriSint32 acf_data_size);
typedef const CriChar8 * (CRIAPI *criAtomExAcf_GetDspSettingNameByIndex_TYPE)(CriUint16 index);
typedef const CriChar8 * (CRIAPI *criAtomExAcf_GetDspSettingNameByIndexFromAcfData_TYPE)( void *acf_data, CriSint32 acf_data_size, CriUint16 index);
typedef CriBool (CRIAPI *criAtomExAcf_GetDspSettingInformation_TYPE)(const CriChar8* name, CriAtomExAcfDspSettingInfo* info);
typedef CriBool (CRIAPI *criAtomExAcf_GetDspSettingSnapshotInformation_TYPE)(CriUint16 index, CriAtomExAcfDspSettingSnapshotInfo* info);
typedef CriBool (CRIAPI *criAtomExAcf_GetDspBusInformation_TYPE)(CriUint16 index, CriAtomExAcfDspBusInfo* info);
typedef CriUint32 (CRIAPI *criAtomExAcf_GetDspFxType_TYPE)(CriUint16 index);
typedef const CriChar8* (CRIAPI *criAtomExAcf_GetDspFxName_TYPE)(CriUint16 index);
typedef CriBool (CRIAPI *criAtomExAcf_GetDspFxParameters_TYPE)(CriUint16 index, void* parameters, CriSint32 size);
typedef CriBool (CRIAPI *criAtomExAcf_GetDspBusLinkInformation_TYPE)(CriUint16 index, CriAtomExAcfDspBusLinkInfo* info);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetNumCategoriesFromAcfData_TYPE)( void *acf_data, CriSint32 acf_data_size);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetNumCategories_TYPE)(void);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetNumCategoriesPerPlaybackFromAcfData_TYPE)( void *acf_data, CriSint32 acf_data_size);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetNumCategoriesPerPlayback_TYPE)(void);
typedef CriBool (CRIAPI *criAtomExAcf_GetCategoryInfo_TYPE)(CriUint16 index, CriAtomExCategoryInfo* info);
typedef CriBool (CRIAPI *criAtomExAcf_GetCategoryInfoByName_TYPE)(const CriChar8* name, CriAtomExCategoryInfo* info);
typedef CriBool (CRIAPI *criAtomExAcf_GetCategoryInfoById_TYPE)(CriUint32 id, CriAtomExCategoryInfo* info);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetNumGlobalAisacs_TYPE)(void);
typedef CriBool (CRIAPI *criAtomExAcf_GetGlobalAisacInfo_TYPE)(CriUint16 index, CriAtomExGlobalAisacInfo* info);
typedef CriBool (CRIAPI *criAtomExAcf_GetGlobalAisacInfoByName_TYPE)(const CriChar8* name, CriAtomExGlobalAisacInfo* info);
typedef CriBool (CRIAPI *criAtomExAcf_GetGlobalAisacGraphInfo_TYPE)( const CriAtomExGlobalAisacInfo* aisac_info, CriUint16 graph_index, CriAtomExAisacGraphInfo* graph_info);
typedef CriBool (CRIAPI *criAtomExAcf_GetGlobalAisacValue_TYPE)( const CriAtomExGlobalAisacInfo* aisac_info, CriFloat32 control, CriAtomExAisacGraphType type, CriFloat32* value);
typedef CriBool (CRIAPI *criAtomExAcf_GetAcfInfo_TYPE)(CriAtomExAcfInfo *acf_info);
typedef CriBool (CRIAPI *criAtomExAcf_GetAcfInfoFromAcfData_TYPE)( void *acf_data, CriSint32 acf_data_size, CriAtomExAcfInfo *acf_info);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetNumSelectors_TYPE)(void);
typedef CriBool (CRIAPI *criAtomExAcf_GetSelectorInfoByIndex_TYPE)(CriUint16 index, CriAtomExSelectorInfo* info);
typedef CriBool (CRIAPI *criAtomExAcf_GetSelectorInfoByName_TYPE)(const CriChar8* name, CriAtomExSelectorInfo* info);
typedef CriBool (CRIAPI *criAtomExAcf_GetSelectorLabelInfo_TYPE)( const CriAtomExSelectorInfo* selector_info, CriUint16 label_index, CriAtomExSelectorLabelInfo* label_info);
typedef void (CRIAPI *criAtomExAcf_SetGlobalLabelToSelectorByName_TYPE)(const CriChar8* selsector_name, const CriChar8* label_name);
typedef void (CRIAPI *criAtomExAcf_SetGlobalLabelToSelectorByIndex_TYPE)(CriUint16 selsector_index, CriUint16 label_index);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetNumBusesFromAcfData_TYPE)( void *acf_data, CriSint32 acf_data_size);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetNumBuses_TYPE)(void);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetMaxBusesOfDspBusSettingsFromAcfData_TYPE)( void *acf_data, CriSint32 acf_data_size);
typedef CriSint32 (CRIAPI *criAtomExAcf_GetMaxBusesOfDspBusSettings_TYPE)(void);
typedef const CriChar8* (CRIAPI *criAtomExAcf_FindBusName_TYPE)(const CriChar8* bus_name);
typedef CriSint32 (CRIAPI *criAtomExAcb_CalculateWorkSizeForLoadAcbData_TYPE)( void *acb_data, CriSint32 acb_data_size, CriFsBinderHn awb_binder, const CriChar8 *awb_path);
typedef CriSint32 (CRIAPI *criAtomExAcb_CalculateWorkSizeForLoadAcbDataById_TYPE)( void *acb_data, CriSint32 acb_data_size, CriFsBinderHn awb_binder, CriUint16 awb_id);
typedef CriAtomExAcbHn (CRIAPI *criAtomExAcb_LoadAcbData_TYPE)( void *acb_data, CriSint32 acb_data_size, CriFsBinderHn awb_binder, const CriChar8 *awb_path, void *work, CriSint32 work_size);
typedef CriAtomExAcbHn (CRIAPI *criAtomExAcb_LoadAcbDataById_TYPE)( void *acb_data, CriSint32 acb_data_size, CriFsBinderHn awb_binder, CriUint16 awb_id, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomExAcb_CalculateWorkSizeForLoadAcbFile_TYPE)( CriFsBinderHn acb_binder, const CriChar8 *acb_path, CriFsBinderHn awb_binder, const CriChar8 *awb_path);
typedef CriSint32 (CRIAPI *criAtomExAcb_CalculateWorkSizeForLoadAcbFileById_TYPE)( CriFsBinderHn acb_binder, CriUint16 acb_id, CriFsBinderHn awb_binder, CriUint16 awb_id);
typedef CriAtomExAcbHn (CRIAPI *criAtomExAcb_LoadAcbFile_TYPE)( CriFsBinderHn acb_binder, const CriChar8 *acb_path, CriFsBinderHn awb_binder, const CriChar8 *awb_path, void *work, CriSint32 work_size);
typedef CriAtomExAcbHn (CRIAPI *criAtomExAcb_LoadAcbFileById_TYPE)( CriFsBinderHn acb_binder, CriUint16 acb_id, CriFsBinderHn awb_binder, CriUint16 awb_id, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExAcb_Release_TYPE)(CriAtomExAcbHn acb_hn);
typedef CriBool (CRIAPI *criAtomExAcb_IsReadyToRelease_TYPE)(CriAtomExAcbHn acb_hn);
typedef void (CRIAPI *criAtomExAcb_ReleaseAll_TYPE)(void);
typedef CriSint32 (CRIAPI *criAtomExAcb_EnumerateHandles_TYPE)(CriAtomExAcbHandleCbFunc func, void *obj);
typedef CriUint32 (CRIAPI *criAtomExAcb_GetVersion_TYPE)( void *acb_data, CriSint32 acb_data_size, void *flag);
typedef CriUint32 (CRIAPI *criAtomExAcb_GetVersionFromFile_TYPE)( CriFsBinderHn acb_binder, const CriChar8 *acb_path, void *work, CriSint32 work_size, CriBool *flag);
typedef void (CRIAPI *criAtomExAcb_GetSupportedVersion_TYPE)( CriUint32 *version_low, CriUint32 *version_high);
typedef CriSint32 (CRIAPI *criAtomExAcb_GetNumCues_TYPE)(CriAtomExAcbHn acb_hn);
typedef CriBool (CRIAPI *criAtomExAcb_ExistsId_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id);
typedef CriBool (CRIAPI *criAtomExAcb_ExistsName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8 *name);
typedef CriBool (CRIAPI *criAtomExAcb_ExistsIndex_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);
typedef CriAtomExCueId (CRIAPI *criAtomExAcb_GetCueIdByIndex_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);
typedef CriAtomExCueId (CRIAPI *criAtomExAcb_GetCueIdByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8* name);
typedef const CriChar8 * (CRIAPI *criAtomExAcb_GetCueNameByIndex_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);
typedef const CriChar8 * (CRIAPI *criAtomExAcb_GetCueNameById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id);
typedef CriAtomExCueIndex (CRIAPI *criAtomExAcb_GetCueIndexById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id);
typedef CriAtomExCueIndex (CRIAPI *criAtomExAcb_GetCueIndexByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8* name);
typedef const CriChar8 * (CRIAPI *criAtomExAcb_GetUserDataById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id);
typedef const CriChar8 * (CRIAPI *criAtomExAcb_GetUserDataByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8 *name);
typedef CriSint64 (CRIAPI *criAtomExAcb_GetLengthById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id);
typedef CriSint64 (CRIAPI *criAtomExAcb_GetLengthByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8 *name);
typedef CriSint32 (CRIAPI *criAtomExAcb_GetNumUsableAisacControlsById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id);
typedef CriSint32 (CRIAPI *criAtomExAcb_GetNumUsableAisacControlsByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8 *name);
typedef CriBool (CRIAPI *criAtomExAcb_GetUsableAisacControlById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id, CriUint16 index, CriAtomExAisacControlInfo* info);
typedef CriBool (CRIAPI *criAtomExAcb_GetUsableAisacControlByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8 *name, CriUint16 index, CriAtomExAisacControlInfo* info);
typedef CriBool (CRIAPI *criAtomExAcb_IsUsingAisacControlById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id, CriAtomExAisacControlId aisac_control_id);
typedef CriBool (CRIAPI *criAtomExAcb_IsUsingAisacControlByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8 *name, const CriChar8 *aisac_control_name);
typedef CriSint32 (CRIAPI *criAtomExAcb_GetCuePriorityById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id);
typedef CriSint32 (CRIAPI *criAtomExAcb_GetCuePriorityByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8 *name);
typedef CriBool (CRIAPI *criAtomExAcb_GetWaveformInfoById_TYPE)( CriAtomExAcbHn acb_hn, CriAtomExCueId id, CriAtomExWaveformInfo *waveform_info);
typedef CriBool (CRIAPI *criAtomExAcb_GetWaveformInfoByName_TYPE)( CriAtomExAcbHn acb_hn, const CriChar8 *name, CriAtomExWaveformInfo *waveform_info);
typedef CriAtomAwbHn (CRIAPI *criAtomExAcb_GetOnMemoryAwbHandle_TYPE)(CriAtomExAcbHn acb_hn);
typedef CriAtomAwbHn (CRIAPI *criAtomExAcb_GetStreamingAwbHandle_TYPE)(CriAtomExAcbHn acb_hn);
typedef CriBool (CRIAPI *criAtomExAcb_GetCueInfoByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8* name, CriAtomExCueInfo* info);
typedef CriBool (CRIAPI *criAtomExAcb_GetCueInfoById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id, CriAtomExCueInfo* info);
typedef CriBool (CRIAPI *criAtomExAcb_GetCueInfoByIndex_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index, CriAtomExCueInfo* info);
typedef CriSint32 (CRIAPI *criAtomExAcb_GetNumCuePlayingCountByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8* name);
typedef CriSint32 (CRIAPI *criAtomExAcb_GetNumCuePlayingCountById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id);
typedef CriSint32 (CRIAPI *criAtomExAcb_GetNumCuePlayingCountByIndex_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);
typedef CriAtomExBlockIndex (CRIAPI *criAtomExAcb_GetBlockIndexByIndex_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index, const CriChar8* block_name);
typedef CriAtomExBlockIndex (CRIAPI *criAtomExAcb_GetBlockIndexById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id, const CriChar8* block_name);
typedef CriAtomExBlockIndex (CRIAPI *criAtomExAcb_GetBlockIndexByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8* name, const CriChar8* block_name);
typedef void (CRIAPI *criAtomExAcb_SetDetectionInGamePreviewDataCallback_TYPE)(CriAtomExAcbDetectionInGamePreviewDataCbFunc func, void* obj);
typedef CriBool (CRIAPI *criAtomExAcb_GetAcbInfo_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExAcbInfo *acb_info);
typedef void (CRIAPI *criAtomExAcb_ResetCueTypeStateByName_TYPE)(CriAtomExAcbHn acb_hn, const CriChar8* name);
typedef void (CRIAPI *criAtomExAcb_ResetCueTypeStateById_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueId id);
typedef void (CRIAPI *criAtomExAcb_ResetCueTypeStateByIndex_TYPE)(CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);
typedef void (CRIAPI *criAtomExAcb_AttachAwbFile_TYPE)( CriAtomExAcbHn acb_hn, CriFsBinderHn awb_binder, const CriChar8* awb_path, const CriChar8* awb_name, void* work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExAcb_DetachAwbFile_TYPE)( CriAtomExAcbHn acb_hn, const CriChar8* awb_name);
typedef CriSint32 (CRIAPI *criAtomExAcb_CalculateWorkSizeForAttachAwbFile_TYPE)( CriFsBinderHn awb_binder, const CriChar8* awb_path);
typedef CriSint32 (CRIAPI *criAtomExAcb_GetNumAwbFileSlots_TYPE)( CriAtomExAcbHn acb_hn);
typedef const CriChar8* (CRIAPI *criAtomExAcb_GetAwbFileSlotName_TYPE)( CriAtomExAcbHn acb_hn, CriUint16 index);
typedef CriBool (CRIAPI *criAtomExAcb_IsAttachedAwbFile_TYPE)( CriAtomExAcbHn acb_hn, const CriChar8* awb_name);
typedef CriSint32 (CRIAPI *criAtomExVoicePool_CalculateWorkSizeForStandardVoicePool_TYPE)( const CriAtomExStandardVoicePoolConfig *config);
typedef CriAtomExVoicePoolHn (CRIAPI *criAtomExVoicePool_AllocateStandardVoicePool_TYPE)( const CriAtomExStandardVoicePoolConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool_TYPE)( const CriAtomExAdxVoicePoolConfig *config);
typedef CriAtomExVoicePoolHn (CRIAPI *criAtomExVoicePool_AllocateAdxVoicePool_TYPE)( const CriAtomExAdxVoicePoolConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomExVoicePool_CalculateWorkSizeForHcaVoicePool_TYPE)( const CriAtomExHcaVoicePoolConfig *config);
typedef CriAtomExVoicePoolHn (CRIAPI *criAtomExVoicePool_AllocateHcaVoicePool_TYPE)( const CriAtomExHcaVoicePoolConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool_TYPE)( const CriAtomExHcaMxVoicePoolConfig *config);
typedef CriAtomExVoicePoolHn (CRIAPI *criAtomExVoicePool_AllocateHcaMxVoicePool_TYPE)( const CriAtomExHcaMxVoicePoolConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomExVoicePool_CalculateWorkSizeForWaveVoicePool_TYPE)( const CriAtomExWaveVoicePoolConfig *config);
typedef CriAtomExVoicePoolHn (CRIAPI *criAtomExVoicePool_AllocateWaveVoicePool_TYPE)( const CriAtomExWaveVoicePoolConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomExVoicePool_CalculateWorkSizeForAiffVoicePool_TYPE)( const CriAtomExAiffVoicePoolConfig *config);
typedef CriAtomExVoicePoolHn (CRIAPI *criAtomExVoicePool_AllocateAiffVoicePool_TYPE)( const CriAtomExAiffVoicePoolConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomExVoicePool_CalculateWorkSizeForRawPcmVoicePool_TYPE)( const CriAtomExRawPcmVoicePoolConfig *config);
typedef CriAtomExVoicePoolHn (CRIAPI *criAtomExVoicePool_AllocateRawPcmVoicePool_TYPE)( const CriAtomExRawPcmVoicePoolConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExVoicePool_Free_TYPE)(CriAtomExVoicePoolHn pool);
typedef void (CRIAPI *criAtomExVoicePool_FreeAll_TYPE)(void);
typedef void (CRIAPI *criAtomExVoicePool_GetNumUsedVoices_TYPE)( CriAtomExVoicePoolHn pool, CriSint32 *cur_num, CriSint32 *limit);
typedef CriAtomPlayerHn (CRIAPI *criAtomExVoicePool_GetPlayerHandle_TYPE)( CriAtomExVoicePoolHn pool, CriSint32 index);
typedef void (CRIAPI *criAtomExCategory_SetVolumeById_TYPE)(CriAtomExCategoryId id, CriFloat32 volume);
typedef CriFloat32 (CRIAPI *criAtomExCategory_GetVolumeById_TYPE)(CriAtomExCategoryId id);
typedef CriFloat32 (CRIAPI *criAtomExCategory_GetTotalVolumeById_TYPE)(CriAtomExCategoryId id);
typedef void (CRIAPI *criAtomExCategory_SetVolumeByName_TYPE)(const CriChar8* name, CriFloat32 volume);
typedef CriFloat32 (CRIAPI *criAtomExCategory_GetVolumeByName_TYPE)(const CriChar8* name);
typedef CriFloat32 (CRIAPI *criAtomExCategory_GetTotalVolumeByName_TYPE)(const CriChar8* name);
typedef void (CRIAPI *criAtomExCategory_MuteById_TYPE)(CriAtomExCategoryId id, CriBool mute);
typedef CriBool (CRIAPI *criAtomExCategory_IsMutedById_TYPE)(CriAtomExCategoryId id);
typedef void (CRIAPI *criAtomExCategory_MuteByName_TYPE)(const CriChar8* name, CriBool mute);
typedef CriBool (CRIAPI *criAtomExCategory_IsMutedByName_TYPE)(const CriChar8* name);
typedef void (CRIAPI *criAtomExCategory_SoloById_TYPE)(CriAtomExCategoryId id, CriBool solo, CriFloat32 mute_volume);
typedef CriBool (CRIAPI *criAtomExCategory_IsSoloedById_TYPE)(CriAtomExCategoryId id);
typedef void (CRIAPI *criAtomExCategory_SoloByName_TYPE)(const CriChar8* name, CriBool solo, CriFloat32 mute_volume);
typedef CriBool (CRIAPI *criAtomExCategory_IsSoloedByName_TYPE)(const CriChar8* name);
typedef void (CRIAPI *criAtomExCategory_PauseById_TYPE)(CriAtomExCategoryId id, CriBool sw);
typedef CriBool (CRIAPI *criAtomExCategory_IsPausedById_TYPE)(CriAtomExCategoryId id);
typedef void (CRIAPI *criAtomExCategory_PauseByName_TYPE)(const CriChar8* name, CriBool sw);
typedef CriBool (CRIAPI *criAtomExCategory_IsPausedByName_TYPE)(const CriChar8* name);
typedef void (CRIAPI *criAtomExCategory_SetFadeInTimeById_TYPE)(CriAtomExCategoryId id, CriUint16 ms);
typedef void (CRIAPI *criAtomExCategory_SetFadeInTimeByName_TYPE)(const CriChar8* name, CriUint16 ms);
typedef void (CRIAPI *criAtomExCategory_SetFadeOutTimeById_TYPE)(CriAtomExCategoryId id, CriUint16 ms);
typedef void (CRIAPI *criAtomExCategory_SetFadeOutTimeByName_TYPE)(const CriChar8* name, CriUint16 ms);
typedef void (CRIAPI *criAtomExCategory_SetAisacControlById_TYPE)( CriAtomExCategoryId id, CriAtomExAisacControlId control_id, CriFloat32 control_value);
typedef void (CRIAPI *criAtomExCategory_SetAisacControlByName_TYPE)( const CriChar8* name, const CriChar8* control_name, CriFloat32 control_value);
typedef CriBool (CRIAPI *criAtomExCategory_ResetAllAisacControlById_TYPE)(CriAtomExCategoryId category_id);
typedef CriBool (CRIAPI *criAtomExCategory_ResetAllAisacControlByName_TYPE)(const CriChar8* category_name);
typedef void (CRIAPI *criAtomExCategory_AttachAisacById_TYPE)(CriAtomExCategoryId id, const CriChar8* global_aisac_name);
typedef void (CRIAPI *criAtomExCategory_AttachAisacByName_TYPE)(const CriChar8* name, const CriChar8* global_aisac_name);
typedef void (CRIAPI *criAtomExCategory_DetachAisacById_TYPE)(CriAtomExCategoryId id, const CriChar8* global_aisac_name);
typedef void (CRIAPI *criAtomExCategory_DetachAisacByName_TYPE)(const CriChar8* name, const CriChar8* global_aisac_name);
typedef void (CRIAPI *criAtomExCategory_DetachAisacAllById_TYPE)(CriAtomExCategoryId id);
typedef void (CRIAPI *criAtomExCategory_DetachAisacAllByName_TYPE)(const CriChar8* name);
typedef CriSint32 (CRIAPI *criAtomExCategory_GetNumAttachedAisacsById_TYPE)(CriAtomExCategoryId id);
typedef CriSint32 (CRIAPI *criAtomExCategory_GetNumAttachedAisacsByName_TYPE)(const CriChar8* name);
typedef CriBool (CRIAPI *criAtomExCategory_GetAttachedAisacInfoById_TYPE)( CriAtomExCategoryId id,  CriSint32 aisac_attached_index, CriAtomExAisacInfo *aisac_info);
typedef CriBool (CRIAPI *criAtomExCategory_GetAttachedAisacInfoByName_TYPE)( const CriChar8* name, CriSint32 aisac_attached_index, CriAtomExAisacInfo *aisac_info);
typedef CriBool (CRIAPI *criAtomExCategory_GetCurrentAisacControlValueById_TYPE)( CriAtomExCategoryId category_id, CriAtomExAisacControlId aisac_control_id, CriFloat32 * control_value);
typedef CriBool (CRIAPI *criAtomExCategory_GetCurrentAisacControlValueByName_TYPE)( const CriChar8* category_name, const CriChar8* aisac_control_name, CriFloat32 * control_value);
typedef CriSint32 (CRIAPI *criAtomExCategory_GetNumCuePlayingCountById_TYPE)(CriAtomExCategoryId id);
typedef CriSint32 (CRIAPI *criAtomExCategory_GetNumCuePlayingCountByName_TYPE)(const CriChar8* name);
typedef void (CRIAPI *criAtomExCategory_StopById_TYPE)(CriAtomExCategoryId id);
typedef void (CRIAPI *criAtomExCategory_StopByName_TYPE)(const CriChar8* name);
typedef void (CRIAPI *criAtomExCategory_StopWithoutReleaseTimeById_TYPE)(CriAtomExCategoryId id);
typedef void (CRIAPI *criAtomExCategory_StopWithoutReleaseTimeByName_TYPE)(const CriChar8* name);
typedef CriSint32 (CRIAPI *criAtomExPlayer_CalculateWorkSize_TYPE)( const CriAtomExPlayerConfig *config);
typedef CriAtomExPlayerHn (CRIAPI *criAtomExPlayer_Create_TYPE)( const CriAtomExPlayerConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExPlayer_Destroy_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_SetCueId_TYPE)( CriAtomExPlayerHn player, CriAtomExAcbHn acb_hn, CriAtomExCueId id);
typedef void (CRIAPI *criAtomExPlayer_SetCueName_TYPE)( CriAtomExPlayerHn player, CriAtomExAcbHn acb_hn, const CriChar8 *cue_name);
typedef void (CRIAPI *criAtomExPlayer_SetCueIndex_TYPE)( CriAtomExPlayerHn player, CriAtomExAcbHn acb_hn, CriAtomExCueIndex index);
typedef void (CRIAPI *criAtomExPlayer_SetData_TYPE)( CriAtomExPlayerHn player, void *buffer, CriSint32 size);
typedef void (CRIAPI *criAtomExPlayer_SetFile_TYPE)( CriAtomExPlayerHn player, CriFsBinderHn binder, const CriChar8 *path);
typedef void (CRIAPI *criAtomExPlayer_SetContentId_TYPE)( CriAtomExPlayerHn player, CriFsBinderHn binder, CriSint32 id);
typedef void (CRIAPI *criAtomExPlayer_SetWaveId_TYPE)( CriAtomExPlayerHn player, CriAtomAwbHn awb, CriAtomExWaveId id);
typedef CriAtomExPlaybackId (CRIAPI *criAtomExPlayer_Start_TYPE)(CriAtomExPlayerHn player);
typedef CriAtomExPlaybackId (CRIAPI *criAtomExPlayer_Prepare_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_Stop_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_StopWithoutReleaseTime_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_StopAllPlayers_TYPE)(void);
typedef void (CRIAPI *criAtomExPlayer_StopAllPlayersWithoutReleaseTime_TYPE)(void);
typedef void (CRIAPI *criAtomExPlayer_EnumeratePlayers_TYPE)(CriAtomExPlayerCbFunc func, void *obj);
typedef void (CRIAPI *criAtomExPlayer_Pause_TYPE)(CriAtomExPlayerHn player, CriBool sw);
typedef void (CRIAPI *criAtomExPlayer_Resume_TYPE)(CriAtomExPlayerHn player, CriAtomExResumeMode mode);
typedef CriBool (CRIAPI *criAtomExPlayer_IsPaused_TYPE)(CriAtomExPlayerHn player);
typedef CriAtomExPlayerStatus (CRIAPI *criAtomExPlayer_GetStatus_TYPE)(CriAtomExPlayerHn player);
typedef CriSint32 (CRIAPI *criAtomExPlayer_GetNumPlaybacks_TYPE)(CriAtomExPlayerHn player);
typedef CriAtomExPlaybackId (CRIAPI *criAtomExPlayer_GetLastPlaybackId_TYPE)(CriAtomExPlayerHn player);
typedef CriSint64 (CRIAPI *criAtomExPlayer_GetTime_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_SetFormat_TYPE)( CriAtomExPlayerHn player, CriAtomExFormat format);
typedef void (CRIAPI *criAtomExPlayer_SetNumChannels_TYPE)( CriAtomExPlayerHn player, CriSint32 num_channels);
typedef void (CRIAPI *criAtomExPlayer_SetSamplingRate_TYPE)( CriAtomExPlayerHn player, CriSint32 sampling_rate);
typedef void (CRIAPI *criAtomExPlayer_SetSoundRendererType_TYPE)( CriAtomExPlayerHn player, CriAtomSoundRendererType type);
typedef void (CRIAPI *criAtomExPlayer_SetGroupNumber_TYPE)( CriAtomExPlayerHn player, CriSint32 group_no);
typedef void (CRIAPI *criAtomExPlayer_SetVoiceControlMethod_TYPE)( CriAtomExPlayerHn player, CriAtomExVoiceControlMethod method);
typedef void (CRIAPI *criAtomExPlayer_SetVoicePoolIdentifier_TYPE)( CriAtomExPlayerHn player, CriAtomExVoicePoolIdentifier identifier);
typedef void (CRIAPI *criAtomExPlayer_SetHcaMxMixerId_TYPE)(CriAtomExPlayerHn player, CriSint32 mixer_id);
typedef void (CRIAPI *criAtomExPlayer_SetAsrRackId_TYPE)(CriAtomExPlayerHn player, CriSint32 rack_id);
typedef void (CRIAPI *criAtomExPlayer_SetAsrRackIdArray_TYPE)( CriAtomExPlayerHn player, const CriSint32 *rack_id_array, CriSint32 num_racks);
typedef void (CRIAPI *criAtomExPlayer_SetStartTime_TYPE)( CriAtomExPlayerHn player, CriSint64 start_time_ms);
typedef void (CRIAPI *criAtomExPlayer_SetSequencePrepareTime_TYPE)( CriAtomExPlayerHn player, CriUint32 seq_prep_time_ms);
typedef void (CRIAPI *criAtomExPlayer_SetSyncPlaybackId_TYPE)( CriAtomExPlayerHn player, CriAtomExPlaybackId playback_id);
typedef void (CRIAPI *criAtomExPlayer_SetPlaybackRatio_TYPE)( CriAtomExPlayerHn player, CriFloat32 playback_ratio);
typedef void (CRIAPI *criAtomExPlayer_LimitLoopCount_TYPE)(CriAtomExPlayerHn player, CriSint32 count);
typedef void (CRIAPI *criAtomExPlayer_UpdateAll_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_Update_TYPE)( CriAtomExPlayerHn player, CriAtomExPlaybackId id);
typedef void (CRIAPI *criAtomExPlayer_ResetParameters_TYPE)(CriAtomExPlayerHn player);
typedef CriFloat32 (CRIAPI *criAtomExPlayer_GetParameterFloat32_TYPE)(CriAtomExPlayerHn player, CriAtomExParameterId id);
typedef CriUint32 (CRIAPI *criAtomExPlayer_GetParameterUint32_TYPE)(CriAtomExPlayerHn player, CriAtomExParameterId id);
typedef CriSint32 (CRIAPI *criAtomExPlayer_GetParameterSint32_TYPE)(CriAtomExPlayerHn player, CriAtomExParameterId id);
typedef void (CRIAPI *criAtomExPlayer_SetVolume_TYPE)( CriAtomExPlayerHn player, CriFloat32 volume);
typedef void (CRIAPI *criAtomExPlayer_SetPitch_TYPE)(CriAtomExPlayerHn player, CriFloat32 pitch);
typedef void (CRIAPI *criAtomExPlayer_SetMaxPitch_TYPE)(CriAtomExPlayerHn player, CriFloat32 pitch);
typedef void (CRIAPI *criAtomExPlayer_SetPan3dAngle_TYPE)( CriAtomExPlayerHn player, CriFloat32 pan3d_angle);
typedef void (CRIAPI *criAtomExPlayer_SetPan3dInteriorDistance_TYPE)( CriAtomExPlayerHn player, CriFloat32 pan3d_interior_distance);
typedef void (CRIAPI *criAtomExPlayer_SetPan3dVolume_TYPE)( CriAtomExPlayerHn player, CriFloat32 pan3d_volume);
typedef void (CRIAPI *criAtomExPlayer_SetPanType_TYPE)( CriAtomExPlayerHn player, CriAtomExPanType pan_type);
typedef void (CRIAPI *criAtomExPlayer_SetPanSpeakerType_TYPE)( CriAtomExPlayerHn player, CriAtomExPanSpeakerType pan_speaker_type);
typedef void (CRIAPI *criAtomExPlayer_AddMixDownCenterVolumeOffset_TYPE)( CriAtomExPlayerHn player, CriFloat32 mixdown_center_volume_offset);
typedef void (CRIAPI *criAtomExPlayer_AddMixDownLfeVolumeOffset_TYPE)( CriAtomExPlayerHn player, CriFloat32 mixdown_lfe_volume_offset);
typedef void (CRIAPI *criAtomExPlayer_ChangeDefaultPanSpeakerType_TYPE)( CriAtomExPanSpeakerType pan_speaker_type);
typedef void (CRIAPI *criAtomExPlayer_SetPanAngleType_TYPE)( CriAtomExPlayerHn player, CriAtomExPanAngleType pan_angle_type);
typedef void (CRIAPI *criAtomExPlayer_SetPanSpread_TYPE)(CriAtomExPlayerHn player, CriFloat32 spread);
typedef void (CRIAPI *criAtomExPlayer_SetSendLevel_TYPE)( CriAtomExPlayerHn player, CriSint32 ch, CriAtomExSpeakerId spk, CriFloat32 level);
typedef void (CRIAPI *criAtomExPlayer_SetBusSendLevelByName_TYPE)( CriAtomExPlayerHn player, const CriChar8* bus_name, CriFloat32 level);
typedef void (CRIAPI *criAtomExPlayer_SetBusSendLevelOffsetByName_TYPE)( CriAtomExPlayerHn player, const CriChar8* bus_name, CriFloat32 level_offset);
typedef void (CRIAPI *criAtomExPlayer_SetPanAdx1Compatible_TYPE)( CriAtomExPlayerHn player, CriSint32 ch, CriFloat32 pan);
typedef void (CRIAPI *criAtomExPlayer_SetBandpassFilterParameters_TYPE)( CriAtomExPlayerHn player, CriFloat32 cof_low, CriFloat32 cof_high);
typedef void (CRIAPI *criAtomExPlayer_SetBiquadFilterParameters_TYPE)( CriAtomExPlayerHn player, CriAtomExBiquadFilterType type, CriFloat32 frequency, CriFloat32 gain, CriFloat32 q_value);
typedef void (CRIAPI *criAtomExPlayer_SetVoicePriority_TYPE)( CriAtomExPlayerHn player, CriSint32 priority);
typedef void (CRIAPI *criAtomExPlayer_SetAisacControlById_TYPE)( CriAtomExPlayerHn player, CriAtomExAisacControlId control_id, CriFloat32 control_value);
typedef void (CRIAPI *criAtomExPlayer_SetAisacControlByName_TYPE)( CriAtomExPlayerHn player, const CriChar8 *control_name, CriFloat32 control_value);
typedef void (CRIAPI *criAtomExPlayer_ClearAisacControls_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_Set3dSourceHn_TYPE)( CriAtomExPlayerHn player, CriAtomEx3dSourceHn source);
typedef void (CRIAPI *criAtomExPlayer_Set3dSourceListHn_TYPE)( CriAtomExPlayerHn player, CriAtomEx3dSourceListHn source_list);
typedef void (CRIAPI *criAtomExPlayer_Set3dListenerHn_TYPE)( CriAtomExPlayerHn player, CriAtomEx3dListenerHn listener);
typedef CriFloat32 (CRIAPI *criAtomExPlayer_GetAisacControlById_TYPE)( CriAtomExPlayerHn player, CriAtomExAisacControlId control_id);
typedef CriFloat32 (CRIAPI *criAtomExPlayer_GetAisacControlByName_TYPE)( CriAtomExPlayerHn player, const CriChar8 *control_name);
typedef void (CRIAPI *criAtomExPlayer_SetCategoryById_TYPE)( CriAtomExPlayerHn player, CriUint32 category_id);
typedef void (CRIAPI *criAtomExPlayer_SetCategoryByName_TYPE)( CriAtomExPlayerHn player, const CriChar8 *category_name);
typedef void (CRIAPI *criAtomExPlayer_UnsetCategory_TYPE)(CriAtomExPlayerHn player);
typedef CriSint32 (CRIAPI *criAtomExPlayer_GetNumCategories_TYPE)(CriAtomExPlayerHn player);
typedef CriBool (CRIAPI *criAtomExPlayer_GetCategoryInfo_TYPE)(CriAtomExPlayerHn player, CriUint16 index, CriAtomExCategoryInfo* info);
typedef void (CRIAPI *criAtomExPlayer_SetTrackInfo_TYPE)(CriAtomExPlayerHn player, CriSint32 num_tracks, const CriSint32 *channels_per_track);
typedef void (CRIAPI *criAtomExPlayer_SetTrackVolume_TYPE)( CriAtomExPlayerHn player, CriSint32 track_no, CriFloat32 volume);
typedef void (CRIAPI *criAtomExPlayer_SetSilentMode_TYPE)( CriAtomExPlayerHn player, CriAtomExSilentMode silent_mode);
typedef void (CRIAPI *criAtomExPlayer_SetCuePriority_TYPE)( CriAtomExPlayerHn player, CriSint32 cue_priority);
typedef void (CRIAPI *criAtomExPlayer_SetPreDelayTime_TYPE)( CriAtomExPlayerHn player, CriFloat32 predelay_time_ms);
typedef void (CRIAPI *criAtomExPlayer_SetEnvelopeAttackTime_TYPE)( CriAtomExPlayerHn player, CriFloat32 attack_time_ms);
typedef void (CRIAPI *criAtomExPlayer_SetEnvelopeHoldTime_TYPE)( CriAtomExPlayerHn player, CriFloat32 hold_time_ms);
typedef void (CRIAPI *criAtomExPlayer_SetEnvelopeDecayTime_TYPE)( CriAtomExPlayerHn player, CriFloat32 decay_time_ms);
typedef void (CRIAPI *criAtomExPlayer_SetEnvelopeReleaseTime_TYPE)( CriAtomExPlayerHn player, CriFloat32 release_time_ms);
typedef void (CRIAPI *criAtomExPlayer_SetEnvelopeSustainLevel_TYPE)( CriAtomExPlayerHn player, CriFloat32 susutain_level);
typedef void (CRIAPI *criAtomExPlayer_SetDataRequestCallback_TYPE)( CriAtomExPlayerHn player, CriAtomExPlayerDataRequestCbFunc func, void *obj);
typedef void (CRIAPI *criAtomExPlayer_SetFilterCallback_TYPE)( CriAtomExPlayerHn player, CriAtomExPlayerFilterCbFunc func, void *obj);
typedef void (CRIAPI *criAtomExPlayer_SetRandomSeed_TYPE)(CriAtomExPlayerHn player, CriUint32 seed);
typedef void (CRIAPI *criAtomExPlayer_SetDspParameter_TYPE)( CriAtomExPlayerHn player, CriSint32 param_id, CriFloat32 param_val);
typedef void (CRIAPI *criAtomExPlayer_AttachAisac_TYPE)(CriAtomExPlayerHn player, const CriChar8* global_aisac_name);
typedef void (CRIAPI *criAtomExPlayer_AttachAisacByIndex_TYPE)(CriAtomExPlayerHn player, CriUint16 global_aisac_index);
typedef void (CRIAPI *criAtomExPlayer_DetachAisac_TYPE)(CriAtomExPlayerHn player, const CriChar8* global_aisac_name);
typedef void (CRIAPI *criAtomExPlayer_DetachAisacByIndex_TYPE)(CriAtomExPlayerHn player, CriUint16 global_aisac_index);
typedef void (CRIAPI *criAtomExPlayer_DetachAisacAll_TYPE)(CriAtomExPlayerHn player);
typedef CriSint32 (CRIAPI *criAtomExPlayer_GetNumAttachedAisacs_TYPE)(CriAtomExPlayerHn player);
typedef CriBool (CRIAPI *criAtomExPlayer_GetAttachedAisacInfo_TYPE)( CriAtomExPlayerHn player, CriSint32 aisac_attached_index, CriAtomExAisacInfo *aisac_info);
typedef void (CRIAPI *criAtomExPlayer_SetStreamingCacheId_TYPE)( CriAtomExPlayerHn player, CriAtomExStreamingCacheId cache_id);
typedef void (CRIAPI *criAtomExPlayer_AttachTween_TYPE)(CriAtomExPlayerHn player, CriAtomExTweenHn tween);
typedef void (CRIAPI *criAtomExPlayer_DetachTween_TYPE)(CriAtomExPlayerHn player, CriAtomExTweenHn tween);
typedef void (CRIAPI *criAtomExPlayer_DetachTweenAll_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_SetFirstBlockIndex_TYPE)( CriAtomExPlayerHn player, CriAtomExBlockIndex index);
typedef void (CRIAPI *criAtomExPlayer_SetBlockTransitionCallback_TYPE)( CriAtomExPlayerHn player, CriAtomExPlayerBlockTransitionCbFunc func, void *obj);
typedef CriAtomExSoundObjectHn (CRIAPI *criAtomExPlayer_GetSoundObject_TYPE)(CriAtomExPlayerHn player); 
typedef void (CRIAPI *criAtomExPlayer_SetDrySendLevel_TYPE)( CriAtomExPlayerHn player, CriAtomExSpeakerId spk, CriFloat32 offset, CriFloat32 gain);
typedef void (CRIAPI *criAtomExPlayer_SetSelectorLabel_TYPE)( CriAtomExPlayerHn player, const CriChar8 *selector, const CriChar8 *label);
typedef void (CRIAPI *criAtomExPlayer_ClearSelectorLabels_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_SetPlaybackTrackInfoNotificationCallback_TYPE)( CriAtomExPlayerHn player, CriAtomExPlayerPlaybackTrackInfoNotificationCbFunc func, void *obj);
typedef void (CRIAPI *criAtomExPlayback_Stop_TYPE)(CriAtomExPlaybackId id);
typedef void (CRIAPI *criAtomExPlayback_StopWithoutReleaseTime_TYPE)(CriAtomExPlaybackId id);
typedef void (CRIAPI *criAtomExPlayback_Pause_TYPE)(CriAtomExPlaybackId id, CriBool sw);
typedef void (CRIAPI *criAtomExPlayback_Resume_TYPE)(CriAtomExPlaybackId id, CriAtomExResumeMode mode);
typedef CriBool (CRIAPI *criAtomExPlayback_IsPaused_TYPE)(CriAtomExPlaybackId id);
typedef CriAtomExPlaybackStatus (CRIAPI *criAtomExPlayback_GetStatus_TYPE)(CriAtomExPlaybackId id);
typedef CriBool (CRIAPI *criAtomExPlayback_GetFormatInfo_TYPE)( CriAtomExPlaybackId id, CriAtomExFormatInfo *info);
typedef CriBool (CRIAPI *criAtomExPlayback_GetSource_TYPE)( CriAtomExPlaybackId id, CriAtomExSourceInfo *source);
typedef CriAtomPlayerHn (CRIAPI *criAtomExPlayback_GetAtomPlayer_TYPE)(CriAtomExPlaybackId id);
typedef CriSint64 (CRIAPI *criAtomExPlayback_GetTime_TYPE)(CriAtomExPlaybackId id);
typedef CriSint64 (CRIAPI *criAtomExPlayback_GetTimeSyncedWithAudio_TYPE)(CriAtomExPlaybackId id);
typedef CriSint64 (CRIAPI *criAtomExPlayback_GetTimeSyncedWithAudioMicro_TYPE)(CriAtomExPlaybackId id);
typedef CriSint64 (CRIAPI *criAtomExPlayback_GetSequencePosition_TYPE)(CriAtomExPlaybackId id);
typedef CriBool (CRIAPI *criAtomExPlayback_GetNumPlayedSamples_TYPE)( CriAtomExPlaybackId id, CriSint64 *num_samples, CriSint32 *sampling_rate);
typedef CriBool (CRIAPI *criAtomExPlayback_GetParameterFloat32_TYPE)( CriAtomExPlaybackId playback_id, CriAtomExParameterId parameter_id, CriFloat32 *value_float32);
typedef CriBool (CRIAPI *criAtomExPlayback_GetParameterUint32_TYPE)( CriAtomExPlaybackId playback_id, CriAtomExParameterId parameter_id, CriUint32* value_uint32);
typedef CriBool (CRIAPI *criAtomExPlayback_GetParameterSint32_TYPE)( CriAtomExPlaybackId playback_id, CriAtomExParameterId parameter_id, CriSint32* value_sint32);
typedef CriBool (CRIAPI *criAtomExPlayback_GetAisacControlById_TYPE)( CriAtomExPlaybackId playback_id, CriAtomExAisacControlId control_id, CriFloat32 *control_value);
typedef CriBool (CRIAPI *criAtomExPlayback_GetAisacControlByName_TYPE)( CriAtomExPlaybackId playback_id, const CriChar8 *control_name, CriFloat32 *control_value);
typedef void (CRIAPI *criAtomExPlayback_SetNextBlockIndex_TYPE)(CriAtomExPlaybackId id, CriAtomExBlockIndex index);
typedef CriAtomExBlockIndex (CRIAPI *criAtomExPlayback_GetCurrentBlockIndex_TYPE)(CriAtomExPlaybackId id);
typedef CriBool (CRIAPI *criAtomExPlayback_GetPlaybackTrackInfo_TYPE)(CriAtomExPlaybackId id, CriAtomExPlaybackTrackInfo* info);
typedef CriBool (CRIAPI *criAtomExPlayback_GetBeatSyncInfo_TYPE)(CriAtomExPlaybackId id, CriAtomExBeatSyncInfo* info);
typedef CriSint32 (CRIAPI *criAtomExPlayer_CalculateWorkSizeForFader_TYPE)( const CriAtomExFaderConfig *config);
typedef void (CRIAPI *criAtomExPlayer_AttachFader_TYPE)(CriAtomExPlayerHn player, const CriAtomExFaderConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExPlayer_DetachFader_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_SetFadeOutTime_TYPE)(CriAtomExPlayerHn player, CriSint32 ms);
typedef CriSint32 (CRIAPI *criAtomExPlayer_GetFadeOutTime_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_SetFadeInTime_TYPE)(CriAtomExPlayerHn player, CriSint32 ms);
typedef CriSint32 (CRIAPI *criAtomExPlayer_GetFadeInTime_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_SetFadeInStartOffset_TYPE)(CriAtomExPlayerHn player, CriSint32 ms);
typedef CriSint32 (CRIAPI *criAtomExPlayer_GetFadeInStartOffset_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_SetFadeOutEndDelay_TYPE)(CriAtomExPlayerHn player, CriSint32 ms);
typedef CriSint32 (CRIAPI *criAtomExPlayer_GetFadeOutEndDelay_TYPE)(CriAtomExPlayerHn player);
typedef CriBool (CRIAPI *criAtomExPlayer_IsFading_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExPlayer_ResetFaderParameters_TYPE)(CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExSequencer_SetEventCallback_TYPE)(CriAtomExSequencerEventCbFunc func, void* obj);
typedef void (CRIAPI *criAtomExBeatSync_SetCallback_TYPE)(CriAtomExBeatSyncCbFunc func, void* obj);
typedef CriSint32 (CRIAPI *criAtomEx3dSource_CalculateWorkSize_TYPE)(const CriAtomEx3dSourceConfig *config);
typedef CriAtomEx3dSourceHn (CRIAPI *criAtomEx3dSource_Create_TYPE)( const CriAtomEx3dSourceConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomEx3dSource_Destroy_TYPE)(CriAtomEx3dSourceHn ex_3d_source);
typedef void (CRIAPI *criAtomEx3dSource_Update_TYPE)(CriAtomEx3dSourceHn ex_3d_source);
typedef void (CRIAPI *criAtomEx3dSource_ResetParameters_TYPE)(CriAtomEx3dSourceHn ex_3d_source);
typedef void (CRIAPI *criAtomEx3dSource_SetPosition_TYPE)(CriAtomEx3dSourceHn ex_3d_source, const CriAtomExVector *position);
typedef CriAtomExVector (CRIAPI *criAtomEx3dSource_GetPosition_TYPE)(CriAtomEx3dSourceHn ex_3d_source);
typedef void (CRIAPI *criAtomEx3dSource_SetVelocity_TYPE)(CriAtomEx3dSourceHn ex_3d_source, const CriAtomExVector *velocity);
typedef void (CRIAPI *criAtomEx3dSource_SetOrientation_TYPE)(CriAtomEx3dSourceHn ex_3d_source, const CriAtomExVector *front, const CriAtomExVector *top);
typedef void (CRIAPI *criAtomEx3dSource_SetConeParameter_TYPE)(CriAtomEx3dSourceHn ex_3d_source, CriFloat32 inside_angle, CriFloat32 outside_angle, CriFloat32 outside_volume);
typedef void (CRIAPI *criAtomEx3dSource_ChangeDefaultConeParameter_TYPE)( CriFloat32 inside_angle, CriFloat32 outside_angle, CriFloat32 outside_volume);
typedef void (CRIAPI *criAtomEx3dSource_SetMinMaxAttenuationDistance_TYPE)(CriAtomEx3dSourceHn ex_3d_source, CriFloat32 min_attenuation_distance, CriFloat32 max_attenuation_distance);
typedef void (CRIAPI *criAtomEx3dSource_ChangeDefaultMinMaxAttenuationDistance_TYPE)( CriFloat32 min_attenuation_distance, CriFloat32 max_attenuation_distance);
typedef void (CRIAPI *criAtomEx3dSource_SetInteriorPanField_TYPE)(CriAtomEx3dSourceHn ex_3d_source, CriFloat32 source_radius, CriFloat32 interior_distance);
typedef void (CRIAPI *criAtomEx3dSource_ChangeDefaultInteriorPanField_TYPE)(CriFloat32 source_radius, CriFloat32 interior_distance);
typedef void (CRIAPI *criAtomEx3dSource_SetDopplerFactor_TYPE)(CriAtomEx3dSourceHn ex_3d_source, CriFloat32 doppler_factor);
typedef void (CRIAPI *criAtomEx3dSource_ChangeDefaultDopplerFactor_TYPE)(CriFloat32 doppler_factor);
typedef void (CRIAPI *criAtomEx3dSource_SetVolume_TYPE)(CriAtomEx3dSourceHn ex_3d_source, CriFloat32 volume);
typedef void (CRIAPI *criAtomEx3dSource_ChangeDefaultVolume_TYPE)(CriFloat32 volume);
typedef void (CRIAPI *criAtomEx3dSource_SetMaxAngleAisacDelta_TYPE)(CriAtomEx3dSourceHn ex_3d_source, CriFloat32 max_delta);
typedef void (CRIAPI *criAtomEx3dSource_SetDistanceAisacControlId_TYPE)(CriAtomEx3dSourceHn ex_3d_source, CriUint16 aisac_control_id);
typedef void (CRIAPI *criAtomEx3dSource_SetListenerBasedAngleAisacControlId_TYPE)(CriAtomEx3dSourceHn ex_3d_source, CriUint16 aisac_control_id);
typedef void (CRIAPI *criAtomEx3dSource_SetSourceBasedAngleAisacControlId_TYPE)(CriAtomEx3dSourceHn ex_3d_source, CriUint16 aisac_control_id);
typedef CriSint32 (CRIAPI *criAtomEx3dSourceList_CalculateWorkSize_TYPE)(const CriAtomEx3dSourceListConfig *config);
typedef CriAtomEx3dSourceListHn (CRIAPI *criAtomEx3dSourceList_Create_TYPE)( const CriAtomEx3dSourceListConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomEx3dSourceList_Destroy_TYPE)(CriAtomEx3dSourceListHn ex_3d_source_list);
typedef void (CRIAPI *criAtomEx3dSourceList_Add_TYPE)( CriAtomEx3dSourceListHn ex_3d_source_list, CriAtomEx3dSourceHn ex_3d_source);
typedef void (CRIAPI *criAtomEx3dSourceList_Remove_TYPE)( CriAtomEx3dSourceListHn ex_3d_source_list, CriAtomEx3dSourceHn ex_3d_source);
typedef void (CRIAPI *criAtomEx3dSourceList_RemoveAll_TYPE)(CriAtomEx3dSourceListHn ex_3d_source_list);
typedef CriSint32 (CRIAPI *criAtomEx3dListener_CalculateWorkSize_TYPE)(const CriAtomEx3dListenerConfig *config);
typedef CriAtomEx3dListenerHn (CRIAPI *criAtomEx3dListener_Create_TYPE)( const CriAtomEx3dListenerConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomEx3dListener_Destroy_TYPE)(CriAtomEx3dListenerHn ex_3d_listener);
typedef void (CRIAPI *criAtomEx3dListener_Update_TYPE)(CriAtomEx3dListenerHn ex_3d_listener);
typedef void (CRIAPI *criAtomEx3dListener_ResetParameters_TYPE)(CriAtomEx3dListenerHn ex_3d_listener);
typedef void (CRIAPI *criAtomEx3dListener_SetPosition_TYPE)(CriAtomEx3dListenerHn ex_3d_listener, const CriAtomExVector *position);
typedef CriAtomExVector (CRIAPI *criAtomEx3dListener_GetPosition_TYPE)(CriAtomEx3dListenerHn ex_3d_listener);
typedef void (CRIAPI *criAtomEx3dListener_SetVelocity_TYPE)(CriAtomEx3dListenerHn ex_3d_listener, const CriAtomExVector *velocity);
typedef void (CRIAPI *criAtomEx3dListener_SetOrientation_TYPE)(CriAtomEx3dListenerHn ex_3d_listener, const CriAtomExVector *front, const CriAtomExVector *top);
typedef void (CRIAPI *criAtomEx3dListener_SetDistanceFactor_TYPE)(CriAtomEx3dListenerHn ex_3d_listener, CriFloat32 distance_factor);
typedef void (CRIAPI *criAtomEx3dListener_SetFocusPoint_TYPE)(CriAtomEx3dListenerHn ex_3d_listener, const CriAtomExVector *focus_point);
typedef void (CRIAPI *criAtomEx3dListener_SetDistanceFocusLevel_TYPE)(CriAtomEx3dListenerHn ex_3d_listener, CriFloat32 distance_focus_level);
typedef void (CRIAPI *criAtomEx3dListener_SetDirectionFocusLevel_TYPE)(CriAtomEx3dListenerHn ex_3d_listener, CriFloat32 direction_focus_level);
typedef void (CRIAPI *criAtomExVoicePool_DetachDsp_TYPE)(CriAtomExVoicePoolHn pool);
typedef CriSint32 (CRIAPI *criAtomExVoicePool_CalculateWorkSizeForDspPitchShifter_TYPE)( const CriAtomExDspPitchShifterConfig *config);
typedef void (CRIAPI *criAtomExVoicePool_AttachDspPitchShifter_TYPE)(CriAtomExVoicePoolHn pool, const CriAtomExDspPitchShifterConfig *config, void *work, CriSint32 work_size);
typedef CriSint32 (CRIAPI *criAtomExVoicePool_CalculateWorkSizeForDspTimeStretch_TYPE)( const CriAtomExDspTimeStretchConfig *config);
typedef void (CRIAPI *criAtomExVoicePool_AttachDspTimeStretch_TYPE)(CriAtomExVoicePoolHn pool, const CriAtomExDspTimeStretchConfig *config, void *work, CriSint32 work_size);
typedef CriBool (CRIAPI *criAtomExStreamingCache_IsCachedWaveformById_TYPE)( CriAtomExStreamingCacheId stm_cache_id, CriAtomExAcbHn acb_hn, CriAtomExCueId id);
typedef CriBool (CRIAPI *criAtomExStreamingCache_IsCachedWaveformByName_TYPE)( CriAtomExStreamingCacheId stm_cache_id, CriAtomExAcbHn acb_hn, const CriChar8 *name);
typedef CriBool (CRIAPI *criAtomExStreamingCache_LoadWaveformById_TYPE)( CriAtomExStreamingCacheId stm_cache_id, CriAtomExAcbHn acb_hn, CriAtomExCueId cue_id);
typedef CriBool (CRIAPI *criAtomExStreamingCache_LoadWaveformByName_TYPE)( CriAtomExStreamingCacheId stm_cache_id, CriAtomExAcbHn acb_hn, const CriChar8 *name);
typedef CriSint32 (CRIAPI *criAtomExTween_CalculateWorkSize_TYPE)(const CriAtomExTweenConfig *config);
typedef CriAtomExTweenHn (CRIAPI *criAtomExTween_Create_TYPE)( const CriAtomExTweenConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExTween_Destroy_TYPE)(CriAtomExTweenHn tween);
typedef CriFloat32 (CRIAPI *criAtomExTween_GetValue_TYPE)(CriAtomExTweenHn tween);
typedef void (CRIAPI *criAtomExTween_MoveTo_TYPE)(CriAtomExTweenHn tween, CriUint16 time_ms, CriFloat32 value);
typedef void (CRIAPI *criAtomExTween_MoveFrom_TYPE)(CriAtomExTweenHn tween, CriUint16 time_ms, CriFloat32 value);
typedef void (CRIAPI *criAtomExTween_Stop_TYPE)(CriAtomExTweenHn tween);
typedef void (CRIAPI *criAtomExTween_Reset_TYPE)(CriAtomExTweenHn tween);
typedef void (CRIAPI *criAtomEx_SetVoiceEventCallback_TYPE)(CriAtomExVoiceEventCbFunc func, void *obj);
typedef void (CRIAPI *criAtomEx_EnumerateVoiceInfos_TYPE)(CriAtomExVoiceInfoCbFunc func, void *obj);
typedef void (CRIAPI *criAtomEx_SetMonitoringVoiceStopCallback_TYPE)(CriAtomExMonitoringVoiceStopCbFunc func, void *obj);
typedef void (CRIAPI *criAtomEx_SetMonitoringVoiceStopPlaybackId_TYPE)(CriAtomExPlaybackId playback_id);
typedef CriSint32 (CRIAPI *criAtomExSoundObject_CalculateWorkSize_TYPE)( const CriAtomExSoundObjectConfig *config);
typedef CriAtomExSoundObjectHn (CRIAPI *criAtomExSoundObject_Create_TYPE)( const CriAtomExSoundObjectConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExSoundObject_Destroy_TYPE)(CriAtomExSoundObjectHn sound_object);
typedef void (CRIAPI *criAtomExSoundObject_AddPlayer_TYPE)(CriAtomExSoundObjectHn sound_object, CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExSoundObject_DeletePlayer_TYPE)(CriAtomExSoundObjectHn sound_object, CriAtomExPlayerHn player);
typedef void (CRIAPI *criAtomExSoundObject_DeleteAllPlayers_TYPE)(CriAtomExSoundObjectHn sound_object);
typedef CriSint64 (CRIAPI *criAtomExPlayer_GetTimeReal_TYPE)(CriAtomExPlayerHn player);
typedef CriSint64 (CRIAPI *criAtomExPlayback_GetTimeReal_TYPE)(CriAtomExPlaybackId id);
typedef void (CRIAPI *criAtomExPlayback_EnumerateAtomPlayers_TYPE)( CriAtomExPlaybackId id, CriAtomPlayerCbFunc func, void* obj);
typedef void (CRIAPI *criAtomEx3dListener_GetFocusPoint_TYPE)(CriAtomEx3dListenerHn ex_3d_listener, CriAtomExVector *focus_point);
typedef CriFloat32 (CRIAPI *criAtomEx3dListener_GetDistanceFocusLevel_TYPE)(CriAtomEx3dListenerHn ex_3d_listener);
typedef CriFloat32 (CRIAPI *criAtomEx3dListener_GetDirectionFocusLevel_TYPE)(CriAtomEx3dListenerHn ex_3d_listener);
typedef CriAtomExAcbHn (CRIAPI *criAtomExAcb_GetCurrentAcb_TYPE)(void);
typedef void (CRIAPI *criAtomEx3dSource_SetAttenuationDistanceSetting_TYPE)(CriAtomEx3dSourceHn ex_3d_source, CriBool sw);
typedef CriBool (CRIAPI *criAtomEx3dSource_GetAttenuationDistanceSetting_TYPE)(const CriAtomEx3dSourceHn ex_3d_source);
typedef void (CRIAPI *criAtomExPlayer_SetBusSendLevel_TYPE)( CriAtomExPlayerHn player, CriSint32 bus_index, CriFloat32 level);
typedef void (CRIAPI *criAtomExPlayer_SetBusSendLevelOffset_TYPE)( CriAtomExPlayerHn player, CriSint32 bus_index, CriFloat32 level_offset);
typedef void (CRIAPI *criAtomEx_GetNumUsedVirtualVoices_TYPE)(CriSint32 *cur_num, CriSint32 *limit);
typedef void (CRIAPI *criAtomEx_GetNumUsedSequences_TYPE)(CriSint32 *cur_num, CriSint32 *limit);
typedef void (CRIAPI *criAtomEx_GetNumUsedSequenceTracks_TYPE)(CriSint32 *cur_num, CriSint32 *limit);
typedef void (CRIAPI *criAtomEx_GetNumUsedSequenceTrackItems_TYPE)(CriSint32 *cur_num, CriSint32 *limit);
typedef void (CRIAPI *criAtomEx_GetNumUsedAisacAutoModulations_TYPE)(CriSint32 *cur_num, CriSint32 *limit);
typedef void (CRIAPI *criAtomEx3dSource_SetConeOrientation_TYPE)(CriAtomEx3dSourceHn ex_3d_source, const CriAtomExVector *cone_orient);
typedef CriSint32 (CRIAPI *criAtomExMonitor_CalculateWorkSize_TYPE)(const CriAtomExMonitorConfig* config);
typedef void (CRIAPI *criAtomExMonitor_Initialize_TYPE)( const CriAtomExMonitorConfig *config, void *work, CriSint32 work_size);
typedef void (CRIAPI *criAtomExMonitor_Finalize_TYPE)(void);
typedef const CriChar8* (CRIAPI *criAtomExMonitor_GetServerIpString_TYPE)(void);
typedef const CriChar8* (CRIAPI *criAtomExMonitor_GetClientIpString_TYPE)(void);
typedef CriBool (CRIAPI *criAtomExMonitor_IsConnected_TYPE)(void);
typedef void (CRIAPI *criAtomExMonitor_SetLogCallback_TYPE)(CriAtomExMonitorLogCbFunc cbf, void* obj);
typedef void (CRIAPI *criAtomExMonitor_SetLogMode_TYPE)(CriUint32 mode);
typedef void (CRIAPI *criAtomExMonitor_OutputUserLog_TYPE)(const CriChar8* message);
typedef void (CRIAPI *criAtomExMonitor_SetDataUpdateNotificationCallback_TYPE)( CriAtomExMonitorDataUpdateNotificationCbFunc func, void *obj);

/***************************************************************************
 *      Prototype Classes
 ***************************************************************************/
class CRIWARERUNTIME_API FCriWareApi {
public:
	static criErr_ConvertIdToMsg_TYPE criErr_ConvertIdToMsg;
	static criErr_ConvertIdToMessage_TYPE criErr_ConvertIdToMessage;
	static criErr_SetCallback_TYPE criErr_SetCallback;
	static criErr_SetErrorNotificationLevel_TYPE criErr_SetErrorNotificationLevel;
	static criErr_GetErrorCount_TYPE criErr_GetErrorCount;
	static criErr_ResetErrorCount_TYPE criErr_ResetErrorCount;
	static criFs_SetUserMallocFunction_TYPE criFs_SetUserMallocFunction;
	static criFs_SetUserFreeFunction_TYPE criFs_SetUserFreeFunction;
	static criFs_SetSelectIoCallback_TYPE criFs_SetSelectIoCallback;
	static criAtom_GetVersionNumber_TYPE criAtom_GetVersionNumber;
	static criAtom_CalculateWorkSize_TYPE criAtom_CalculateWorkSize;
	static criAtom_Initialize_TYPE criAtom_Initialize;
	static criAtom_Finalize_TYPE criAtom_Finalize;
	static criAtom_IsInitialized_TYPE criAtom_IsInitialized;
	static criAtom_IsAudioOutputActive_TYPE criAtom_IsAudioOutputActive;
	static criAtom_ExecuteMain_TYPE criAtom_ExecuteMain;
	static criAtom_ExecuteAudioProcess_TYPE criAtom_ExecuteAudioProcess;
	static criAtom_SetUserMallocFunction_TYPE criAtom_SetUserMallocFunction;
	static criAtom_SetUserFreeFunction_TYPE criAtom_SetUserFreeFunction;
	static criAtom_SetAudioFrameStartCallback_TYPE criAtom_SetAudioFrameStartCallback;
	static criAtom_SetAudioFrameEndCallback_TYPE criAtom_SetAudioFrameEndCallback;
	static criAtom_Lock_TYPE criAtom_Lock;
	static criAtom_Unlock_TYPE criAtom_Unlock;
	static criAtom_SetChannelMapping_TYPE criAtom_SetChannelMapping;
	static criAtom_AttachPerformanceMonitor_TYPE criAtom_AttachPerformanceMonitor;
	static criAtom_DetachPerformanceMonitor_TYPE criAtom_DetachPerformanceMonitor;
	static criAtom_ResetPerformanceMonitor_TYPE criAtom_ResetPerformanceMonitor;
	static criAtom_GetPerformanceInfo_TYPE criAtom_GetPerformanceInfo;
	static criAtom_CalculateAdxBitrate_TYPE criAtom_CalculateAdxBitrate;
	static criAtom_CalculateHcaBitrate_TYPE criAtom_CalculateHcaBitrate;
	static criAtom_CalculateHcaMxBitrate_TYPE criAtom_CalculateHcaMxBitrate;
	static criAtom_GetStreamingInfo_TYPE criAtom_GetStreamingInfo;
	static criAtom_SetFreeTimeBufferingFlagForDefaultDevice_TYPE criAtom_SetFreeTimeBufferingFlagForDefaultDevice;
	static criAtomHcaMx_CalculateWorkSize_TYPE criAtomHcaMx_CalculateWorkSize;
	static criAtomHcaMx_SetConfigForWorkSizeCalculation_TYPE criAtomHcaMx_SetConfigForWorkSizeCalculation;
	static criAtomHcaMx_Initialize_TYPE criAtomHcaMx_Initialize;
	static criAtomHcaMx_Finalize_TYPE criAtomHcaMx_Finalize;
	static criAtomHcaMx_SetBusSendLevelByName_TYPE criAtomHcaMx_SetBusSendLevelByName;
	static criAtomHcaMx_SetFrequencyRatio_TYPE criAtomHcaMx_SetFrequencyRatio;
	static criAtomAwb_CalculateWorkSizeForLoadToc_TYPE criAtomAwb_CalculateWorkSizeForLoadToc;
	static criAtomAwb_LoadToc_TYPE criAtomAwb_LoadToc;
	static criAtomAwb_LoadTocById_TYPE criAtomAwb_LoadTocById;
	static criAtomAwb_LoadTocAsync_TYPE criAtomAwb_LoadTocAsync;
	static criAtomAwb_LoadTocAsyncById_TYPE criAtomAwb_LoadTocAsyncById;
	static criAtomAwb_LoadFromMemory_TYPE criAtomAwb_LoadFromMemory;
	static criAtomAwb_GetType_TYPE criAtomAwb_GetType;
	static criAtomAwb_GetWaveFileInfo_TYPE criAtomAwb_GetWaveFileInfo;
	static criAtomAwb_GetWaveDataInfo_TYPE criAtomAwb_GetWaveDataInfo;
	static criAtomAwb_GetNumContents_TYPE criAtomAwb_GetNumContents;
	static criAtomAwb_Release_TYPE criAtomAwb_Release;
	static criAtomAwb_IsReadyToRelease_TYPE criAtomAwb_IsReadyToRelease;
	static criAtomAwb_GetStatus_TYPE criAtomAwb_GetStatus;
	static criAtomPlayer_CalculateWorkSizeForStandardPlayer_TYPE criAtomPlayer_CalculateWorkSizeForStandardPlayer;
	static criAtomPlayer_CreateStandardPlayer_TYPE criAtomPlayer_CreateStandardPlayer;
	static criAtomPlayer_CalculateWorkSizeForAdxPlayer_TYPE criAtomPlayer_CalculateWorkSizeForAdxPlayer;
	static criAtomPlayer_CreateAdxPlayer_TYPE criAtomPlayer_CreateAdxPlayer;
	static criAtomPlayer_CalculateWorkSizeForHcaPlayer_TYPE criAtomPlayer_CalculateWorkSizeForHcaPlayer;
	static criAtomPlayer_CreateHcaPlayer_TYPE criAtomPlayer_CreateHcaPlayer;
	static criAtomPlayer_CalculateWorkSizeForHcaMxPlayer_TYPE criAtomPlayer_CalculateWorkSizeForHcaMxPlayer;
	static criAtomPlayer_CreateHcaMxPlayer_TYPE criAtomPlayer_CreateHcaMxPlayer;
	static criAtomPlayer_CalculateWorkSizeForWavePlayer_TYPE criAtomPlayer_CalculateWorkSizeForWavePlayer;
	static criAtomPlayer_CreateWavePlayer_TYPE criAtomPlayer_CreateWavePlayer;
	static criAtomPlayer_CalculateWorkSizeForAiffPlayer_TYPE criAtomPlayer_CalculateWorkSizeForAiffPlayer;
	static criAtomPlayer_CreateAiffPlayer_TYPE criAtomPlayer_CreateAiffPlayer;
	static criAtomPlayer_CalculateWorkSizeForRawPcmPlayer_TYPE criAtomPlayer_CalculateWorkSizeForRawPcmPlayer;
	static criAtomPlayer_CreateRawPcmPlayer_TYPE criAtomPlayer_CreateRawPcmPlayer;
	static criAtomPlayer_Destroy_TYPE criAtomPlayer_Destroy;
	static criAtomPlayer_SetData_TYPE criAtomPlayer_SetData;
	static criAtomPlayer_SetFile_TYPE criAtomPlayer_SetFile;
	static criAtomPlayer_SetContentId_TYPE criAtomPlayer_SetContentId;
	static criAtomPlayer_SetWaveId_TYPE criAtomPlayer_SetWaveId;
	static criAtomPlayer_SetPreviousDataAgain_TYPE criAtomPlayer_SetPreviousDataAgain;
	static criAtomPlayer_DeferCallback_TYPE criAtomPlayer_DeferCallback;
	static criAtomPlayer_Start_TYPE criAtomPlayer_Start;
	static criAtomPlayer_Stop_TYPE criAtomPlayer_Stop;
	static criAtomPlayer_Pause_TYPE criAtomPlayer_Pause;
	static criAtomPlayer_IsPaused_TYPE criAtomPlayer_IsPaused;
	static criAtomPlayer_GetStatus_TYPE criAtomPlayer_GetStatus;
	static criAtomPlayer_GetNumChannels_TYPE criAtomPlayer_GetNumChannels;
	static criAtomPlayer_GetNumPlayedSamples_TYPE criAtomPlayer_GetNumPlayedSamples;
	static criAtomPlayer_GetDecodedDataSize_TYPE criAtomPlayer_GetDecodedDataSize;
	static criAtomPlayer_GetNumDecodedSamples_TYPE criAtomPlayer_GetNumDecodedSamples;
	static criAtomPlayer_GetTime_TYPE criAtomPlayer_GetTime;
	static criAtomPlayer_GetFormatInfo_TYPE criAtomPlayer_GetFormatInfo;
	static criAtomPlayer_GetInputBufferRemainSize_TYPE criAtomPlayer_GetInputBufferRemainSize;
	static criAtomPlayer_GetOutputBufferRemainSamples_TYPE criAtomPlayer_GetOutputBufferRemainSamples;
	static criAtomPlayer_SetStartTime_TYPE criAtomPlayer_SetStartTime;
	static criAtomPlayer_SetVolume_TYPE criAtomPlayer_SetVolume;
	static criAtomPlayer_GetVolume_TYPE criAtomPlayer_GetVolume;
	static criAtomPlayer_SetChannelVolume_TYPE criAtomPlayer_SetChannelVolume;
	static criAtomPlayer_SetSendLevel_TYPE criAtomPlayer_SetSendLevel;
	static criAtomPlayer_ResetSendLevel_TYPE criAtomPlayer_ResetSendLevel;
	static criAtomPlayer_SetPanAdx1Compatible_TYPE criAtomPlayer_SetPanAdx1Compatible;
	static criAtomPlayer_ResetPan_TYPE criAtomPlayer_ResetPan;
	static criAtomPlayer_SetFrequencyRatio_TYPE criAtomPlayer_SetFrequencyRatio;
	static criAtomPlayer_SetMaxFrequencyRatio_TYPE criAtomPlayer_SetMaxFrequencyRatio;
	static criAtomPlayer_LimitLoopCount_TYPE criAtomPlayer_LimitLoopCount;
	static criAtomPlayer_SetHcaMxMixerId_TYPE criAtomPlayer_SetHcaMxMixerId;
	static criAtomPlayer_SetAsrRackId_TYPE criAtomPlayer_SetAsrRackId;
	static criAtomPlayer_SetRawPcmFormat_TYPE criAtomPlayer_SetRawPcmFormat;
	static criAtomPlayer_SetDataRequestCallback_TYPE criAtomPlayer_SetDataRequestCallback;
	static criAtomPlayer_SetStatusChangeCallback_TYPE criAtomPlayer_SetStatusChangeCallback;
	static criAtomPlayer_SetParameterChangeCallback_TYPE criAtomPlayer_SetParameterChangeCallback;
	static criAtomPlayer_SetFilterCallback_TYPE criAtomPlayer_SetFilterCallback;
	static criAtomPlayer_SetLoadRequestCallback_TYPE criAtomPlayer_SetLoadRequestCallback;
	static criAtomPlayer_SetHcaFormat_TYPE criAtomPlayer_SetHcaFormat;
	static criAtomDbas_CalculateWorkSize_TYPE criAtomDbas_CalculateWorkSize;
	static criAtomDbas_Create_TYPE criAtomDbas_Create;
	static criAtomDbas_Destroy_TYPE criAtomDbas_Destroy;
	static criAtomDbas_GetStreamingPlayerHandles_TYPE criAtomDbas_GetStreamingPlayerHandles;
	static criAtomStreamingCache_CalculateWorkSize_TYPE criAtomStreamingCache_CalculateWorkSize;
	static criAtomStreamingCache_Create_TYPE criAtomStreamingCache_Create;
	static criAtomStreamingCache_Destroy_TYPE criAtomStreamingCache_Destroy;
	static criAtomStreamingCache_Clear_TYPE criAtomStreamingCache_Clear;
	static criAtomStreamingCache_IsCachedWaveId_TYPE criAtomStreamingCache_IsCachedWaveId;
	static criAtomStreamingCache_IsCachedFile_TYPE criAtomStreamingCache_IsCachedFile;
	static criAtomMeter_CalculateWorkSizeForLevelMeter_TYPE criAtomMeter_CalculateWorkSizeForLevelMeter;
	static criAtomMeter_AttachLevelMeter_TYPE criAtomMeter_AttachLevelMeter;
	static criAtomMeter_DetachLevelMeter_TYPE criAtomMeter_DetachLevelMeter;
	static criAtomMeter_GetLevelInfo_TYPE criAtomMeter_GetLevelInfo;
	static criAtomMeter_CalculateWorkSizeForLoudnessMeter_TYPE criAtomMeter_CalculateWorkSizeForLoudnessMeter;
	static criAtomMeter_AttachLoudnessMeter_TYPE criAtomMeter_AttachLoudnessMeter;
	static criAtomMeter_DetachLoudnessMeter_TYPE criAtomMeter_DetachLoudnessMeter;
	static criAtomMeter_GetLoudnessInfo_TYPE criAtomMeter_GetLoudnessInfo;
	static criAtomMeter_ResetLoudnessMeter_TYPE criAtomMeter_ResetLoudnessMeter;
	static criAtomMeter_CalculateWorkSizeForTruePeakMeter_TYPE criAtomMeter_CalculateWorkSizeForTruePeakMeter;
	static criAtomMeter_AttachTruePeakMeter_TYPE criAtomMeter_AttachTruePeakMeter;
	static criAtomMeter_DetachTruePeakMeter_TYPE criAtomMeter_DetachTruePeakMeter;
	static criAtomMeter_GetTruePeakInfo_TYPE criAtomMeter_GetTruePeakInfo;
	static criAtomPlayer_SetDecodeCallback_TYPE criAtomPlayer_SetDecodeCallback;
	static criAtomPlayer_DiscardSamples_TYPE criAtomPlayer_DiscardSamples;
	static criAtomExAsr_CalculateWorkSize_TYPE criAtomExAsr_CalculateWorkSize;
	static criAtomExAsr_SetConfigForWorkSizeCalculation_TYPE criAtomExAsr_SetConfigForWorkSizeCalculation;
	static criAtomExAsr_Initialize_TYPE criAtomExAsr_Initialize;
	static criAtomExAsr_Finalize_TYPE criAtomExAsr_Finalize;
	static criAtomExAsr_SetBusVolumeByName_TYPE criAtomExAsr_SetBusVolumeByName;
	static criAtomExAsr_GetBusVolumeByName_TYPE criAtomExAsr_GetBusVolumeByName;
	static criAtomExAsr_SetBusPan3dByName_TYPE criAtomExAsr_SetBusPan3dByName;
	static criAtomExAsr_GetBusPan3dByName_TYPE criAtomExAsr_GetBusPan3dByName;
	static criAtomExAsr_SetBusMatrixByName_TYPE criAtomExAsr_SetBusMatrixByName;
	static criAtomExAsr_SetBusSendLevelByName_TYPE criAtomExAsr_SetBusSendLevelByName;
	static criAtomExAsr_SetEffectParameter_TYPE criAtomExAsr_SetEffectParameter;
	static criAtomExAsr_UpdateEffectParameters_TYPE criAtomExAsr_UpdateEffectParameters;
	static criAtomExAsr_GetEffectParameter_TYPE criAtomExAsr_GetEffectParameter;
	static criAtomExAsr_SetEffectBypass_TYPE criAtomExAsr_SetEffectBypass;
	static criAtomExAsr_AttachBusAnalyzerByName_TYPE criAtomExAsr_AttachBusAnalyzerByName;
	static criAtomExAsr_DetachBusAnalyzerByName_TYPE criAtomExAsr_DetachBusAnalyzerByName;
	static criAtomExAsr_GetBusAnalyzerInfoByName_TYPE criAtomExAsr_GetBusAnalyzerInfoByName;
	static criAtomExAsr_SetBusFilterCallbackByName_TYPE criAtomExAsr_SetBusFilterCallbackByName;
	static criAtomExAsr_GetNumBuses_TYPE criAtomExAsr_GetNumBuses;
	static criAtomExAsr_RegisterEffectInterface_TYPE criAtomExAsr_RegisterEffectInterface;
	static criAtomExAsr_UnregisterEffectInterface_TYPE criAtomExAsr_UnregisterEffectInterface;
	static criAtomExAsrRack_CalculateWorkSize_TYPE criAtomExAsrRack_CalculateWorkSize;
	static criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromConfig_TYPE criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromConfig;
	static criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromAcfDataAndConfig_TYPE criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromAcfDataAndConfig;
	static criAtomExAsrRack_Create_TYPE criAtomExAsrRack_Create;
	static criAtomExAsrRack_Destroy_TYPE criAtomExAsrRack_Destroy;
	static criAtomExAsrRack_CalculateWorkSizeForDspBusSetting_TYPE criAtomExAsrRack_CalculateWorkSizeForDspBusSetting;
	static criAtomExAsrRack_AttachDspBusSetting_TYPE criAtomExAsrRack_AttachDspBusSetting;
	static criAtomExAsrRack_DetachDspBusSetting_TYPE criAtomExAsrRack_DetachDspBusSetting;
	static criAtomExAsrRack_ApplyDspBusSnapshot_TYPE criAtomExAsrRack_ApplyDspBusSnapshot;
	static criAtomExAsrRack_GetAppliedDspBusSnapshotName_TYPE criAtomExAsrRack_GetAppliedDspBusSnapshotName;
	static criAtomExAsrRack_SetBusVolumeByName_TYPE criAtomExAsrRack_SetBusVolumeByName;
	static criAtomExAsrRack_GetBusVolumeByName_TYPE criAtomExAsrRack_GetBusVolumeByName;
	static criAtomExAsrRack_SetBusPan3dByName_TYPE criAtomExAsrRack_SetBusPan3dByName;
	static criAtomExAsrRack_GetBusPan3dByName_TYPE criAtomExAsrRack_GetBusPan3dByName;
	static criAtomExAsrRack_SetBusMatrixByName_TYPE criAtomExAsrRack_SetBusMatrixByName;
	static criAtomExAsrRack_SetBusSendLevelByName_TYPE criAtomExAsrRack_SetBusSendLevelByName;
	static criAtomExAsrRack_SetEffectParameter_TYPE criAtomExAsrRack_SetEffectParameter;
	static criAtomExAsrRack_UpdateEffectParameters_TYPE criAtomExAsrRack_UpdateEffectParameters;
	static criAtomExAsrRack_GetEffectParameter_TYPE criAtomExAsrRack_GetEffectParameter;
	static criAtomExAsrRack_SetEffectBypass_TYPE criAtomExAsrRack_SetEffectBypass;
	static criAtomExAsrRack_AttachBusAnalyzerByName_TYPE criAtomExAsrRack_AttachBusAnalyzerByName;
	static criAtomExAsrRack_DetachBusAnalyzerByName_TYPE criAtomExAsrRack_DetachBusAnalyzerByName;
	static criAtomExAsrRack_GetBusAnalyzerInfoByName_TYPE criAtomExAsrRack_GetBusAnalyzerInfoByName;
	static criAtomExAsrRack_SetBusFilterCallbackByName_TYPE criAtomExAsrRack_SetBusFilterCallbackByName;
	static criAtomExAsrRack_SetAlternateRackId_TYPE criAtomExAsrRack_SetAlternateRackId;
	static criAtomExAsrRack_GetNumBuses_TYPE criAtomExAsrRack_GetNumBuses;
	static criAtomExAsr_SetPcmBufferSize_TYPE criAtomExAsr_SetPcmBufferSize;
	static criAtomAsr_CalculateWorkSize_TYPE criAtomAsr_CalculateWorkSize;
	static criAtomAsr_Initialize_TYPE criAtomAsr_Initialize;
	static criAtomAsr_Finalize_TYPE criAtomAsr_Finalize;
	static criAtomEx_CalculateWorkSizeForUserPcmOutput_TYPE criAtomEx_CalculateWorkSizeForUserPcmOutput;
	static criAtomExAsr_PauseOutputVoice_TYPE criAtomExAsr_PauseOutputVoice;
	static criAtomExAsrRack_GetNumOutputSamples_TYPE criAtomExAsrRack_GetNumOutputSamples;
	static criAtomExAsrRack_GetOutputChannels_TYPE criAtomExAsrRack_GetOutputChannels;
	static criAtomExAsrRack_GetBusNumber_TYPE criAtomExAsrRack_GetBusNumber;
	static criAtomAsr_PauseOutputVoice_TYPE criAtomAsr_PauseOutputVoice;
	static criAtomExAsrRack_GetAmbisonicRackId_TYPE criAtomExAsrRack_GetAmbisonicRackId;
	static criAtomExAsr_SetDspParameter_TYPE criAtomExAsr_SetDspParameter;
	static criAtomExAsr_SetDspParameterByName_TYPE criAtomExAsr_SetDspParameterByName;
	static criAtomExAsr_GetDspParameter_TYPE criAtomExAsr_GetDspParameter;
	static criAtomExAsr_GetDspParameterByName_TYPE criAtomExAsr_GetDspParameterByName;
	static criAtomExAsr_SetDspBypass_TYPE criAtomExAsr_SetDspBypass;
	static criAtomExAsr_SetDspBypassByName_TYPE criAtomExAsr_SetDspBypassByName;
	static criAtomExAsr_SetBusVolume_TYPE criAtomExAsr_SetBusVolume;
	static criAtomExAsr_GetBusVolume_TYPE criAtomExAsr_GetBusVolume;
	static criAtomExAsr_SetBusPan3d_TYPE criAtomExAsr_SetBusPan3d;
	static criAtomExAsr_GetBusPan3d_TYPE criAtomExAsr_GetBusPan3d;
	static criAtomExAsr_SetBusMatrix_TYPE criAtomExAsr_SetBusMatrix;
	static criAtomExAsr_SetBusSendLevel_TYPE criAtomExAsr_SetBusSendLevel;
	static criAtomExAsr_AttachBusAnalyzer_TYPE criAtomExAsr_AttachBusAnalyzer;
	static criAtomExAsr_DetachBusAnalyzer_TYPE criAtomExAsr_DetachBusAnalyzer;
	static criAtomExAsr_GetBusAnalyzerInfo_TYPE criAtomExAsr_GetBusAnalyzerInfo;
	static criAtomExAsr_SetBusFilterCallback_TYPE criAtomExAsr_SetBusFilterCallback;
	static criAtomExAsrRack_SetDspParameter_TYPE criAtomExAsrRack_SetDspParameter;
	static criAtomExAsrRack_SetDspParameterByName_TYPE criAtomExAsrRack_SetDspParameterByName;
	static criAtomExAsrRack_GetDspParameter_TYPE criAtomExAsrRack_GetDspParameter;
	static criAtomExAsrRack_GetDspParameterByName_TYPE criAtomExAsrRack_GetDspParameterByName;
	static criAtomExAsrRack_SetDspBypass_TYPE criAtomExAsrRack_SetDspBypass;
	static criAtomExAsrRack_SetDspBypassByName_TYPE criAtomExAsrRack_SetDspBypassByName;
	static criAtomExAsrRack_SetBusVolume_TYPE criAtomExAsrRack_SetBusVolume;
	static criAtomExAsrRack_GetBusVolume_TYPE criAtomExAsrRack_GetBusVolume;
	static criAtomExAsrRack_SetBusPan3d_TYPE criAtomExAsrRack_SetBusPan3d;
	static criAtomExAsrRack_GetBusPan3d_TYPE criAtomExAsrRack_GetBusPan3d;
	static criAtomExAsrRack_SetBusMatrix_TYPE criAtomExAsrRack_SetBusMatrix;
	static criAtomExAsrRack_SetBusSendLevel_TYPE criAtomExAsrRack_SetBusSendLevel;
	static criAtomExAsrRack_AttachBusAnalyzer_TYPE criAtomExAsrRack_AttachBusAnalyzer;
	static criAtomExAsrRack_DetachBusAnalyzer_TYPE criAtomExAsrRack_DetachBusAnalyzer;
	static criAtomExAsrRack_GetBusAnalyzerInfo_TYPE criAtomExAsrRack_GetBusAnalyzerInfo;
	static criAtomExAsrRack_SetBusFilterCallback_TYPE criAtomExAsrRack_SetBusFilterCallback;
	static criAtomEx_CalculateWorkSize_TYPE criAtomEx_CalculateWorkSize;
	static criAtomEx_Initialize_TYPE criAtomEx_Initialize;
	static criAtomEx_Finalize_TYPE criAtomEx_Finalize;
	static criAtomEx_IsInitialized_TYPE criAtomEx_IsInitialized;
	static criAtomEx_ExecuteMain_TYPE criAtomEx_ExecuteMain;
	static criAtomEx_ExecuteAudioProcess_TYPE criAtomEx_ExecuteAudioProcess;
	static criAtomEx_Lock_TYPE criAtomEx_Lock;
	static criAtomEx_Unlock_TYPE criAtomEx_Unlock;
	static criAtomEx_GetTimeMicro_TYPE criAtomEx_GetTimeMicro;
	static criAtomEx_ResetTimer_TYPE criAtomEx_ResetTimer;
	static criAtomEx_PauseTimer_TYPE criAtomEx_PauseTimer;
	static criAtomEx_SetConfigForWorkSizeCalculation_TYPE criAtomEx_SetConfigForWorkSizeCalculation;
	static criAtomEx_CalculateWorkSizeForRegisterAcfData_TYPE criAtomEx_CalculateWorkSizeForRegisterAcfData;
	static criAtomEx_RegisterAcfData_TYPE criAtomEx_RegisterAcfData;
	static criAtomEx_CalculateWorkSizeForRegisterAcfFile_TYPE criAtomEx_CalculateWorkSizeForRegisterAcfFile;
	static criAtomEx_CalculateWorkSizeForRegisterAcfFileById_TYPE criAtomEx_CalculateWorkSizeForRegisterAcfFileById;
	static criAtomEx_RegisterAcfFile_TYPE criAtomEx_RegisterAcfFile;
	static criAtomEx_RegisterAcfFileById_TYPE criAtomEx_RegisterAcfFileById;
	static criAtomEx_UnregisterAcf_TYPE criAtomEx_UnregisterAcf;
	static criAtomEx_GetAcfVersion_TYPE criAtomEx_GetAcfVersion;
	static criAtomEx_GetAcfVersionFromFile_TYPE criAtomEx_GetAcfVersionFromFile;
	static criAtomEx_GetAcfVersionFromFileById_TYPE criAtomEx_GetAcfVersionFromFileById;
	static criAtomEx_GetSupportedAcfVersion_TYPE criAtomEx_GetSupportedAcfVersion;
	static criAtomEx_AnalyzeAudioHeader_TYPE criAtomEx_AnalyzeAudioHeader;
	static criAtomEx_SetRandomSeed_TYPE criAtomEx_SetRandomSeed;
	static criAtomEx_IsDataPlaying_TYPE criAtomEx_IsDataPlaying;
	static criAtomEx_CalculateWorkSizeForDspBusSetting_TYPE criAtomEx_CalculateWorkSizeForDspBusSetting;
	static criAtomEx_CalculateWorkSizeForDspBusSettingFromAcfData_TYPE criAtomEx_CalculateWorkSizeForDspBusSettingFromAcfData;
	static criAtomEx_AttachDspBusSetting_TYPE criAtomEx_AttachDspBusSetting;
	static criAtomEx_DetachDspBusSetting_TYPE criAtomEx_DetachDspBusSetting;
	static criAtomEx_ApplyDspBusSnapshot_TYPE criAtomEx_ApplyDspBusSnapshot;
	static criAtomEx_GetAppliedDspBusSnapshotName_TYPE criAtomEx_GetAppliedDspBusSnapshotName;
	static criAtomEx_SetCueLinkCallback_TYPE criAtomEx_SetCueLinkCallback;
	static criAtomEx_SetSpeakerAngles_TYPE criAtomEx_SetSpeakerAngles;
	static criAtomEx_SetSpeakerAngleArray_TYPE criAtomEx_SetSpeakerAngleArray;
	static criAtomEx_SetVirtualSpeakerAngleArray_TYPE criAtomEx_SetVirtualSpeakerAngleArray;
	static criAtomEx_ControlVirtualSpeakerSetting_TYPE criAtomEx_ControlVirtualSpeakerSetting;
	static criAtomEx_GetNumGameVariables_TYPE criAtomEx_GetNumGameVariables;
	static criAtomEx_GetGameVariableInfo_TYPE criAtomEx_GetGameVariableInfo;
	static criAtomEx_GetGameVariableById_TYPE criAtomEx_GetGameVariableById;
	static criAtomEx_GetGameVariableByName_TYPE criAtomEx_GetGameVariableByName;
	static criAtomEx_SetGameVariableById_TYPE criAtomEx_SetGameVariableById;
	static criAtomEx_SetGameVariableByName_TYPE criAtomEx_SetGameVariableByName;
	static criAtomEx_SetPlaybackCancelCallback_TYPE criAtomEx_SetPlaybackCancelCallback;
	static criAtomEx_ControlAcfConsistencyCheck_TYPE criAtomEx_ControlAcfConsistencyCheck;
	static criAtomEx_SetAcfConsistencyCheckErrorLevel_TYPE criAtomEx_SetAcfConsistencyCheckErrorLevel;
	static criAtomEx_SetTrackTransitionBySelectorCallback_TYPE criAtomEx_SetTrackTransitionBySelectorCallback;
	static criAtomExDebug_GetResourcesInfo_TYPE criAtomExDebug_GetResourcesInfo;
	static criAtomExHcaMx_CalculateWorkSize_TYPE criAtomExHcaMx_CalculateWorkSize;
	static criAtomExHcaMx_SetConfigForWorkSizeCalculation_TYPE criAtomExHcaMx_SetConfigForWorkSizeCalculation;
	static criAtomExHcaMx_Initialize_TYPE criAtomExHcaMx_Initialize;
	static criAtomExHcaMx_Finalize_TYPE criAtomExHcaMx_Finalize;
	static criAtomExHcaMx_SetBusSendLevelByName_TYPE criAtomExHcaMx_SetBusSendLevelByName;
	static criAtomExHcaMx_SetFrequencyRatio_TYPE criAtomExHcaMx_SetFrequencyRatio;
	static criAtomExHcaMx_SetAsrRackId_TYPE criAtomExHcaMx_SetAsrRackId;
	static criAtomExAcf_GetNumAisacControls_TYPE criAtomExAcf_GetNumAisacControls;
	static criAtomExAcf_GetAisacControlInfo_TYPE criAtomExAcf_GetAisacControlInfo;
	static criAtomExAcf_GetAisacControlIdByName_TYPE criAtomExAcf_GetAisacControlIdByName;
	static criAtomExAcf_GetAisacControlNameById_TYPE criAtomExAcf_GetAisacControlNameById;
	static criAtomExAcf_GetNumDspSettings_TYPE criAtomExAcf_GetNumDspSettings;
	static criAtomExAcf_GetNumDspSettingsFromAcfData_TYPE criAtomExAcf_GetNumDspSettingsFromAcfData;
	static criAtomExAcf_GetDspSettingNameByIndex_TYPE criAtomExAcf_GetDspSettingNameByIndex;
	static criAtomExAcf_GetDspSettingNameByIndexFromAcfData_TYPE criAtomExAcf_GetDspSettingNameByIndexFromAcfData;
	static criAtomExAcf_GetDspSettingInformation_TYPE criAtomExAcf_GetDspSettingInformation;
	static criAtomExAcf_GetDspSettingSnapshotInformation_TYPE criAtomExAcf_GetDspSettingSnapshotInformation;
	static criAtomExAcf_GetDspBusInformation_TYPE criAtomExAcf_GetDspBusInformation;
	static criAtomExAcf_GetDspFxType_TYPE criAtomExAcf_GetDspFxType;
	static criAtomExAcf_GetDspFxName_TYPE criAtomExAcf_GetDspFxName;
	static criAtomExAcf_GetDspFxParameters_TYPE criAtomExAcf_GetDspFxParameters;
	static criAtomExAcf_GetDspBusLinkInformation_TYPE criAtomExAcf_GetDspBusLinkInformation;
	static criAtomExAcf_GetNumCategoriesFromAcfData_TYPE criAtomExAcf_GetNumCategoriesFromAcfData;
	static criAtomExAcf_GetNumCategories_TYPE criAtomExAcf_GetNumCategories;
	static criAtomExAcf_GetNumCategoriesPerPlaybackFromAcfData_TYPE criAtomExAcf_GetNumCategoriesPerPlaybackFromAcfData;
	static criAtomExAcf_GetNumCategoriesPerPlayback_TYPE criAtomExAcf_GetNumCategoriesPerPlayback;
	static criAtomExAcf_GetCategoryInfo_TYPE criAtomExAcf_GetCategoryInfo;
	static criAtomExAcf_GetCategoryInfoByName_TYPE criAtomExAcf_GetCategoryInfoByName;
	static criAtomExAcf_GetCategoryInfoById_TYPE criAtomExAcf_GetCategoryInfoById;
	static criAtomExAcf_GetNumGlobalAisacs_TYPE criAtomExAcf_GetNumGlobalAisacs;
	static criAtomExAcf_GetGlobalAisacInfo_TYPE criAtomExAcf_GetGlobalAisacInfo;
	static criAtomExAcf_GetGlobalAisacInfoByName_TYPE criAtomExAcf_GetGlobalAisacInfoByName;
	static criAtomExAcf_GetGlobalAisacGraphInfo_TYPE criAtomExAcf_GetGlobalAisacGraphInfo;
	static criAtomExAcf_GetGlobalAisacValue_TYPE criAtomExAcf_GetGlobalAisacValue;
	static criAtomExAcf_GetAcfInfo_TYPE criAtomExAcf_GetAcfInfo;
	static criAtomExAcf_GetAcfInfoFromAcfData_TYPE criAtomExAcf_GetAcfInfoFromAcfData;
	static criAtomExAcf_GetNumSelectors_TYPE criAtomExAcf_GetNumSelectors;
	static criAtomExAcf_GetSelectorInfoByIndex_TYPE criAtomExAcf_GetSelectorInfoByIndex;
	static criAtomExAcf_GetSelectorInfoByName_TYPE criAtomExAcf_GetSelectorInfoByName;
	static criAtomExAcf_GetSelectorLabelInfo_TYPE criAtomExAcf_GetSelectorLabelInfo;
	static criAtomExAcf_SetGlobalLabelToSelectorByName_TYPE criAtomExAcf_SetGlobalLabelToSelectorByName;
	static criAtomExAcf_SetGlobalLabelToSelectorByIndex_TYPE criAtomExAcf_SetGlobalLabelToSelectorByIndex;
	static criAtomExAcf_GetNumBusesFromAcfData_TYPE criAtomExAcf_GetNumBusesFromAcfData;
	static criAtomExAcf_GetNumBuses_TYPE criAtomExAcf_GetNumBuses;
	static criAtomExAcf_GetMaxBusesOfDspBusSettingsFromAcfData_TYPE criAtomExAcf_GetMaxBusesOfDspBusSettingsFromAcfData;
	static criAtomExAcf_GetMaxBusesOfDspBusSettings_TYPE criAtomExAcf_GetMaxBusesOfDspBusSettings;
	static criAtomExAcf_FindBusName_TYPE criAtomExAcf_FindBusName;
	static criAtomExAcb_CalculateWorkSizeForLoadAcbData_TYPE criAtomExAcb_CalculateWorkSizeForLoadAcbData;
	static criAtomExAcb_CalculateWorkSizeForLoadAcbDataById_TYPE criAtomExAcb_CalculateWorkSizeForLoadAcbDataById;
	static criAtomExAcb_LoadAcbData_TYPE criAtomExAcb_LoadAcbData;
	static criAtomExAcb_LoadAcbDataById_TYPE criAtomExAcb_LoadAcbDataById;
	static criAtomExAcb_CalculateWorkSizeForLoadAcbFile_TYPE criAtomExAcb_CalculateWorkSizeForLoadAcbFile;
	static criAtomExAcb_CalculateWorkSizeForLoadAcbFileById_TYPE criAtomExAcb_CalculateWorkSizeForLoadAcbFileById;
	static criAtomExAcb_LoadAcbFile_TYPE criAtomExAcb_LoadAcbFile;
	static criAtomExAcb_LoadAcbFileById_TYPE criAtomExAcb_LoadAcbFileById;
	static criAtomExAcb_Release_TYPE criAtomExAcb_Release;
	static criAtomExAcb_IsReadyToRelease_TYPE criAtomExAcb_IsReadyToRelease;
	static criAtomExAcb_ReleaseAll_TYPE criAtomExAcb_ReleaseAll;
	static criAtomExAcb_EnumerateHandles_TYPE criAtomExAcb_EnumerateHandles;
	static criAtomExAcb_GetVersion_TYPE criAtomExAcb_GetVersion;
	static criAtomExAcb_GetVersionFromFile_TYPE criAtomExAcb_GetVersionFromFile;
	static criAtomExAcb_GetSupportedVersion_TYPE criAtomExAcb_GetSupportedVersion;
	static criAtomExAcb_GetNumCues_TYPE criAtomExAcb_GetNumCues;
	static criAtomExAcb_ExistsId_TYPE criAtomExAcb_ExistsId;
	static criAtomExAcb_ExistsName_TYPE criAtomExAcb_ExistsName;
	static criAtomExAcb_ExistsIndex_TYPE criAtomExAcb_ExistsIndex;
	static criAtomExAcb_GetCueIdByIndex_TYPE criAtomExAcb_GetCueIdByIndex;
	static criAtomExAcb_GetCueIdByName_TYPE criAtomExAcb_GetCueIdByName;
	static criAtomExAcb_GetCueNameByIndex_TYPE criAtomExAcb_GetCueNameByIndex;
	static criAtomExAcb_GetCueNameById_TYPE criAtomExAcb_GetCueNameById;
	static criAtomExAcb_GetCueIndexById_TYPE criAtomExAcb_GetCueIndexById;
	static criAtomExAcb_GetCueIndexByName_TYPE criAtomExAcb_GetCueIndexByName;
	static criAtomExAcb_GetUserDataById_TYPE criAtomExAcb_GetUserDataById;
	static criAtomExAcb_GetUserDataByName_TYPE criAtomExAcb_GetUserDataByName;
	static criAtomExAcb_GetLengthById_TYPE criAtomExAcb_GetLengthById;
	static criAtomExAcb_GetLengthByName_TYPE criAtomExAcb_GetLengthByName;
	static criAtomExAcb_GetNumUsableAisacControlsById_TYPE criAtomExAcb_GetNumUsableAisacControlsById;
	static criAtomExAcb_GetNumUsableAisacControlsByName_TYPE criAtomExAcb_GetNumUsableAisacControlsByName;
	static criAtomExAcb_GetUsableAisacControlById_TYPE criAtomExAcb_GetUsableAisacControlById;
	static criAtomExAcb_GetUsableAisacControlByName_TYPE criAtomExAcb_GetUsableAisacControlByName;
	static criAtomExAcb_IsUsingAisacControlById_TYPE criAtomExAcb_IsUsingAisacControlById;
	static criAtomExAcb_IsUsingAisacControlByName_TYPE criAtomExAcb_IsUsingAisacControlByName;
	static criAtomExAcb_GetCuePriorityById_TYPE criAtomExAcb_GetCuePriorityById;
	static criAtomExAcb_GetCuePriorityByName_TYPE criAtomExAcb_GetCuePriorityByName;
	static criAtomExAcb_GetWaveformInfoById_TYPE criAtomExAcb_GetWaveformInfoById;
	static criAtomExAcb_GetWaveformInfoByName_TYPE criAtomExAcb_GetWaveformInfoByName;
	static criAtomExAcb_GetOnMemoryAwbHandle_TYPE criAtomExAcb_GetOnMemoryAwbHandle;
	static criAtomExAcb_GetStreamingAwbHandle_TYPE criAtomExAcb_GetStreamingAwbHandle;
	static criAtomExAcb_GetCueInfoByName_TYPE criAtomExAcb_GetCueInfoByName;
	static criAtomExAcb_GetCueInfoById_TYPE criAtomExAcb_GetCueInfoById;
	static criAtomExAcb_GetCueInfoByIndex_TYPE criAtomExAcb_GetCueInfoByIndex;
	static criAtomExAcb_GetNumCuePlayingCountByName_TYPE criAtomExAcb_GetNumCuePlayingCountByName;
	static criAtomExAcb_GetNumCuePlayingCountById_TYPE criAtomExAcb_GetNumCuePlayingCountById;
	static criAtomExAcb_GetNumCuePlayingCountByIndex_TYPE criAtomExAcb_GetNumCuePlayingCountByIndex;
	static criAtomExAcb_GetBlockIndexByIndex_TYPE criAtomExAcb_GetBlockIndexByIndex;
	static criAtomExAcb_GetBlockIndexById_TYPE criAtomExAcb_GetBlockIndexById;
	static criAtomExAcb_GetBlockIndexByName_TYPE criAtomExAcb_GetBlockIndexByName;
	static criAtomExAcb_SetDetectionInGamePreviewDataCallback_TYPE criAtomExAcb_SetDetectionInGamePreviewDataCallback;
	static criAtomExAcb_GetAcbInfo_TYPE criAtomExAcb_GetAcbInfo;
	static criAtomExAcb_ResetCueTypeStateByName_TYPE criAtomExAcb_ResetCueTypeStateByName;
	static criAtomExAcb_ResetCueTypeStateById_TYPE criAtomExAcb_ResetCueTypeStateById;
	static criAtomExAcb_ResetCueTypeStateByIndex_TYPE criAtomExAcb_ResetCueTypeStateByIndex;
	static criAtomExAcb_AttachAwbFile_TYPE criAtomExAcb_AttachAwbFile;
	static criAtomExAcb_DetachAwbFile_TYPE criAtomExAcb_DetachAwbFile;
	static criAtomExAcb_CalculateWorkSizeForAttachAwbFile_TYPE criAtomExAcb_CalculateWorkSizeForAttachAwbFile;
	static criAtomExAcb_GetNumAwbFileSlots_TYPE criAtomExAcb_GetNumAwbFileSlots;
	static criAtomExAcb_GetAwbFileSlotName_TYPE criAtomExAcb_GetAwbFileSlotName;
	static criAtomExAcb_IsAttachedAwbFile_TYPE criAtomExAcb_IsAttachedAwbFile;
	static criAtomExVoicePool_CalculateWorkSizeForStandardVoicePool_TYPE criAtomExVoicePool_CalculateWorkSizeForStandardVoicePool;
	static criAtomExVoicePool_AllocateStandardVoicePool_TYPE criAtomExVoicePool_AllocateStandardVoicePool;
	static criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool_TYPE criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool;
	static criAtomExVoicePool_AllocateAdxVoicePool_TYPE criAtomExVoicePool_AllocateAdxVoicePool;
	static criAtomExVoicePool_CalculateWorkSizeForHcaVoicePool_TYPE criAtomExVoicePool_CalculateWorkSizeForHcaVoicePool;
	static criAtomExVoicePool_AllocateHcaVoicePool_TYPE criAtomExVoicePool_AllocateHcaVoicePool;
	static criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool_TYPE criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool;
	static criAtomExVoicePool_AllocateHcaMxVoicePool_TYPE criAtomExVoicePool_AllocateHcaMxVoicePool;
	static criAtomExVoicePool_CalculateWorkSizeForWaveVoicePool_TYPE criAtomExVoicePool_CalculateWorkSizeForWaveVoicePool;
	static criAtomExVoicePool_AllocateWaveVoicePool_TYPE criAtomExVoicePool_AllocateWaveVoicePool;
	static criAtomExVoicePool_CalculateWorkSizeForAiffVoicePool_TYPE criAtomExVoicePool_CalculateWorkSizeForAiffVoicePool;
	static criAtomExVoicePool_AllocateAiffVoicePool_TYPE criAtomExVoicePool_AllocateAiffVoicePool;
	static criAtomExVoicePool_CalculateWorkSizeForRawPcmVoicePool_TYPE criAtomExVoicePool_CalculateWorkSizeForRawPcmVoicePool;
	static criAtomExVoicePool_AllocateRawPcmVoicePool_TYPE criAtomExVoicePool_AllocateRawPcmVoicePool;
	static criAtomExVoicePool_Free_TYPE criAtomExVoicePool_Free;
	static criAtomExVoicePool_FreeAll_TYPE criAtomExVoicePool_FreeAll;
	static criAtomExVoicePool_GetNumUsedVoices_TYPE criAtomExVoicePool_GetNumUsedVoices;
	static criAtomExVoicePool_GetPlayerHandle_TYPE criAtomExVoicePool_GetPlayerHandle;
	static criAtomExCategory_SetVolumeById_TYPE criAtomExCategory_SetVolumeById;
	static criAtomExCategory_GetVolumeById_TYPE criAtomExCategory_GetVolumeById;
	static criAtomExCategory_GetTotalVolumeById_TYPE criAtomExCategory_GetTotalVolumeById;
	static criAtomExCategory_SetVolumeByName_TYPE criAtomExCategory_SetVolumeByName;
	static criAtomExCategory_GetVolumeByName_TYPE criAtomExCategory_GetVolumeByName;
	static criAtomExCategory_GetTotalVolumeByName_TYPE criAtomExCategory_GetTotalVolumeByName;
	static criAtomExCategory_MuteById_TYPE criAtomExCategory_MuteById;
	static criAtomExCategory_IsMutedById_TYPE criAtomExCategory_IsMutedById;
	static criAtomExCategory_MuteByName_TYPE criAtomExCategory_MuteByName;
	static criAtomExCategory_IsMutedByName_TYPE criAtomExCategory_IsMutedByName;
	static criAtomExCategory_SoloById_TYPE criAtomExCategory_SoloById;
	static criAtomExCategory_IsSoloedById_TYPE criAtomExCategory_IsSoloedById;
	static criAtomExCategory_SoloByName_TYPE criAtomExCategory_SoloByName;
	static criAtomExCategory_IsSoloedByName_TYPE criAtomExCategory_IsSoloedByName;
	static criAtomExCategory_PauseById_TYPE criAtomExCategory_PauseById;
	static criAtomExCategory_IsPausedById_TYPE criAtomExCategory_IsPausedById;
	static criAtomExCategory_PauseByName_TYPE criAtomExCategory_PauseByName;
	static criAtomExCategory_IsPausedByName_TYPE criAtomExCategory_IsPausedByName;
	static criAtomExCategory_SetFadeInTimeById_TYPE criAtomExCategory_SetFadeInTimeById;
	static criAtomExCategory_SetFadeInTimeByName_TYPE criAtomExCategory_SetFadeInTimeByName;
	static criAtomExCategory_SetFadeOutTimeById_TYPE criAtomExCategory_SetFadeOutTimeById;
	static criAtomExCategory_SetFadeOutTimeByName_TYPE criAtomExCategory_SetFadeOutTimeByName;
	static criAtomExCategory_SetAisacControlById_TYPE criAtomExCategory_SetAisacControlById;
	static criAtomExCategory_SetAisacControlByName_TYPE criAtomExCategory_SetAisacControlByName;
	static criAtomExCategory_ResetAllAisacControlById_TYPE criAtomExCategory_ResetAllAisacControlById;
	static criAtomExCategory_ResetAllAisacControlByName_TYPE criAtomExCategory_ResetAllAisacControlByName;
	static criAtomExCategory_AttachAisacById_TYPE criAtomExCategory_AttachAisacById;
	static criAtomExCategory_AttachAisacByName_TYPE criAtomExCategory_AttachAisacByName;
	static criAtomExCategory_DetachAisacById_TYPE criAtomExCategory_DetachAisacById;
	static criAtomExCategory_DetachAisacByName_TYPE criAtomExCategory_DetachAisacByName;
	static criAtomExCategory_DetachAisacAllById_TYPE criAtomExCategory_DetachAisacAllById;
	static criAtomExCategory_DetachAisacAllByName_TYPE criAtomExCategory_DetachAisacAllByName;
	static criAtomExCategory_GetNumAttachedAisacsById_TYPE criAtomExCategory_GetNumAttachedAisacsById;
	static criAtomExCategory_GetNumAttachedAisacsByName_TYPE criAtomExCategory_GetNumAttachedAisacsByName;
	static criAtomExCategory_GetAttachedAisacInfoById_TYPE criAtomExCategory_GetAttachedAisacInfoById;
	static criAtomExCategory_GetAttachedAisacInfoByName_TYPE criAtomExCategory_GetAttachedAisacInfoByName;
	static criAtomExCategory_GetCurrentAisacControlValueById_TYPE criAtomExCategory_GetCurrentAisacControlValueById;
	static criAtomExCategory_GetCurrentAisacControlValueByName_TYPE criAtomExCategory_GetCurrentAisacControlValueByName;
	static criAtomExCategory_GetNumCuePlayingCountById_TYPE criAtomExCategory_GetNumCuePlayingCountById;
	static criAtomExCategory_GetNumCuePlayingCountByName_TYPE criAtomExCategory_GetNumCuePlayingCountByName;
	static criAtomExCategory_StopById_TYPE criAtomExCategory_StopById;
	static criAtomExCategory_StopByName_TYPE criAtomExCategory_StopByName;
	static criAtomExCategory_StopWithoutReleaseTimeById_TYPE criAtomExCategory_StopWithoutReleaseTimeById;
	static criAtomExCategory_StopWithoutReleaseTimeByName_TYPE criAtomExCategory_StopWithoutReleaseTimeByName;
	static criAtomExPlayer_CalculateWorkSize_TYPE criAtomExPlayer_CalculateWorkSize;
	static criAtomExPlayer_Create_TYPE criAtomExPlayer_Create;
	static criAtomExPlayer_Destroy_TYPE criAtomExPlayer_Destroy;
	static criAtomExPlayer_SetCueId_TYPE criAtomExPlayer_SetCueId;
	static criAtomExPlayer_SetCueName_TYPE criAtomExPlayer_SetCueName;
	static criAtomExPlayer_SetCueIndex_TYPE criAtomExPlayer_SetCueIndex;
	static criAtomExPlayer_SetData_TYPE criAtomExPlayer_SetData;
	static criAtomExPlayer_SetFile_TYPE criAtomExPlayer_SetFile;
	static criAtomExPlayer_SetContentId_TYPE criAtomExPlayer_SetContentId;
	static criAtomExPlayer_SetWaveId_TYPE criAtomExPlayer_SetWaveId;
	static criAtomExPlayer_Start_TYPE criAtomExPlayer_Start;
	static criAtomExPlayer_Prepare_TYPE criAtomExPlayer_Prepare;
	static criAtomExPlayer_Stop_TYPE criAtomExPlayer_Stop;
	static criAtomExPlayer_StopWithoutReleaseTime_TYPE criAtomExPlayer_StopWithoutReleaseTime;
	static criAtomExPlayer_StopAllPlayers_TYPE criAtomExPlayer_StopAllPlayers;
	static criAtomExPlayer_StopAllPlayersWithoutReleaseTime_TYPE criAtomExPlayer_StopAllPlayersWithoutReleaseTime;
	static criAtomExPlayer_EnumeratePlayers_TYPE criAtomExPlayer_EnumeratePlayers;
	static criAtomExPlayer_Pause_TYPE criAtomExPlayer_Pause;
	static criAtomExPlayer_Resume_TYPE criAtomExPlayer_Resume;
	static criAtomExPlayer_IsPaused_TYPE criAtomExPlayer_IsPaused;
	static criAtomExPlayer_GetStatus_TYPE criAtomExPlayer_GetStatus;
	static criAtomExPlayer_GetNumPlaybacks_TYPE criAtomExPlayer_GetNumPlaybacks;
	static criAtomExPlayer_GetLastPlaybackId_TYPE criAtomExPlayer_GetLastPlaybackId;
	static criAtomExPlayer_GetTime_TYPE criAtomExPlayer_GetTime;
	static criAtomExPlayer_SetFormat_TYPE criAtomExPlayer_SetFormat;
	static criAtomExPlayer_SetNumChannels_TYPE criAtomExPlayer_SetNumChannels;
	static criAtomExPlayer_SetSamplingRate_TYPE criAtomExPlayer_SetSamplingRate;
	static criAtomExPlayer_SetSoundRendererType_TYPE criAtomExPlayer_SetSoundRendererType;
	static criAtomExPlayer_SetGroupNumber_TYPE criAtomExPlayer_SetGroupNumber;
	static criAtomExPlayer_SetVoiceControlMethod_TYPE criAtomExPlayer_SetVoiceControlMethod;
	static criAtomExPlayer_SetVoicePoolIdentifier_TYPE criAtomExPlayer_SetVoicePoolIdentifier;
	static criAtomExPlayer_SetHcaMxMixerId_TYPE criAtomExPlayer_SetHcaMxMixerId;
	static criAtomExPlayer_SetAsrRackId_TYPE criAtomExPlayer_SetAsrRackId;
	static criAtomExPlayer_SetAsrRackIdArray_TYPE criAtomExPlayer_SetAsrRackIdArray;
	static criAtomExPlayer_SetStartTime_TYPE criAtomExPlayer_SetStartTime;
	static criAtomExPlayer_SetSequencePrepareTime_TYPE criAtomExPlayer_SetSequencePrepareTime;
	static criAtomExPlayer_SetSyncPlaybackId_TYPE criAtomExPlayer_SetSyncPlaybackId;
	static criAtomExPlayer_SetPlaybackRatio_TYPE criAtomExPlayer_SetPlaybackRatio;
	static criAtomExPlayer_LimitLoopCount_TYPE criAtomExPlayer_LimitLoopCount;
	static criAtomExPlayer_UpdateAll_TYPE criAtomExPlayer_UpdateAll;
	static criAtomExPlayer_Update_TYPE criAtomExPlayer_Update;
	static criAtomExPlayer_ResetParameters_TYPE criAtomExPlayer_ResetParameters;
	static criAtomExPlayer_GetParameterFloat32_TYPE criAtomExPlayer_GetParameterFloat32;
	static criAtomExPlayer_GetParameterUint32_TYPE criAtomExPlayer_GetParameterUint32;
	static criAtomExPlayer_GetParameterSint32_TYPE criAtomExPlayer_GetParameterSint32;
	static criAtomExPlayer_SetVolume_TYPE criAtomExPlayer_SetVolume;
	static criAtomExPlayer_SetPitch_TYPE criAtomExPlayer_SetPitch;
	static criAtomExPlayer_SetMaxPitch_TYPE criAtomExPlayer_SetMaxPitch;
	static criAtomExPlayer_SetPan3dAngle_TYPE criAtomExPlayer_SetPan3dAngle;
	static criAtomExPlayer_SetPan3dInteriorDistance_TYPE criAtomExPlayer_SetPan3dInteriorDistance;
	static criAtomExPlayer_SetPan3dVolume_TYPE criAtomExPlayer_SetPan3dVolume;
	static criAtomExPlayer_SetPanType_TYPE criAtomExPlayer_SetPanType;
	static criAtomExPlayer_SetPanSpeakerType_TYPE criAtomExPlayer_SetPanSpeakerType;
	static criAtomExPlayer_AddMixDownCenterVolumeOffset_TYPE criAtomExPlayer_AddMixDownCenterVolumeOffset;
	static criAtomExPlayer_AddMixDownLfeVolumeOffset_TYPE criAtomExPlayer_AddMixDownLfeVolumeOffset;
	static criAtomExPlayer_ChangeDefaultPanSpeakerType_TYPE criAtomExPlayer_ChangeDefaultPanSpeakerType;
	static criAtomExPlayer_SetPanAngleType_TYPE criAtomExPlayer_SetPanAngleType;
	static criAtomExPlayer_SetPanSpread_TYPE criAtomExPlayer_SetPanSpread;
	static criAtomExPlayer_SetSendLevel_TYPE criAtomExPlayer_SetSendLevel;
	static criAtomExPlayer_SetBusSendLevelByName_TYPE criAtomExPlayer_SetBusSendLevelByName;
	static criAtomExPlayer_SetBusSendLevelOffsetByName_TYPE criAtomExPlayer_SetBusSendLevelOffsetByName;
	static criAtomExPlayer_SetPanAdx1Compatible_TYPE criAtomExPlayer_SetPanAdx1Compatible;
	static criAtomExPlayer_SetBandpassFilterParameters_TYPE criAtomExPlayer_SetBandpassFilterParameters;
	static criAtomExPlayer_SetBiquadFilterParameters_TYPE criAtomExPlayer_SetBiquadFilterParameters;
	static criAtomExPlayer_SetVoicePriority_TYPE criAtomExPlayer_SetVoicePriority;
	static criAtomExPlayer_SetAisacControlById_TYPE criAtomExPlayer_SetAisacControlById;
	static criAtomExPlayer_SetAisacControlByName_TYPE criAtomExPlayer_SetAisacControlByName;
	static criAtomExPlayer_ClearAisacControls_TYPE criAtomExPlayer_ClearAisacControls;
	static criAtomExPlayer_Set3dSourceHn_TYPE criAtomExPlayer_Set3dSourceHn;
	static criAtomExPlayer_Set3dSourceListHn_TYPE criAtomExPlayer_Set3dSourceListHn;
	static criAtomExPlayer_Set3dListenerHn_TYPE criAtomExPlayer_Set3dListenerHn;
	static criAtomExPlayer_GetAisacControlById_TYPE criAtomExPlayer_GetAisacControlById;
	static criAtomExPlayer_GetAisacControlByName_TYPE criAtomExPlayer_GetAisacControlByName;
	static criAtomExPlayer_SetCategoryById_TYPE criAtomExPlayer_SetCategoryById;
	static criAtomExPlayer_SetCategoryByName_TYPE criAtomExPlayer_SetCategoryByName;
	static criAtomExPlayer_UnsetCategory_TYPE criAtomExPlayer_UnsetCategory;
	static criAtomExPlayer_GetNumCategories_TYPE criAtomExPlayer_GetNumCategories;
	static criAtomExPlayer_GetCategoryInfo_TYPE criAtomExPlayer_GetCategoryInfo;
	static criAtomExPlayer_SetTrackInfo_TYPE criAtomExPlayer_SetTrackInfo;
	static criAtomExPlayer_SetTrackVolume_TYPE criAtomExPlayer_SetTrackVolume;
	static criAtomExPlayer_SetSilentMode_TYPE criAtomExPlayer_SetSilentMode;
	static criAtomExPlayer_SetCuePriority_TYPE criAtomExPlayer_SetCuePriority;
	static criAtomExPlayer_SetPreDelayTime_TYPE criAtomExPlayer_SetPreDelayTime;
	static criAtomExPlayer_SetEnvelopeAttackTime_TYPE criAtomExPlayer_SetEnvelopeAttackTime;
	static criAtomExPlayer_SetEnvelopeHoldTime_TYPE criAtomExPlayer_SetEnvelopeHoldTime;
	static criAtomExPlayer_SetEnvelopeDecayTime_TYPE criAtomExPlayer_SetEnvelopeDecayTime;
	static criAtomExPlayer_SetEnvelopeReleaseTime_TYPE criAtomExPlayer_SetEnvelopeReleaseTime;
	static criAtomExPlayer_SetEnvelopeSustainLevel_TYPE criAtomExPlayer_SetEnvelopeSustainLevel;
	static criAtomExPlayer_SetDataRequestCallback_TYPE criAtomExPlayer_SetDataRequestCallback;
	static criAtomExPlayer_SetFilterCallback_TYPE criAtomExPlayer_SetFilterCallback;
	static criAtomExPlayer_SetRandomSeed_TYPE criAtomExPlayer_SetRandomSeed;
	static criAtomExPlayer_SetDspParameter_TYPE criAtomExPlayer_SetDspParameter;
	static criAtomExPlayer_AttachAisac_TYPE criAtomExPlayer_AttachAisac;
	static criAtomExPlayer_AttachAisacByIndex_TYPE criAtomExPlayer_AttachAisacByIndex;
	static criAtomExPlayer_DetachAisac_TYPE criAtomExPlayer_DetachAisac;
	static criAtomExPlayer_DetachAisacByIndex_TYPE criAtomExPlayer_DetachAisacByIndex;
	static criAtomExPlayer_DetachAisacAll_TYPE criAtomExPlayer_DetachAisacAll;
	static criAtomExPlayer_GetNumAttachedAisacs_TYPE criAtomExPlayer_GetNumAttachedAisacs;
	static criAtomExPlayer_GetAttachedAisacInfo_TYPE criAtomExPlayer_GetAttachedAisacInfo;
	static criAtomExPlayer_SetStreamingCacheId_TYPE criAtomExPlayer_SetStreamingCacheId;
	static criAtomExPlayer_AttachTween_TYPE criAtomExPlayer_AttachTween;
	static criAtomExPlayer_DetachTween_TYPE criAtomExPlayer_DetachTween;
	static criAtomExPlayer_DetachTweenAll_TYPE criAtomExPlayer_DetachTweenAll;
	static criAtomExPlayer_SetFirstBlockIndex_TYPE criAtomExPlayer_SetFirstBlockIndex;
	static criAtomExPlayer_SetBlockTransitionCallback_TYPE criAtomExPlayer_SetBlockTransitionCallback;
	static criAtomExPlayer_GetSoundObject_TYPE criAtomExPlayer_GetSoundObject;
	static criAtomExPlayer_SetDrySendLevel_TYPE criAtomExPlayer_SetDrySendLevel;
	static criAtomExPlayer_SetSelectorLabel_TYPE criAtomExPlayer_SetSelectorLabel;
	static criAtomExPlayer_ClearSelectorLabels_TYPE criAtomExPlayer_ClearSelectorLabels;
	static criAtomExPlayer_SetPlaybackTrackInfoNotificationCallback_TYPE criAtomExPlayer_SetPlaybackTrackInfoNotificationCallback;
	static criAtomExPlayback_Stop_TYPE criAtomExPlayback_Stop;
	static criAtomExPlayback_StopWithoutReleaseTime_TYPE criAtomExPlayback_StopWithoutReleaseTime;
	static criAtomExPlayback_Pause_TYPE criAtomExPlayback_Pause;
	static criAtomExPlayback_Resume_TYPE criAtomExPlayback_Resume;
	static criAtomExPlayback_IsPaused_TYPE criAtomExPlayback_IsPaused;
	static criAtomExPlayback_GetStatus_TYPE criAtomExPlayback_GetStatus;
	static criAtomExPlayback_GetFormatInfo_TYPE criAtomExPlayback_GetFormatInfo;
	static criAtomExPlayback_GetSource_TYPE criAtomExPlayback_GetSource;
	static criAtomExPlayback_GetAtomPlayer_TYPE criAtomExPlayback_GetAtomPlayer;
	static criAtomExPlayback_GetTime_TYPE criAtomExPlayback_GetTime;
	static criAtomExPlayback_GetTimeSyncedWithAudio_TYPE criAtomExPlayback_GetTimeSyncedWithAudio;
	static criAtomExPlayback_GetTimeSyncedWithAudioMicro_TYPE criAtomExPlayback_GetTimeSyncedWithAudioMicro;
	static criAtomExPlayback_GetSequencePosition_TYPE criAtomExPlayback_GetSequencePosition;
	static criAtomExPlayback_GetNumPlayedSamples_TYPE criAtomExPlayback_GetNumPlayedSamples;
	static criAtomExPlayback_GetParameterFloat32_TYPE criAtomExPlayback_GetParameterFloat32;
	static criAtomExPlayback_GetParameterUint32_TYPE criAtomExPlayback_GetParameterUint32;
	static criAtomExPlayback_GetParameterSint32_TYPE criAtomExPlayback_GetParameterSint32;
	static criAtomExPlayback_GetAisacControlById_TYPE criAtomExPlayback_GetAisacControlById;
	static criAtomExPlayback_GetAisacControlByName_TYPE criAtomExPlayback_GetAisacControlByName;
	static criAtomExPlayback_SetNextBlockIndex_TYPE criAtomExPlayback_SetNextBlockIndex;
	static criAtomExPlayback_GetCurrentBlockIndex_TYPE criAtomExPlayback_GetCurrentBlockIndex;
	static criAtomExPlayback_GetPlaybackTrackInfo_TYPE criAtomExPlayback_GetPlaybackTrackInfo;
	static criAtomExPlayback_GetBeatSyncInfo_TYPE criAtomExPlayback_GetBeatSyncInfo;
	static criAtomExPlayer_CalculateWorkSizeForFader_TYPE criAtomExPlayer_CalculateWorkSizeForFader;
	static criAtomExPlayer_AttachFader_TYPE criAtomExPlayer_AttachFader;
	static criAtomExPlayer_DetachFader_TYPE criAtomExPlayer_DetachFader;
	static criAtomExPlayer_SetFadeOutTime_TYPE criAtomExPlayer_SetFadeOutTime;
	static criAtomExPlayer_GetFadeOutTime_TYPE criAtomExPlayer_GetFadeOutTime;
	static criAtomExPlayer_SetFadeInTime_TYPE criAtomExPlayer_SetFadeInTime;
	static criAtomExPlayer_GetFadeInTime_TYPE criAtomExPlayer_GetFadeInTime;
	static criAtomExPlayer_SetFadeInStartOffset_TYPE criAtomExPlayer_SetFadeInStartOffset;
	static criAtomExPlayer_GetFadeInStartOffset_TYPE criAtomExPlayer_GetFadeInStartOffset;
	static criAtomExPlayer_SetFadeOutEndDelay_TYPE criAtomExPlayer_SetFadeOutEndDelay;
	static criAtomExPlayer_GetFadeOutEndDelay_TYPE criAtomExPlayer_GetFadeOutEndDelay;
	static criAtomExPlayer_IsFading_TYPE criAtomExPlayer_IsFading;
	static criAtomExPlayer_ResetFaderParameters_TYPE criAtomExPlayer_ResetFaderParameters;
	static criAtomExSequencer_SetEventCallback_TYPE criAtomExSequencer_SetEventCallback;
	static criAtomExBeatSync_SetCallback_TYPE criAtomExBeatSync_SetCallback;
	static criAtomEx3dSource_CalculateWorkSize_TYPE criAtomEx3dSource_CalculateWorkSize;
	static criAtomEx3dSource_Create_TYPE criAtomEx3dSource_Create;
	static criAtomEx3dSource_Destroy_TYPE criAtomEx3dSource_Destroy;
	static criAtomEx3dSource_Update_TYPE criAtomEx3dSource_Update;
	static criAtomEx3dSource_ResetParameters_TYPE criAtomEx3dSource_ResetParameters;
	static criAtomEx3dSource_SetPosition_TYPE criAtomEx3dSource_SetPosition;
	static criAtomEx3dSource_GetPosition_TYPE criAtomEx3dSource_GetPosition;
	static criAtomEx3dSource_SetVelocity_TYPE criAtomEx3dSource_SetVelocity;
	static criAtomEx3dSource_SetOrientation_TYPE criAtomEx3dSource_SetOrientation;
	static criAtomEx3dSource_SetConeParameter_TYPE criAtomEx3dSource_SetConeParameter;
	static criAtomEx3dSource_ChangeDefaultConeParameter_TYPE criAtomEx3dSource_ChangeDefaultConeParameter;
	static criAtomEx3dSource_SetMinMaxAttenuationDistance_TYPE criAtomEx3dSource_SetMinMaxAttenuationDistance;
	static criAtomEx3dSource_ChangeDefaultMinMaxAttenuationDistance_TYPE criAtomEx3dSource_ChangeDefaultMinMaxAttenuationDistance;
	static criAtomEx3dSource_SetInteriorPanField_TYPE criAtomEx3dSource_SetInteriorPanField;
	static criAtomEx3dSource_ChangeDefaultInteriorPanField_TYPE criAtomEx3dSource_ChangeDefaultInteriorPanField;
	static criAtomEx3dSource_SetDopplerFactor_TYPE criAtomEx3dSource_SetDopplerFactor;
	static criAtomEx3dSource_ChangeDefaultDopplerFactor_TYPE criAtomEx3dSource_ChangeDefaultDopplerFactor;
	static criAtomEx3dSource_SetVolume_TYPE criAtomEx3dSource_SetVolume;
	static criAtomEx3dSource_ChangeDefaultVolume_TYPE criAtomEx3dSource_ChangeDefaultVolume;
	static criAtomEx3dSource_SetMaxAngleAisacDelta_TYPE criAtomEx3dSource_SetMaxAngleAisacDelta;
	static criAtomEx3dSource_SetDistanceAisacControlId_TYPE criAtomEx3dSource_SetDistanceAisacControlId;
	static criAtomEx3dSource_SetListenerBasedAngleAisacControlId_TYPE criAtomEx3dSource_SetListenerBasedAngleAisacControlId;
	static criAtomEx3dSource_SetSourceBasedAngleAisacControlId_TYPE criAtomEx3dSource_SetSourceBasedAngleAisacControlId;
	static criAtomEx3dSourceList_CalculateWorkSize_TYPE criAtomEx3dSourceList_CalculateWorkSize;
	static criAtomEx3dSourceList_Create_TYPE criAtomEx3dSourceList_Create;
	static criAtomEx3dSourceList_Destroy_TYPE criAtomEx3dSourceList_Destroy;
	static criAtomEx3dSourceList_Add_TYPE criAtomEx3dSourceList_Add;
	static criAtomEx3dSourceList_Remove_TYPE criAtomEx3dSourceList_Remove;
	static criAtomEx3dSourceList_RemoveAll_TYPE criAtomEx3dSourceList_RemoveAll;
	static criAtomEx3dListener_CalculateWorkSize_TYPE criAtomEx3dListener_CalculateWorkSize;
	static criAtomEx3dListener_Create_TYPE criAtomEx3dListener_Create;
	static criAtomEx3dListener_Destroy_TYPE criAtomEx3dListener_Destroy;
	static criAtomEx3dListener_Update_TYPE criAtomEx3dListener_Update;
	static criAtomEx3dListener_ResetParameters_TYPE criAtomEx3dListener_ResetParameters;
	static criAtomEx3dListener_SetPosition_TYPE criAtomEx3dListener_SetPosition;
	static criAtomEx3dListener_GetPosition_TYPE criAtomEx3dListener_GetPosition;
	static criAtomEx3dListener_SetVelocity_TYPE criAtomEx3dListener_SetVelocity;
	static criAtomEx3dListener_SetOrientation_TYPE criAtomEx3dListener_SetOrientation;
	static criAtomEx3dListener_SetDistanceFactor_TYPE criAtomEx3dListener_SetDistanceFactor;
	static criAtomEx3dListener_SetFocusPoint_TYPE criAtomEx3dListener_SetFocusPoint;
	static criAtomEx3dListener_SetDistanceFocusLevel_TYPE criAtomEx3dListener_SetDistanceFocusLevel;
	static criAtomEx3dListener_SetDirectionFocusLevel_TYPE criAtomEx3dListener_SetDirectionFocusLevel;
	static criAtomExVoicePool_DetachDsp_TYPE criAtomExVoicePool_DetachDsp;
	static criAtomExVoicePool_CalculateWorkSizeForDspPitchShifter_TYPE criAtomExVoicePool_CalculateWorkSizeForDspPitchShifter;
	static criAtomExVoicePool_AttachDspPitchShifter_TYPE criAtomExVoicePool_AttachDspPitchShifter;
	static criAtomExVoicePool_CalculateWorkSizeForDspTimeStretch_TYPE criAtomExVoicePool_CalculateWorkSizeForDspTimeStretch;
	static criAtomExVoicePool_AttachDspTimeStretch_TYPE criAtomExVoicePool_AttachDspTimeStretch;
	static criAtomExStreamingCache_IsCachedWaveformById_TYPE criAtomExStreamingCache_IsCachedWaveformById;
	static criAtomExStreamingCache_IsCachedWaveformByName_TYPE criAtomExStreamingCache_IsCachedWaveformByName;
	static criAtomExStreamingCache_LoadWaveformById_TYPE criAtomExStreamingCache_LoadWaveformById;
	static criAtomExStreamingCache_LoadWaveformByName_TYPE criAtomExStreamingCache_LoadWaveformByName;
	static criAtomExTween_CalculateWorkSize_TYPE criAtomExTween_CalculateWorkSize;
	static criAtomExTween_Create_TYPE criAtomExTween_Create;
	static criAtomExTween_Destroy_TYPE criAtomExTween_Destroy;
	static criAtomExTween_GetValue_TYPE criAtomExTween_GetValue;
	static criAtomExTween_MoveTo_TYPE criAtomExTween_MoveTo;
	static criAtomExTween_MoveFrom_TYPE criAtomExTween_MoveFrom;
	static criAtomExTween_Stop_TYPE criAtomExTween_Stop;
	static criAtomExTween_Reset_TYPE criAtomExTween_Reset;
	static criAtomEx_SetVoiceEventCallback_TYPE criAtomEx_SetVoiceEventCallback;
	static criAtomEx_EnumerateVoiceInfos_TYPE criAtomEx_EnumerateVoiceInfos;
	static criAtomEx_SetMonitoringVoiceStopCallback_TYPE criAtomEx_SetMonitoringVoiceStopCallback;
	static criAtomEx_SetMonitoringVoiceStopPlaybackId_TYPE criAtomEx_SetMonitoringVoiceStopPlaybackId;
	static criAtomExSoundObject_CalculateWorkSize_TYPE criAtomExSoundObject_CalculateWorkSize;
	static criAtomExSoundObject_Create_TYPE criAtomExSoundObject_Create;
	static criAtomExSoundObject_Destroy_TYPE criAtomExSoundObject_Destroy;
	static criAtomExSoundObject_AddPlayer_TYPE criAtomExSoundObject_AddPlayer;
	static criAtomExSoundObject_DeletePlayer_TYPE criAtomExSoundObject_DeletePlayer;
	static criAtomExSoundObject_DeleteAllPlayers_TYPE criAtomExSoundObject_DeleteAllPlayers;
	static criAtomExPlayer_GetTimeReal_TYPE criAtomExPlayer_GetTimeReal;
	static criAtomExPlayback_GetTimeReal_TYPE criAtomExPlayback_GetTimeReal;
	static criAtomExPlayback_EnumerateAtomPlayers_TYPE criAtomExPlayback_EnumerateAtomPlayers;
	static criAtomEx3dListener_GetFocusPoint_TYPE criAtomEx3dListener_GetFocusPoint;
	static criAtomEx3dListener_GetDistanceFocusLevel_TYPE criAtomEx3dListener_GetDistanceFocusLevel;
	static criAtomEx3dListener_GetDirectionFocusLevel_TYPE criAtomEx3dListener_GetDirectionFocusLevel;
	static criAtomExAcb_GetCurrentAcb_TYPE criAtomExAcb_GetCurrentAcb;
	static criAtomEx3dSource_SetAttenuationDistanceSetting_TYPE criAtomEx3dSource_SetAttenuationDistanceSetting;
	static criAtomEx3dSource_GetAttenuationDistanceSetting_TYPE criAtomEx3dSource_GetAttenuationDistanceSetting;
	static criAtomExPlayer_SetBusSendLevel_TYPE criAtomExPlayer_SetBusSendLevel;
	static criAtomExPlayer_SetBusSendLevelOffset_TYPE criAtomExPlayer_SetBusSendLevelOffset;
	static criAtomEx_GetNumUsedVirtualVoices_TYPE criAtomEx_GetNumUsedVirtualVoices;
	static criAtomEx_GetNumUsedSequences_TYPE criAtomEx_GetNumUsedSequences;
	static criAtomEx_GetNumUsedSequenceTracks_TYPE criAtomEx_GetNumUsedSequenceTracks;
	static criAtomEx_GetNumUsedSequenceTrackItems_TYPE criAtomEx_GetNumUsedSequenceTrackItems;
	static criAtomEx_GetNumUsedAisacAutoModulations_TYPE criAtomEx_GetNumUsedAisacAutoModulations;
	static criAtomEx3dSource_SetConeOrientation_TYPE criAtomEx3dSource_SetConeOrientation;
	static criAtomExMonitor_CalculateWorkSize_TYPE criAtomExMonitor_CalculateWorkSize;
	static criAtomExMonitor_Initialize_TYPE criAtomExMonitor_Initialize;
	static criAtomExMonitor_Finalize_TYPE criAtomExMonitor_Finalize;
	static criAtomExMonitor_GetServerIpString_TYPE criAtomExMonitor_GetServerIpString;
	static criAtomExMonitor_GetClientIpString_TYPE criAtomExMonitor_GetClientIpString;
	static criAtomExMonitor_IsConnected_TYPE criAtomExMonitor_IsConnected;
	static criAtomExMonitor_SetLogCallback_TYPE criAtomExMonitor_SetLogCallback;
	static criAtomExMonitor_SetLogMode_TYPE criAtomExMonitor_SetLogMode;
	static criAtomExMonitor_OutputUserLog_TYPE criAtomExMonitor_OutputUserLog;
	static criAtomExMonitor_SetDataUpdateNotificationCallback_TYPE criAtomExMonitor_SetDataUpdateNotificationCallback;
};
/***************************************************************************
 *      Compatible Macro
 ***************************************************************************/
#if defined(CRIWARE_DEFINE_COMPATIBLE_MACRO)
#define criErr_ConvertIdToMsg FCriWareApi::criErr_ConvertIdToMsg
#define criErr_ConvertIdToMessage FCriWareApi::criErr_ConvertIdToMessage
#define criErr_SetCallback FCriWareApi::criErr_SetCallback
#define criErr_SetErrorNotificationLevel FCriWareApi::criErr_SetErrorNotificationLevel
#define criErr_GetErrorCount FCriWareApi::criErr_GetErrorCount
#define criErr_ResetErrorCount FCriWareApi::criErr_ResetErrorCount
#define criFs_SetUserMallocFunction FCriWareApi::criFs_SetUserMallocFunction
#define criFs_SetUserFreeFunction FCriWareApi::criFs_SetUserFreeFunction
#define criFs_SetSelectIoCallback FCriWareApi::criFs_SetSelectIoCallback
#define criAtom_GetVersionNumber FCriWareApi::criAtom_GetVersionNumber
#define criAtom_CalculateWorkSize FCriWareApi::criAtom_CalculateWorkSize
#define criAtom_Initialize FCriWareApi::criAtom_Initialize
#define criAtom_Finalize FCriWareApi::criAtom_Finalize
#define criAtom_IsInitialized FCriWareApi::criAtom_IsInitialized
#define criAtom_IsAudioOutputActive FCriWareApi::criAtom_IsAudioOutputActive
#define criAtom_ExecuteMain FCriWareApi::criAtom_ExecuteMain
#define criAtom_ExecuteAudioProcess FCriWareApi::criAtom_ExecuteAudioProcess
#define criAtom_SetUserMallocFunction FCriWareApi::criAtom_SetUserMallocFunction
#define criAtom_SetUserFreeFunction FCriWareApi::criAtom_SetUserFreeFunction
#define criAtom_SetAudioFrameStartCallback FCriWareApi::criAtom_SetAudioFrameStartCallback
#define criAtom_SetAudioFrameEndCallback FCriWareApi::criAtom_SetAudioFrameEndCallback
#define criAtom_Lock FCriWareApi::criAtom_Lock
#define criAtom_Unlock FCriWareApi::criAtom_Unlock
#define criAtom_SetChannelMapping FCriWareApi::criAtom_SetChannelMapping
#define criAtom_AttachPerformanceMonitor FCriWareApi::criAtom_AttachPerformanceMonitor
#define criAtom_DetachPerformanceMonitor FCriWareApi::criAtom_DetachPerformanceMonitor
#define criAtom_ResetPerformanceMonitor FCriWareApi::criAtom_ResetPerformanceMonitor
#define criAtom_GetPerformanceInfo FCriWareApi::criAtom_GetPerformanceInfo
#define criAtom_CalculateAdxBitrate FCriWareApi::criAtom_CalculateAdxBitrate
#define criAtom_CalculateHcaBitrate FCriWareApi::criAtom_CalculateHcaBitrate
#define criAtom_CalculateHcaMxBitrate FCriWareApi::criAtom_CalculateHcaMxBitrate
#define criAtom_GetStreamingInfo FCriWareApi::criAtom_GetStreamingInfo
#define criAtom_SetFreeTimeBufferingFlagForDefaultDevice FCriWareApi::criAtom_SetFreeTimeBufferingFlagForDefaultDevice
#define criAtomHcaMx_CalculateWorkSize FCriWareApi::criAtomHcaMx_CalculateWorkSize
#define criAtomHcaMx_SetConfigForWorkSizeCalculation FCriWareApi::criAtomHcaMx_SetConfigForWorkSizeCalculation
#define criAtomHcaMx_Initialize FCriWareApi::criAtomHcaMx_Initialize
#define criAtomHcaMx_Finalize FCriWareApi::criAtomHcaMx_Finalize
#define criAtomHcaMx_SetBusSendLevelByName FCriWareApi::criAtomHcaMx_SetBusSendLevelByName
#define criAtomHcaMx_SetFrequencyRatio FCriWareApi::criAtomHcaMx_SetFrequencyRatio
#define criAtomAwb_CalculateWorkSizeForLoadToc FCriWareApi::criAtomAwb_CalculateWorkSizeForLoadToc
#define criAtomAwb_LoadToc FCriWareApi::criAtomAwb_LoadToc
#define criAtomAwb_LoadTocById FCriWareApi::criAtomAwb_LoadTocById
#define criAtomAwb_LoadTocAsync FCriWareApi::criAtomAwb_LoadTocAsync
#define criAtomAwb_LoadTocAsyncById FCriWareApi::criAtomAwb_LoadTocAsyncById
#define criAtomAwb_LoadFromMemory FCriWareApi::criAtomAwb_LoadFromMemory
#define criAtomAwb_GetType FCriWareApi::criAtomAwb_GetType
#define criAtomAwb_GetWaveFileInfo FCriWareApi::criAtomAwb_GetWaveFileInfo
#define criAtomAwb_GetWaveDataInfo FCriWareApi::criAtomAwb_GetWaveDataInfo
#define criAtomAwb_GetNumContents FCriWareApi::criAtomAwb_GetNumContents
#define criAtomAwb_Release FCriWareApi::criAtomAwb_Release
#define criAtomAwb_IsReadyToRelease FCriWareApi::criAtomAwb_IsReadyToRelease
#define criAtomAwb_GetStatus FCriWareApi::criAtomAwb_GetStatus
#define criAtomPlayer_CalculateWorkSizeForStandardPlayer FCriWareApi::criAtomPlayer_CalculateWorkSizeForStandardPlayer
#define criAtomPlayer_CreateStandardPlayer FCriWareApi::criAtomPlayer_CreateStandardPlayer
#define criAtomPlayer_CalculateWorkSizeForAdxPlayer FCriWareApi::criAtomPlayer_CalculateWorkSizeForAdxPlayer
#define criAtomPlayer_CreateAdxPlayer FCriWareApi::criAtomPlayer_CreateAdxPlayer
#define criAtomPlayer_CalculateWorkSizeForHcaPlayer FCriWareApi::criAtomPlayer_CalculateWorkSizeForHcaPlayer
#define criAtomPlayer_CreateHcaPlayer FCriWareApi::criAtomPlayer_CreateHcaPlayer
#define criAtomPlayer_CalculateWorkSizeForHcaMxPlayer FCriWareApi::criAtomPlayer_CalculateWorkSizeForHcaMxPlayer
#define criAtomPlayer_CreateHcaMxPlayer FCriWareApi::criAtomPlayer_CreateHcaMxPlayer
#define criAtomPlayer_CalculateWorkSizeForWavePlayer FCriWareApi::criAtomPlayer_CalculateWorkSizeForWavePlayer
#define criAtomPlayer_CreateWavePlayer FCriWareApi::criAtomPlayer_CreateWavePlayer
#define criAtomPlayer_CalculateWorkSizeForAiffPlayer FCriWareApi::criAtomPlayer_CalculateWorkSizeForAiffPlayer
#define criAtomPlayer_CreateAiffPlayer FCriWareApi::criAtomPlayer_CreateAiffPlayer
#define criAtomPlayer_CalculateWorkSizeForRawPcmPlayer FCriWareApi::criAtomPlayer_CalculateWorkSizeForRawPcmPlayer
#define criAtomPlayer_CreateRawPcmPlayer FCriWareApi::criAtomPlayer_CreateRawPcmPlayer
#define criAtomPlayer_Destroy FCriWareApi::criAtomPlayer_Destroy
#define criAtomPlayer_SetData FCriWareApi::criAtomPlayer_SetData
#define criAtomPlayer_SetFile FCriWareApi::criAtomPlayer_SetFile
#define criAtomPlayer_SetContentId FCriWareApi::criAtomPlayer_SetContentId
#define criAtomPlayer_SetWaveId FCriWareApi::criAtomPlayer_SetWaveId
#define criAtomPlayer_SetPreviousDataAgain FCriWareApi::criAtomPlayer_SetPreviousDataAgain
#define criAtomPlayer_DeferCallback FCriWareApi::criAtomPlayer_DeferCallback
#define criAtomPlayer_Start FCriWareApi::criAtomPlayer_Start
#define criAtomPlayer_Stop FCriWareApi::criAtomPlayer_Stop
#define criAtomPlayer_Pause FCriWareApi::criAtomPlayer_Pause
#define criAtomPlayer_IsPaused FCriWareApi::criAtomPlayer_IsPaused
#define criAtomPlayer_GetStatus FCriWareApi::criAtomPlayer_GetStatus
#define criAtomPlayer_GetNumChannels FCriWareApi::criAtomPlayer_GetNumChannels
#define criAtomPlayer_GetNumPlayedSamples FCriWareApi::criAtomPlayer_GetNumPlayedSamples
#define criAtomPlayer_GetDecodedDataSize FCriWareApi::criAtomPlayer_GetDecodedDataSize
#define criAtomPlayer_GetNumDecodedSamples FCriWareApi::criAtomPlayer_GetNumDecodedSamples
#define criAtomPlayer_GetTime FCriWareApi::criAtomPlayer_GetTime
#define criAtomPlayer_GetFormatInfo FCriWareApi::criAtomPlayer_GetFormatInfo
#define criAtomPlayer_GetInputBufferRemainSize FCriWareApi::criAtomPlayer_GetInputBufferRemainSize
#define criAtomPlayer_GetOutputBufferRemainSamples FCriWareApi::criAtomPlayer_GetOutputBufferRemainSamples
#define criAtomPlayer_SetStartTime FCriWareApi::criAtomPlayer_SetStartTime
#define criAtomPlayer_SetVolume FCriWareApi::criAtomPlayer_SetVolume
#define criAtomPlayer_GetVolume FCriWareApi::criAtomPlayer_GetVolume
#define criAtomPlayer_SetChannelVolume FCriWareApi::criAtomPlayer_SetChannelVolume
#define criAtomPlayer_SetSendLevel FCriWareApi::criAtomPlayer_SetSendLevel
#define criAtomPlayer_ResetSendLevel FCriWareApi::criAtomPlayer_ResetSendLevel
#define criAtomPlayer_SetPanAdx1Compatible FCriWareApi::criAtomPlayer_SetPanAdx1Compatible
#define criAtomPlayer_ResetPan FCriWareApi::criAtomPlayer_ResetPan
#define criAtomPlayer_SetFrequencyRatio FCriWareApi::criAtomPlayer_SetFrequencyRatio
#define criAtomPlayer_SetMaxFrequencyRatio FCriWareApi::criAtomPlayer_SetMaxFrequencyRatio
#define criAtomPlayer_LimitLoopCount FCriWareApi::criAtomPlayer_LimitLoopCount
#define criAtomPlayer_SetHcaMxMixerId FCriWareApi::criAtomPlayer_SetHcaMxMixerId
#define criAtomPlayer_SetAsrRackId FCriWareApi::criAtomPlayer_SetAsrRackId
#define criAtomPlayer_SetRawPcmFormat FCriWareApi::criAtomPlayer_SetRawPcmFormat
#define criAtomPlayer_SetDataRequestCallback FCriWareApi::criAtomPlayer_SetDataRequestCallback
#define criAtomPlayer_SetStatusChangeCallback FCriWareApi::criAtomPlayer_SetStatusChangeCallback
#define criAtomPlayer_SetParameterChangeCallback FCriWareApi::criAtomPlayer_SetParameterChangeCallback
#define criAtomPlayer_SetFilterCallback FCriWareApi::criAtomPlayer_SetFilterCallback
#define criAtomPlayer_SetLoadRequestCallback FCriWareApi::criAtomPlayer_SetLoadRequestCallback
#define criAtomDbas_CalculateWorkSize FCriWareApi::criAtomDbas_CalculateWorkSize
#define criAtomDbas_Create FCriWareApi::criAtomDbas_Create
#define criAtomDbas_Destroy FCriWareApi::criAtomDbas_Destroy
#define criAtomDbas_GetStreamingPlayerHandles FCriWareApi::criAtomDbas_GetStreamingPlayerHandles
#define criAtomStreamingCache_CalculateWorkSize FCriWareApi::criAtomStreamingCache_CalculateWorkSize
#define criAtomStreamingCache_Create FCriWareApi::criAtomStreamingCache_Create
#define criAtomStreamingCache_Destroy FCriWareApi::criAtomStreamingCache_Destroy
#define criAtomStreamingCache_Clear FCriWareApi::criAtomStreamingCache_Clear
#define criAtomStreamingCache_IsCachedWaveId FCriWareApi::criAtomStreamingCache_IsCachedWaveId
#define criAtomStreamingCache_IsCachedFile FCriWareApi::criAtomStreamingCache_IsCachedFile
#define criAtomMeter_CalculateWorkSizeForLevelMeter FCriWareApi::criAtomMeter_CalculateWorkSizeForLevelMeter
#define criAtomMeter_AttachLevelMeter FCriWareApi::criAtomMeter_AttachLevelMeter
#define criAtomMeter_DetachLevelMeter FCriWareApi::criAtomMeter_DetachLevelMeter
#define criAtomMeter_GetLevelInfo FCriWareApi::criAtomMeter_GetLevelInfo
#define criAtomMeter_CalculateWorkSizeForLoudnessMeter FCriWareApi::criAtomMeter_CalculateWorkSizeForLoudnessMeter
#define criAtomMeter_AttachLoudnessMeter FCriWareApi::criAtomMeter_AttachLoudnessMeter
#define criAtomMeter_DetachLoudnessMeter FCriWareApi::criAtomMeter_DetachLoudnessMeter
#define criAtomMeter_GetLoudnessInfo FCriWareApi::criAtomMeter_GetLoudnessInfo
#define criAtomMeter_ResetLoudnessMeter FCriWareApi::criAtomMeter_ResetLoudnessMeter
#define criAtomMeter_CalculateWorkSizeForTruePeakMeter FCriWareApi::criAtomMeter_CalculateWorkSizeForTruePeakMeter
#define criAtomMeter_AttachTruePeakMeter FCriWareApi::criAtomMeter_AttachTruePeakMeter
#define criAtomMeter_DetachTruePeakMeter FCriWareApi::criAtomMeter_DetachTruePeakMeter
#define criAtomMeter_GetTruePeakInfo FCriWareApi::criAtomMeter_GetTruePeakInfo
#define criAtomPlayer_SetDecodeCallback FCriWareApi::criAtomPlayer_SetDecodeCallback
#define criAtomPlayer_DiscardSamples FCriWareApi::criAtomPlayer_DiscardSamples
#define criAtomExAsr_CalculateWorkSize FCriWareApi::criAtomExAsr_CalculateWorkSize
#define criAtomExAsr_SetConfigForWorkSizeCalculation FCriWareApi::criAtomExAsr_SetConfigForWorkSizeCalculation
#define criAtomExAsr_Initialize FCriWareApi::criAtomExAsr_Initialize
#define criAtomExAsr_Finalize FCriWareApi::criAtomExAsr_Finalize
#define criAtomExAsr_SetBusVolumeByName FCriWareApi::criAtomExAsr_SetBusVolumeByName
#define criAtomExAsr_GetBusVolumeByName FCriWareApi::criAtomExAsr_GetBusVolumeByName
#define criAtomExAsr_SetBusPan3dByName FCriWareApi::criAtomExAsr_SetBusPan3dByName
#define criAtomExAsr_GetBusPan3dByName FCriWareApi::criAtomExAsr_GetBusPan3dByName
#define criAtomExAsr_SetBusMatrixByName FCriWareApi::criAtomExAsr_SetBusMatrixByName
#define criAtomExAsr_SetBusSendLevelByName FCriWareApi::criAtomExAsr_SetBusSendLevelByName
#define criAtomExAsr_SetEffectParameter FCriWareApi::criAtomExAsr_SetEffectParameter
#define criAtomExAsr_UpdateEffectParameters FCriWareApi::criAtomExAsr_UpdateEffectParameters
#define criAtomExAsr_GetEffectParameter FCriWareApi::criAtomExAsr_GetEffectParameter
#define criAtomExAsr_SetEffectBypass FCriWareApi::criAtomExAsr_SetEffectBypass
#define criAtomExAsr_AttachBusAnalyzerByName FCriWareApi::criAtomExAsr_AttachBusAnalyzerByName
#define criAtomExAsr_DetachBusAnalyzerByName FCriWareApi::criAtomExAsr_DetachBusAnalyzerByName
#define criAtomExAsr_GetBusAnalyzerInfoByName FCriWareApi::criAtomExAsr_GetBusAnalyzerInfoByName
#define criAtomExAsr_SetBusFilterCallbackByName FCriWareApi::criAtomExAsr_SetBusFilterCallbackByName
#define criAtomExAsr_GetNumBuses FCriWareApi::criAtomExAsr_GetNumBuses
#define criAtomExAsr_RegisterEffectInterface FCriWareApi::criAtomExAsr_RegisterEffectInterface
#define criAtomExAsr_UnregisterEffectInterface FCriWareApi::criAtomExAsr_UnregisterEffectInterface
#define criAtomExAsrRack_CalculateWorkSize FCriWareApi::criAtomExAsrRack_CalculateWorkSize
#define criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromConfig FCriWareApi::criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromConfig
#define criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromAcfDataAndConfig FCriWareApi::criAtomExAsrRack_CalculateWorkSizeForDspBusSettingFromAcfDataAndConfig
#define criAtomExAsrRack_Create FCriWareApi::criAtomExAsrRack_Create
#define criAtomExAsrRack_Destroy FCriWareApi::criAtomExAsrRack_Destroy
#define criAtomExAsrRack_CalculateWorkSizeForDspBusSetting FCriWareApi::criAtomExAsrRack_CalculateWorkSizeForDspBusSetting
#define criAtomExAsrRack_AttachDspBusSetting FCriWareApi::criAtomExAsrRack_AttachDspBusSetting
#define criAtomExAsrRack_DetachDspBusSetting FCriWareApi::criAtomExAsrRack_DetachDspBusSetting
#define criAtomExAsrRack_ApplyDspBusSnapshot FCriWareApi::criAtomExAsrRack_ApplyDspBusSnapshot
#define criAtomExAsrRack_GetAppliedDspBusSnapshotName FCriWareApi::criAtomExAsrRack_GetAppliedDspBusSnapshotName
#define criAtomExAsrRack_SetBusVolumeByName FCriWareApi::criAtomExAsrRack_SetBusVolumeByName
#define criAtomExAsrRack_GetBusVolumeByName FCriWareApi::criAtomExAsrRack_GetBusVolumeByName
#define criAtomExAsrRack_SetBusPan3dByName FCriWareApi::criAtomExAsrRack_SetBusPan3dByName
#define criAtomExAsrRack_GetBusPan3dByName FCriWareApi::criAtomExAsrRack_GetBusPan3dByName
#define criAtomExAsrRack_SetBusMatrixByName FCriWareApi::criAtomExAsrRack_SetBusMatrixByName
#define criAtomExAsrRack_SetBusSendLevelByName FCriWareApi::criAtomExAsrRack_SetBusSendLevelByName
#define criAtomExAsrRack_SetEffectParameter FCriWareApi::criAtomExAsrRack_SetEffectParameter
#define criAtomExAsrRack_UpdateEffectParameters FCriWareApi::criAtomExAsrRack_UpdateEffectParameters
#define criAtomExAsrRack_GetEffectParameter FCriWareApi::criAtomExAsrRack_GetEffectParameter
#define criAtomExAsrRack_SetEffectBypass FCriWareApi::criAtomExAsrRack_SetEffectBypass
#define criAtomExAsrRack_AttachBusAnalyzerByName FCriWareApi::criAtomExAsrRack_AttachBusAnalyzerByName
#define criAtomExAsrRack_DetachBusAnalyzerByName FCriWareApi::criAtomExAsrRack_DetachBusAnalyzerByName
#define criAtomExAsrRack_GetBusAnalyzerInfoByName FCriWareApi::criAtomExAsrRack_GetBusAnalyzerInfoByName
#define criAtomExAsrRack_SetBusFilterCallbackByName FCriWareApi::criAtomExAsrRack_SetBusFilterCallbackByName
#define criAtomExAsrRack_SetAlternateRackId FCriWareApi::criAtomExAsrRack_SetAlternateRackId
#define criAtomExAsrRack_GetNumBuses FCriWareApi::criAtomExAsrRack_GetNumBuses
#define criAtomExAsr_GetPcmDataFloat32 FCriWareApi::criAtomExAsr_GetPcmDataFloat32
#define criAtomExAsr_GetNumBufferedSamples FCriWareApi::criAtomExAsr_GetNumBufferedSamples
#define criAtomExAsrRack_GetPcmDataFloat32 FCriWareApi::criAtomExAsrRack_GetPcmDataFloat32
#define criAtomExAsrRack_GetNumBufferedSamples FCriWareApi::criAtomExAsrRack_GetNumBufferedSamples
#define criAtomAsr_CalculateWorkSize FCriWareApi::criAtomAsr_CalculateWorkSize
#define criAtomAsr_Initialize FCriWareApi::criAtomAsr_Initialize
#define criAtomAsr_Finalize FCriWareApi::criAtomAsr_Finalize
#define criAtomEx_InitializeForUserPcmOutput FCriWareApi::criAtomEx_InitializeForUserPcmOutput
#define criAtomEx_FinalizeForUserPcmOutput FCriWareApi::criAtomEx_FinalizeForUserPcmOutput
#define criAtomExAsr_PauseOutputVoice FCriWareApi::criAtomExAsr_PauseOutputVoice
#define criAtomExAsrRack_GetNumOutputSamples FCriWareApi::criAtomExAsrRack_GetNumOutputSamples
#define criAtomExAsrRack_GetOutputChannels FCriWareApi::criAtomExAsrRack_GetOutputChannels
#define criAtomExAsrRack_GetBusNumber FCriWareApi::criAtomExAsrRack_GetBusNumber
#define criAtomAsr_PauseOutputVoice FCriWareApi::criAtomAsr_PauseOutputVoice
#define criAtomExAsrRack_GetAmbisonicRackId FCriWareApi::criAtomExAsrRack_GetAmbisonicRackId
#define criAtomExAsr_SetDspParameter FCriWareApi::criAtomExAsr_SetDspParameter
#define criAtomExAsr_SetDspParameterByName FCriWareApi::criAtomExAsr_SetDspParameterByName
#define criAtomExAsr_GetDspParameter FCriWareApi::criAtomExAsr_GetDspParameter
#define criAtomExAsr_GetDspParameterByName FCriWareApi::criAtomExAsr_GetDspParameterByName
#define criAtomExAsr_SetDspBypass FCriWareApi::criAtomExAsr_SetDspBypass
#define criAtomExAsr_SetDspBypassByName FCriWareApi::criAtomExAsr_SetDspBypassByName
#define criAtomExAsr_SetBusVolume FCriWareApi::criAtomExAsr_SetBusVolume
#define criAtomExAsr_GetBusVolume FCriWareApi::criAtomExAsr_GetBusVolume
#define criAtomExAsr_SetBusPan3d FCriWareApi::criAtomExAsr_SetBusPan3d
#define criAtomExAsr_GetBusPan3d FCriWareApi::criAtomExAsr_GetBusPan3d
#define criAtomExAsr_SetBusMatrix FCriWareApi::criAtomExAsr_SetBusMatrix
#define criAtomExAsr_SetBusSendLevel FCriWareApi::criAtomExAsr_SetBusSendLevel
#define criAtomExAsr_AttachBusAnalyzer FCriWareApi::criAtomExAsr_AttachBusAnalyzer
#define criAtomExAsr_DetachBusAnalyzer FCriWareApi::criAtomExAsr_DetachBusAnalyzer
#define criAtomExAsr_GetBusAnalyzerInfo FCriWareApi::criAtomExAsr_GetBusAnalyzerInfo
#define criAtomExAsr_SetBusFilterCallback FCriWareApi::criAtomExAsr_SetBusFilterCallback
#define criAtomExAsrRack_SetDspParameter FCriWareApi::criAtomExAsrRack_SetDspParameter
#define criAtomExAsrRack_SetDspParameterByName FCriWareApi::criAtomExAsrRack_SetDspParameterByName
#define criAtomExAsrRack_GetDspParameter FCriWareApi::criAtomExAsrRack_GetDspParameter
#define criAtomExAsrRack_GetDspParameterByName FCriWareApi::criAtomExAsrRack_GetDspParameterByName
#define criAtomExAsrRack_SetDspBypass FCriWareApi::criAtomExAsrRack_SetDspBypass
#define criAtomExAsrRack_SetDspBypassByName FCriWareApi::criAtomExAsrRack_SetDspBypassByName
#define criAtomExAsrRack_SetBusVolume FCriWareApi::criAtomExAsrRack_SetBusVolume
#define criAtomExAsrRack_GetBusVolume FCriWareApi::criAtomExAsrRack_GetBusVolume
#define criAtomExAsrRack_SetBusPan3d FCriWareApi::criAtomExAsrRack_SetBusPan3d
#define criAtomExAsrRack_GetBusPan3d FCriWareApi::criAtomExAsrRack_GetBusPan3d
#define criAtomExAsrRack_SetBusMatrix FCriWareApi::criAtomExAsrRack_SetBusMatrix
#define criAtomExAsrRack_SetBusSendLevel FCriWareApi::criAtomExAsrRack_SetBusSendLevel
#define criAtomExAsrRack_AttachBusAnalyzer FCriWareApi::criAtomExAsrRack_AttachBusAnalyzer
#define criAtomExAsrRack_DetachBusAnalyzer FCriWareApi::criAtomExAsrRack_DetachBusAnalyzer
#define criAtomExAsrRack_GetBusAnalyzerInfo FCriWareApi::criAtomExAsrRack_GetBusAnalyzerInfo
#define criAtomExAsrRack_SetBusFilterCallback FCriWareApi::criAtomExAsrRack_SetBusFilterCallback
#define criAtomEx_CalculateWorkSize FCriWareApi::criAtomEx_CalculateWorkSize
#define criAtomEx_Initialize FCriWareApi::criAtomEx_Initialize
#define criAtomEx_Finalize FCriWareApi::criAtomEx_Finalize
#define criAtomEx_IsInitialized FCriWareApi::criAtomEx_IsInitialized
#define criAtomEx_ExecuteMain FCriWareApi::criAtomEx_ExecuteMain
#define criAtomEx_ExecuteAudioProcess FCriWareApi::criAtomEx_ExecuteAudioProcess
#define criAtomEx_Lock FCriWareApi::criAtomEx_Lock
#define criAtomEx_Unlock FCriWareApi::criAtomEx_Unlock
#define criAtomEx_GetTimeMicro FCriWareApi::criAtomEx_GetTimeMicro
#define criAtomEx_ResetTimer FCriWareApi::criAtomEx_ResetTimer
#define criAtomEx_PauseTimer FCriWareApi::criAtomEx_PauseTimer
#define criAtomEx_SetConfigForWorkSizeCalculation FCriWareApi::criAtomEx_SetConfigForWorkSizeCalculation
#define criAtomEx_CalculateWorkSizeForRegisterAcfData FCriWareApi::criAtomEx_CalculateWorkSizeForRegisterAcfData
#define criAtomEx_RegisterAcfData FCriWareApi::criAtomEx_RegisterAcfData
#define criAtomEx_CalculateWorkSizeForRegisterAcfFile FCriWareApi::criAtomEx_CalculateWorkSizeForRegisterAcfFile
#define criAtomEx_CalculateWorkSizeForRegisterAcfFileById FCriWareApi::criAtomEx_CalculateWorkSizeForRegisterAcfFileById
#define criAtomEx_RegisterAcfFile FCriWareApi::criAtomEx_RegisterAcfFile
#define criAtomEx_RegisterAcfFileById FCriWareApi::criAtomEx_RegisterAcfFileById
#define criAtomEx_UnregisterAcf FCriWareApi::criAtomEx_UnregisterAcf
#define criAtomEx_GetAcfVersion FCriWareApi::criAtomEx_GetAcfVersion
#define criAtomEx_GetAcfVersionFromFile FCriWareApi::criAtomEx_GetAcfVersionFromFile
#define criAtomEx_GetAcfVersionFromFileById FCriWareApi::criAtomEx_GetAcfVersionFromFileById
#define criAtomEx_GetSupportedAcfVersion FCriWareApi::criAtomEx_GetSupportedAcfVersion
#define criAtomEx_AnalyzeAudioHeader FCriWareApi::criAtomEx_AnalyzeAudioHeader
#define criAtomEx_SetRandomSeed FCriWareApi::criAtomEx_SetRandomSeed
#define criAtomEx_IsDataPlaying FCriWareApi::criAtomEx_IsDataPlaying
#define criAtomEx_CalculateWorkSizeForDspBusSetting FCriWareApi::criAtomEx_CalculateWorkSizeForDspBusSetting
#define criAtomEx_CalculateWorkSizeForDspBusSettingFromAcfData FCriWareApi::criAtomEx_CalculateWorkSizeForDspBusSettingFromAcfData
#define criAtomEx_AttachDspBusSetting FCriWareApi::criAtomEx_AttachDspBusSetting
#define criAtomEx_DetachDspBusSetting FCriWareApi::criAtomEx_DetachDspBusSetting
#define criAtomEx_ApplyDspBusSnapshot FCriWareApi::criAtomEx_ApplyDspBusSnapshot
#define criAtomEx_GetAppliedDspBusSnapshotName FCriWareApi::criAtomEx_GetAppliedDspBusSnapshotName
#define criAtomEx_SetCueLinkCallback FCriWareApi::criAtomEx_SetCueLinkCallback
#define criAtomEx_SetSpeakerAngles FCriWareApi::criAtomEx_SetSpeakerAngles
#define criAtomEx_SetSpeakerAngleArray FCriWareApi::criAtomEx_SetSpeakerAngleArray
#define criAtomEx_SetVirtualSpeakerAngleArray FCriWareApi::criAtomEx_SetVirtualSpeakerAngleArray
#define criAtomEx_ControlVirtualSpeakerSetting FCriWareApi::criAtomEx_ControlVirtualSpeakerSetting
#define criAtomEx_GetNumGameVariables FCriWareApi::criAtomEx_GetNumGameVariables
#define criAtomEx_GetGameVariableInfo FCriWareApi::criAtomEx_GetGameVariableInfo
#define criAtomEx_GetGameVariableById FCriWareApi::criAtomEx_GetGameVariableById
#define criAtomEx_GetGameVariableByName FCriWareApi::criAtomEx_GetGameVariableByName
#define criAtomEx_SetGameVariableById FCriWareApi::criAtomEx_SetGameVariableById
#define criAtomEx_SetGameVariableByName FCriWareApi::criAtomEx_SetGameVariableByName
#define criAtomEx_SetPlaybackCancelCallback FCriWareApi::criAtomEx_SetPlaybackCancelCallback
#define criAtomEx_ControlAcfConsistencyCheck FCriWareApi::criAtomEx_ControlAcfConsistencyCheck
#define criAtomEx_SetAcfConsistencyCheckErrorLevel FCriWareApi::criAtomEx_SetAcfConsistencyCheckErrorLevel
#define criAtomEx_SetTrackTransitionBySelectorCallback FCriWareApi::criAtomEx_SetTrackTransitionBySelectorCallback
#define criAtomExDebug_GetResourcesInfo FCriWareApi::criAtomExDebug_GetResourcesInfo
#define criAtomExHcaMx_CalculateWorkSize FCriWareApi::criAtomExHcaMx_CalculateWorkSize
#define criAtomExHcaMx_SetConfigForWorkSizeCalculation FCriWareApi::criAtomExHcaMx_SetConfigForWorkSizeCalculation
#define criAtomExHcaMx_Initialize FCriWareApi::criAtomExHcaMx_Initialize
#define criAtomExHcaMx_Finalize FCriWareApi::criAtomExHcaMx_Finalize
#define criAtomExHcaMx_SetBusSendLevelByName FCriWareApi::criAtomExHcaMx_SetBusSendLevelByName
#define criAtomExHcaMx_SetFrequencyRatio FCriWareApi::criAtomExHcaMx_SetFrequencyRatio
#define criAtomExHcaMx_SetAsrRackId FCriWareApi::criAtomExHcaMx_SetAsrRackId
#define criAtomExAcf_GetNumAisacControls FCriWareApi::criAtomExAcf_GetNumAisacControls
#define criAtomExAcf_GetAisacControlInfo FCriWareApi::criAtomExAcf_GetAisacControlInfo
#define criAtomExAcf_GetAisacControlIdByName FCriWareApi::criAtomExAcf_GetAisacControlIdByName
#define criAtomExAcf_GetAisacControlNameById FCriWareApi::criAtomExAcf_GetAisacControlNameById
#define criAtomExAcf_GetNumDspSettings FCriWareApi::criAtomExAcf_GetNumDspSettings
#define criAtomExAcf_GetNumDspSettingsFromAcfData FCriWareApi::criAtomExAcf_GetNumDspSettingsFromAcfData
#define criAtomExAcf_GetDspSettingNameByIndex FCriWareApi::criAtomExAcf_GetDspSettingNameByIndex
#define criAtomExAcf_GetDspSettingNameByIndexFromAcfData FCriWareApi::criAtomExAcf_GetDspSettingNameByIndexFromAcfData
#define criAtomExAcf_GetDspSettingInformation FCriWareApi::criAtomExAcf_GetDspSettingInformation
#define criAtomExAcf_GetDspSettingSnapshotInformation FCriWareApi::criAtomExAcf_GetDspSettingSnapshotInformation
#define criAtomExAcf_GetDspBusInformation FCriWareApi::criAtomExAcf_GetDspBusInformation
#define criAtomExAcf_GetDspFxType FCriWareApi::criAtomExAcf_GetDspFxType
#define criAtomExAcf_GetDspFxName FCriWareApi::criAtomExAcf_GetDspFxName
#define criAtomExAcf_GetDspFxParameters FCriWareApi::criAtomExAcf_GetDspFxParameters
#define criAtomExAcf_GetDspBusLinkInformation FCriWareApi::criAtomExAcf_GetDspBusLinkInformation
#define criAtomExAcf_GetNumCategoriesFromAcfData FCriWareApi::criAtomExAcf_GetNumCategoriesFromAcfData
#define criAtomExAcf_GetNumCategories FCriWareApi::criAtomExAcf_GetNumCategories
#define criAtomExAcf_GetNumCategoriesPerPlaybackFromAcfData FCriWareApi::criAtomExAcf_GetNumCategoriesPerPlaybackFromAcfData
#define criAtomExAcf_GetNumCategoriesPerPlayback FCriWareApi::criAtomExAcf_GetNumCategoriesPerPlayback
#define criAtomExAcf_GetCategoryInfo FCriWareApi::criAtomExAcf_GetCategoryInfo
#define criAtomExAcf_GetCategoryInfoByName FCriWareApi::criAtomExAcf_GetCategoryInfoByName
#define criAtomExAcf_GetCategoryInfoById FCriWareApi::criAtomExAcf_GetCategoryInfoById
#define criAtomExAcf_GetNumGlobalAisacs FCriWareApi::criAtomExAcf_GetNumGlobalAisacs
#define criAtomExAcf_GetGlobalAisacInfo FCriWareApi::criAtomExAcf_GetGlobalAisacInfo
#define criAtomExAcf_GetGlobalAisacInfoByName FCriWareApi::criAtomExAcf_GetGlobalAisacInfoByName
#define criAtomExAcf_GetGlobalAisacGraphInfo FCriWareApi::criAtomExAcf_GetGlobalAisacGraphInfo
#define criAtomExAcf_GetGlobalAisacValue FCriWareApi::criAtomExAcf_GetGlobalAisacValue
#define criAtomExAcf_GetAcfInfo FCriWareApi::criAtomExAcf_GetAcfInfo
#define criAtomExAcf_GetAcfInfoFromAcfData FCriWareApi::criAtomExAcf_GetAcfInfoFromAcfData
#define criAtomExAcf_GetNumSelectors FCriWareApi::criAtomExAcf_GetNumSelectors
#define criAtomExAcf_GetSelectorInfoByIndex FCriWareApi::criAtomExAcf_GetSelectorInfoByIndex
#define criAtomExAcf_GetSelectorInfoByName FCriWareApi::criAtomExAcf_GetSelectorInfoByName
#define criAtomExAcf_GetSelectorLabelInfo FCriWareApi::criAtomExAcf_GetSelectorLabelInfo
#define criAtomExAcf_SetGlobalLabelToSelectorByName FCriWareApi::criAtomExAcf_SetGlobalLabelToSelectorByName
#define criAtomExAcf_SetGlobalLabelToSelectorByIndex FCriWareApi::criAtomExAcf_SetGlobalLabelToSelectorByIndex
#define criAtomExAcf_GetNumBusesFromAcfData FCriWareApi::criAtomExAcf_GetNumBusesFromAcfData
#define criAtomExAcf_GetNumBuses FCriWareApi::criAtomExAcf_GetNumBuses
#define criAtomExAcf_GetMaxBusesOfDspBusSettingsFromAcfData FCriWareApi::criAtomExAcf_GetMaxBusesOfDspBusSettingsFromAcfData
#define criAtomExAcf_GetMaxBusesOfDspBusSettings FCriWareApi::criAtomExAcf_GetMaxBusesOfDspBusSettings
#define criAtomExAcf_FindBusName FCriWareApi::criAtomExAcf_FindBusName
#define criAtomExAcb_CalculateWorkSizeForLoadAcbData FCriWareApi::criAtomExAcb_CalculateWorkSizeForLoadAcbData
#define criAtomExAcb_CalculateWorkSizeForLoadAcbDataById FCriWareApi::criAtomExAcb_CalculateWorkSizeForLoadAcbDataById
#define criAtomExAcb_LoadAcbData FCriWareApi::criAtomExAcb_LoadAcbData
#define criAtomExAcb_LoadAcbDataById FCriWareApi::criAtomExAcb_LoadAcbDataById
#define criAtomExAcb_CalculateWorkSizeForLoadAcbFile FCriWareApi::criAtomExAcb_CalculateWorkSizeForLoadAcbFile
#define criAtomExAcb_CalculateWorkSizeForLoadAcbFileById FCriWareApi::criAtomExAcb_CalculateWorkSizeForLoadAcbFileById
#define criAtomExAcb_LoadAcbFile FCriWareApi::criAtomExAcb_LoadAcbFile
#define criAtomExAcb_LoadAcbFileById FCriWareApi::criAtomExAcb_LoadAcbFileById
#define criAtomExAcb_Release FCriWareApi::criAtomExAcb_Release
#define criAtomExAcb_IsReadyToRelease FCriWareApi::criAtomExAcb_IsReadyToRelease
#define criAtomExAcb_ReleaseAll FCriWareApi::criAtomExAcb_ReleaseAll
#define criAtomExAcb_EnumerateHandles FCriWareApi::criAtomExAcb_EnumerateHandles
#define criAtomExAcb_GetVersion FCriWareApi::criAtomExAcb_GetVersion
#define criAtomExAcb_GetVersionFromFile FCriWareApi::criAtomExAcb_GetVersionFromFile
#define criAtomExAcb_GetSupportedVersion FCriWareApi::criAtomExAcb_GetSupportedVersion
#define criAtomExAcb_GetNumCues FCriWareApi::criAtomExAcb_GetNumCues
#define criAtomExAcb_ExistsId FCriWareApi::criAtomExAcb_ExistsId
#define criAtomExAcb_ExistsName FCriWareApi::criAtomExAcb_ExistsName
#define criAtomExAcb_ExistsIndex FCriWareApi::criAtomExAcb_ExistsIndex
#define criAtomExAcb_GetCueIdByIndex FCriWareApi::criAtomExAcb_GetCueIdByIndex
#define criAtomExAcb_GetCueIdByName FCriWareApi::criAtomExAcb_GetCueIdByName
#define criAtomExAcb_GetCueNameByIndex FCriWareApi::criAtomExAcb_GetCueNameByIndex
#define criAtomExAcb_GetCueNameById FCriWareApi::criAtomExAcb_GetCueNameById
#define criAtomExAcb_GetCueIndexById FCriWareApi::criAtomExAcb_GetCueIndexById
#define criAtomExAcb_GetCueIndexByName FCriWareApi::criAtomExAcb_GetCueIndexByName
#define criAtomExAcb_GetUserDataById FCriWareApi::criAtomExAcb_GetUserDataById
#define criAtomExAcb_GetUserDataByName FCriWareApi::criAtomExAcb_GetUserDataByName
#define criAtomExAcb_GetLengthById FCriWareApi::criAtomExAcb_GetLengthById
#define criAtomExAcb_GetLengthByName FCriWareApi::criAtomExAcb_GetLengthByName
#define criAtomExAcb_GetNumUsableAisacControlsById FCriWareApi::criAtomExAcb_GetNumUsableAisacControlsById
#define criAtomExAcb_GetNumUsableAisacControlsByName FCriWareApi::criAtomExAcb_GetNumUsableAisacControlsByName
#define criAtomExAcb_GetUsableAisacControlById FCriWareApi::criAtomExAcb_GetUsableAisacControlById
#define criAtomExAcb_GetUsableAisacControlByName FCriWareApi::criAtomExAcb_GetUsableAisacControlByName
#define criAtomExAcb_IsUsingAisacControlById FCriWareApi::criAtomExAcb_IsUsingAisacControlById
#define criAtomExAcb_IsUsingAisacControlByName FCriWareApi::criAtomExAcb_IsUsingAisacControlByName
#define criAtomExAcb_GetCuePriorityById FCriWareApi::criAtomExAcb_GetCuePriorityById
#define criAtomExAcb_GetCuePriorityByName FCriWareApi::criAtomExAcb_GetCuePriorityByName
#define criAtomExAcb_GetWaveformInfoById FCriWareApi::criAtomExAcb_GetWaveformInfoById
#define criAtomExAcb_GetWaveformInfoByName FCriWareApi::criAtomExAcb_GetWaveformInfoByName
#define criAtomExAcb_GetOnMemoryAwbHandle FCriWareApi::criAtomExAcb_GetOnMemoryAwbHandle
#define criAtomExAcb_GetStreamingAwbHandle FCriWareApi::criAtomExAcb_GetStreamingAwbHandle
#define criAtomExAcb_GetCueInfoByName FCriWareApi::criAtomExAcb_GetCueInfoByName
#define criAtomExAcb_GetCueInfoById FCriWareApi::criAtomExAcb_GetCueInfoById
#define criAtomExAcb_GetCueInfoByIndex FCriWareApi::criAtomExAcb_GetCueInfoByIndex
#define criAtomExAcb_GetNumCuePlayingCountByName FCriWareApi::criAtomExAcb_GetNumCuePlayingCountByName
#define criAtomExAcb_GetNumCuePlayingCountById FCriWareApi::criAtomExAcb_GetNumCuePlayingCountById
#define criAtomExAcb_GetNumCuePlayingCountByIndex FCriWareApi::criAtomExAcb_GetNumCuePlayingCountByIndex
#define criAtomExAcb_GetBlockIndexByIndex FCriWareApi::criAtomExAcb_GetBlockIndexByIndex
#define criAtomExAcb_GetBlockIndexById FCriWareApi::criAtomExAcb_GetBlockIndexById
#define criAtomExAcb_GetBlockIndexByName FCriWareApi::criAtomExAcb_GetBlockIndexByName
#define criAtomExAcb_SetDetectionInGamePreviewDataCallback FCriWareApi::criAtomExAcb_SetDetectionInGamePreviewDataCallback
#define criAtomExAcb_GetAcbInfo FCriWareApi::criAtomExAcb_GetAcbInfo
#define criAtomExAcb_ResetCueTypeStateByName FCriWareApi::criAtomExAcb_ResetCueTypeStateByName
#define criAtomExAcb_ResetCueTypeStateById FCriWareApi::criAtomExAcb_ResetCueTypeStateById
#define criAtomExAcb_ResetCueTypeStateByIndex FCriWareApi::criAtomExAcb_ResetCueTypeStateByIndex
#define criAtomExAcb_AttachAwbFile FCriWareApi::criAtomExAcb_AttachAwbFile
#define criAtomExAcb_DetachAwbFile FCriWareApi::criAtomExAcb_DetachAwbFile
#define criAtomExAcb_CalculateWorkSizeForAttachAwbFile FCriWareApi::criAtomExAcb_CalculateWorkSizeForAttachAwbFile
#define criAtomExAcb_GetNumAwbFileSlots FCriWareApi::criAtomExAcb_GetNumAwbFileSlots
#define criAtomExAcb_GetAwbFileSlotName FCriWareApi::criAtomExAcb_GetAwbFileSlotName
#define criAtomExAcb_IsAttachedAwbFile FCriWareApi::criAtomExAcb_IsAttachedAwbFile
#define criAtomExVoicePool_CalculateWorkSizeForStandardVoicePool FCriWareApi::criAtomExVoicePool_CalculateWorkSizeForStandardVoicePool
#define criAtomExVoicePool_AllocateStandardVoicePool FCriWareApi::criAtomExVoicePool_AllocateStandardVoicePool
#define criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool FCriWareApi::criAtomExVoicePool_CalculateWorkSizeForAdxVoicePool
#define criAtomExVoicePool_AllocateAdxVoicePool FCriWareApi::criAtomExVoicePool_AllocateAdxVoicePool
#define criAtomExVoicePool_CalculateWorkSizeForHcaVoicePool FCriWareApi::criAtomExVoicePool_CalculateWorkSizeForHcaVoicePool
#define criAtomExVoicePool_AllocateHcaVoicePool FCriWareApi::criAtomExVoicePool_AllocateHcaVoicePool
#define criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool FCriWareApi::criAtomExVoicePool_CalculateWorkSizeForHcaMxVoicePool
#define criAtomExVoicePool_AllocateHcaMxVoicePool FCriWareApi::criAtomExVoicePool_AllocateHcaMxVoicePool
#define criAtomExVoicePool_CalculateWorkSizeForWaveVoicePool FCriWareApi::criAtomExVoicePool_CalculateWorkSizeForWaveVoicePool
#define criAtomExVoicePool_AllocateWaveVoicePool FCriWareApi::criAtomExVoicePool_AllocateWaveVoicePool
#define criAtomExVoicePool_CalculateWorkSizeForAiffVoicePool FCriWareApi::criAtomExVoicePool_CalculateWorkSizeForAiffVoicePool
#define criAtomExVoicePool_AllocateAiffVoicePool FCriWareApi::criAtomExVoicePool_AllocateAiffVoicePool
#define criAtomExVoicePool_CalculateWorkSizeForRawPcmVoicePool FCriWareApi::criAtomExVoicePool_CalculateWorkSizeForRawPcmVoicePool
#define criAtomExVoicePool_AllocateRawPcmVoicePool FCriWareApi::criAtomExVoicePool_AllocateRawPcmVoicePool
#define criAtomExVoicePool_Free FCriWareApi::criAtomExVoicePool_Free
#define criAtomExVoicePool_FreeAll FCriWareApi::criAtomExVoicePool_FreeAll
#define criAtomExVoicePool_GetNumUsedVoices FCriWareApi::criAtomExVoicePool_GetNumUsedVoices
#define criAtomExVoicePool_GetPlayerHandle FCriWareApi::criAtomExVoicePool_GetPlayerHandle
#define criAtomExCategory_SetVolumeById FCriWareApi::criAtomExCategory_SetVolumeById
#define criAtomExCategory_GetVolumeById FCriWareApi::criAtomExCategory_GetVolumeById
#define criAtomExCategory_GetTotalVolumeById FCriWareApi::criAtomExCategory_GetTotalVolumeById
#define criAtomExCategory_SetVolumeByName FCriWareApi::criAtomExCategory_SetVolumeByName
#define criAtomExCategory_GetVolumeByName FCriWareApi::criAtomExCategory_GetVolumeByName
#define criAtomExCategory_GetTotalVolumeByName FCriWareApi::criAtomExCategory_GetTotalVolumeByName
#define criAtomExCategory_MuteById FCriWareApi::criAtomExCategory_MuteById
#define criAtomExCategory_IsMutedById FCriWareApi::criAtomExCategory_IsMutedById
#define criAtomExCategory_MuteByName FCriWareApi::criAtomExCategory_MuteByName
#define criAtomExCategory_IsMutedByName FCriWareApi::criAtomExCategory_IsMutedByName
#define criAtomExCategory_SoloById FCriWareApi::criAtomExCategory_SoloById
#define criAtomExCategory_IsSoloedById FCriWareApi::criAtomExCategory_IsSoloedById
#define criAtomExCategory_SoloByName FCriWareApi::criAtomExCategory_SoloByName
#define criAtomExCategory_IsSoloedByName FCriWareApi::criAtomExCategory_IsSoloedByName
#define criAtomExCategory_PauseById FCriWareApi::criAtomExCategory_PauseById
#define criAtomExCategory_IsPausedById FCriWareApi::criAtomExCategory_IsPausedById
#define criAtomExCategory_PauseByName FCriWareApi::criAtomExCategory_PauseByName
#define criAtomExCategory_IsPausedByName FCriWareApi::criAtomExCategory_IsPausedByName
#define criAtomExCategory_SetFadeInTimeById FCriWareApi::criAtomExCategory_SetFadeInTimeById
#define criAtomExCategory_SetFadeInTimeByName FCriWareApi::criAtomExCategory_SetFadeInTimeByName
#define criAtomExCategory_SetFadeOutTimeById FCriWareApi::criAtomExCategory_SetFadeOutTimeById
#define criAtomExCategory_SetFadeOutTimeByName FCriWareApi::criAtomExCategory_SetFadeOutTimeByName
#define criAtomExCategory_SetAisacControlById FCriWareApi::criAtomExCategory_SetAisacControlById
#define criAtomExCategory_SetAisacControlByName FCriWareApi::criAtomExCategory_SetAisacControlByName
#define criAtomExCategory_ResetAllAisacControlById FCriWareApi::criAtomExCategory_ResetAllAisacControlById
#define criAtomExCategory_ResetAllAisacControlByName FCriWareApi::criAtomExCategory_ResetAllAisacControlByName
#define criAtomExCategory_AttachAisacById FCriWareApi::criAtomExCategory_AttachAisacById
#define criAtomExCategory_AttachAisacByName FCriWareApi::criAtomExCategory_AttachAisacByName
#define criAtomExCategory_DetachAisacById FCriWareApi::criAtomExCategory_DetachAisacById
#define criAtomExCategory_DetachAisacByName FCriWareApi::criAtomExCategory_DetachAisacByName
#define criAtomExCategory_DetachAisacAllById FCriWareApi::criAtomExCategory_DetachAisacAllById
#define criAtomExCategory_DetachAisacAllByName FCriWareApi::criAtomExCategory_DetachAisacAllByName
#define criAtomExCategory_GetNumAttachedAisacsById FCriWareApi::criAtomExCategory_GetNumAttachedAisacsById
#define criAtomExCategory_GetNumAttachedAisacsByName FCriWareApi::criAtomExCategory_GetNumAttachedAisacsByName
#define criAtomExCategory_GetAttachedAisacInfoById FCriWareApi::criAtomExCategory_GetAttachedAisacInfoById
#define criAtomExCategory_GetAttachedAisacInfoByName FCriWareApi::criAtomExCategory_GetAttachedAisacInfoByName
#define criAtomExCategory_GetCurrentAisacControlValueById FCriWareApi::criAtomExCategory_GetCurrentAisacControlValueById
#define criAtomExCategory_GetCurrentAisacControlValueByName FCriWareApi::criAtomExCategory_GetCurrentAisacControlValueByName
#define criAtomExCategory_GetNumCuePlayingCountById FCriWareApi::criAtomExCategory_GetNumCuePlayingCountById
#define criAtomExCategory_GetNumCuePlayingCountByName FCriWareApi::criAtomExCategory_GetNumCuePlayingCountByName
#define criAtomExCategory_StopById FCriWareApi::criAtomExCategory_StopById
#define criAtomExCategory_StopByName FCriWareApi::criAtomExCategory_StopByName
#define criAtomExCategory_StopWithoutReleaseTimeById FCriWareApi::criAtomExCategory_StopWithoutReleaseTimeById
#define criAtomExCategory_StopWithoutReleaseTimeByName FCriWareApi::criAtomExCategory_StopWithoutReleaseTimeByName
#define criAtomExPlayer_CalculateWorkSize FCriWareApi::criAtomExPlayer_CalculateWorkSize
#define criAtomExPlayer_Create FCriWareApi::criAtomExPlayer_Create
#define criAtomExPlayer_Destroy FCriWareApi::criAtomExPlayer_Destroy
#define criAtomExPlayer_SetCueId FCriWareApi::criAtomExPlayer_SetCueId
#define criAtomExPlayer_SetCueName FCriWareApi::criAtomExPlayer_SetCueName
#define criAtomExPlayer_SetCueIndex FCriWareApi::criAtomExPlayer_SetCueIndex
#define criAtomExPlayer_SetData FCriWareApi::criAtomExPlayer_SetData
#define criAtomExPlayer_SetFile FCriWareApi::criAtomExPlayer_SetFile
#define criAtomExPlayer_SetContentId FCriWareApi::criAtomExPlayer_SetContentId
#define criAtomExPlayer_SetWaveId FCriWareApi::criAtomExPlayer_SetWaveId
#define criAtomExPlayer_Start FCriWareApi::criAtomExPlayer_Start
#define criAtomExPlayer_Prepare FCriWareApi::criAtomExPlayer_Prepare
#define criAtomExPlayer_Stop FCriWareApi::criAtomExPlayer_Stop
#define criAtomExPlayer_StopWithoutReleaseTime FCriWareApi::criAtomExPlayer_StopWithoutReleaseTime
#define criAtomExPlayer_StopAllPlayers FCriWareApi::criAtomExPlayer_StopAllPlayers
#define criAtomExPlayer_StopAllPlayersWithoutReleaseTime FCriWareApi::criAtomExPlayer_StopAllPlayersWithoutReleaseTime
#define criAtomExPlayer_EnumeratePlayers FCriWareApi::criAtomExPlayer_EnumeratePlayers
#define criAtomExPlayer_Pause FCriWareApi::criAtomExPlayer_Pause
#define criAtomExPlayer_Resume FCriWareApi::criAtomExPlayer_Resume
#define criAtomExPlayer_IsPaused FCriWareApi::criAtomExPlayer_IsPaused
#define criAtomExPlayer_GetStatus FCriWareApi::criAtomExPlayer_GetStatus
#define criAtomExPlayer_GetNumPlaybacks FCriWareApi::criAtomExPlayer_GetNumPlaybacks
#define criAtomExPlayer_GetLastPlaybackId FCriWareApi::criAtomExPlayer_GetLastPlaybackId
#define criAtomExPlayer_GetTime FCriWareApi::criAtomExPlayer_GetTime
#define criAtomExPlayer_SetFormat FCriWareApi::criAtomExPlayer_SetFormat
#define criAtomExPlayer_SetNumChannels FCriWareApi::criAtomExPlayer_SetNumChannels
#define criAtomExPlayer_SetSamplingRate FCriWareApi::criAtomExPlayer_SetSamplingRate
#define criAtomExPlayer_SetSoundRendererType FCriWareApi::criAtomExPlayer_SetSoundRendererType
#define criAtomExPlayer_SetGroupNumber FCriWareApi::criAtomExPlayer_SetGroupNumber
#define criAtomExPlayer_SetVoiceControlMethod FCriWareApi::criAtomExPlayer_SetVoiceControlMethod
#define criAtomExPlayer_SetVoicePoolIdentifier FCriWareApi::criAtomExPlayer_SetVoicePoolIdentifier
#define criAtomExPlayer_SetHcaMxMixerId FCriWareApi::criAtomExPlayer_SetHcaMxMixerId
#define criAtomExPlayer_SetAsrRackId FCriWareApi::criAtomExPlayer_SetAsrRackId
#define criAtomExPlayer_SetAsrRackIdArray FCriWareApi::criAtomExPlayer_SetAsrRackIdArray
#define criAtomExPlayer_SetStartTime FCriWareApi::criAtomExPlayer_SetStartTime
#define criAtomExPlayer_SetSequencePrepareTime FCriWareApi::criAtomExPlayer_SetSequencePrepareTime
#define criAtomExPlayer_SetSyncPlaybackId FCriWareApi::criAtomExPlayer_SetSyncPlaybackId
#define criAtomExPlayer_SetPlaybackRatio FCriWareApi::criAtomExPlayer_SetPlaybackRatio
#define criAtomExPlayer_LimitLoopCount FCriWareApi::criAtomExPlayer_LimitLoopCount
#define criAtomExPlayer_UpdateAll FCriWareApi::criAtomExPlayer_UpdateAll
#define criAtomExPlayer_Update FCriWareApi::criAtomExPlayer_Update
#define criAtomExPlayer_ResetParameters FCriWareApi::criAtomExPlayer_ResetParameters
#define criAtomExPlayer_GetParameterFloat32 FCriWareApi::criAtomExPlayer_GetParameterFloat32
#define criAtomExPlayer_GetParameterUint32 FCriWareApi::criAtomExPlayer_GetParameterUint32
#define criAtomExPlayer_GetParameterSint32 FCriWareApi::criAtomExPlayer_GetParameterSint32
#define criAtomExPlayer_SetVolume FCriWareApi::criAtomExPlayer_SetVolume
#define criAtomExPlayer_SetPitch FCriWareApi::criAtomExPlayer_SetPitch
#define criAtomExPlayer_SetMaxPitch FCriWareApi::criAtomExPlayer_SetMaxPitch
#define criAtomExPlayer_SetPan3dAngle FCriWareApi::criAtomExPlayer_SetPan3dAngle
#define criAtomExPlayer_SetPan3dInteriorDistance FCriWareApi::criAtomExPlayer_SetPan3dInteriorDistance
#define criAtomExPlayer_SetPan3dVolume FCriWareApi::criAtomExPlayer_SetPan3dVolume
#define criAtomExPlayer_SetPanType FCriWareApi::criAtomExPlayer_SetPanType
#define criAtomExPlayer_SetPanSpeakerType FCriWareApi::criAtomExPlayer_SetPanSpeakerType
#define criAtomExPlayer_AddMixDownCenterVolumeOffset FCriWareApi::criAtomExPlayer_AddMixDownCenterVolumeOffset
#define criAtomExPlayer_AddMixDownLfeVolumeOffset FCriWareApi::criAtomExPlayer_AddMixDownLfeVolumeOffset
#define criAtomExPlayer_ChangeDefaultPanSpeakerType FCriWareApi::criAtomExPlayer_ChangeDefaultPanSpeakerType
#define criAtomExPlayer_SetPanAngleType FCriWareApi::criAtomExPlayer_SetPanAngleType
#define criAtomExPlayer_SetPanSpread FCriWareApi::criAtomExPlayer_SetPanSpread
#define criAtomExPlayer_SetSendLevel FCriWareApi::criAtomExPlayer_SetSendLevel
#define criAtomExPlayer_SetBusSendLevelByName FCriWareApi::criAtomExPlayer_SetBusSendLevelByName
#define criAtomExPlayer_SetBusSendLevelOffsetByName FCriWareApi::criAtomExPlayer_SetBusSendLevelOffsetByName
#define criAtomExPlayer_SetPanAdx1Compatible FCriWareApi::criAtomExPlayer_SetPanAdx1Compatible
#define criAtomExPlayer_SetBandpassFilterParameters FCriWareApi::criAtomExPlayer_SetBandpassFilterParameters
#define criAtomExPlayer_SetBiquadFilterParameters FCriWareApi::criAtomExPlayer_SetBiquadFilterParameters
#define criAtomExPlayer_SetVoicePriority FCriWareApi::criAtomExPlayer_SetVoicePriority
#define criAtomExPlayer_SetAisacControlById FCriWareApi::criAtomExPlayer_SetAisacControlById
#define criAtomExPlayer_SetAisacControlByName FCriWareApi::criAtomExPlayer_SetAisacControlByName
#define criAtomExPlayer_ClearAisacControls FCriWareApi::criAtomExPlayer_ClearAisacControls
#define criAtomExPlayer_Set3dSourceHn FCriWareApi::criAtomExPlayer_Set3dSourceHn
#define criAtomExPlayer_Set3dSourceListHn FCriWareApi::criAtomExPlayer_Set3dSourceListHn
#define criAtomExPlayer_Set3dListenerHn FCriWareApi::criAtomExPlayer_Set3dListenerHn
#define criAtomExPlayer_GetAisacControlById FCriWareApi::criAtomExPlayer_GetAisacControlById
#define criAtomExPlayer_GetAisacControlByName FCriWareApi::criAtomExPlayer_GetAisacControlByName
#define criAtomExPlayer_SetCategoryById FCriWareApi::criAtomExPlayer_SetCategoryById
#define criAtomExPlayer_SetCategoryByName FCriWareApi::criAtomExPlayer_SetCategoryByName
#define criAtomExPlayer_UnsetCategory FCriWareApi::criAtomExPlayer_UnsetCategory
#define criAtomExPlayer_GetNumCategories FCriWareApi::criAtomExPlayer_GetNumCategories
#define criAtomExPlayer_GetCategoryInfo FCriWareApi::criAtomExPlayer_GetCategoryInfo
#define criAtomExPlayer_SetTrackInfo FCriWareApi::criAtomExPlayer_SetTrackInfo
#define criAtomExPlayer_SetTrackVolume FCriWareApi::criAtomExPlayer_SetTrackVolume
#define criAtomExPlayer_SetSilentMode FCriWareApi::criAtomExPlayer_SetSilentMode
#define criAtomExPlayer_SetCuePriority FCriWareApi::criAtomExPlayer_SetCuePriority
#define criAtomExPlayer_SetPreDelayTime FCriWareApi::criAtomExPlayer_SetPreDelayTime
#define criAtomExPlayer_SetEnvelopeAttackTime FCriWareApi::criAtomExPlayer_SetEnvelopeAttackTime
#define criAtomExPlayer_SetEnvelopeHoldTime FCriWareApi::criAtomExPlayer_SetEnvelopeHoldTime
#define criAtomExPlayer_SetEnvelopeDecayTime FCriWareApi::criAtomExPlayer_SetEnvelopeDecayTime
#define criAtomExPlayer_SetEnvelopeReleaseTime FCriWareApi::criAtomExPlayer_SetEnvelopeReleaseTime
#define criAtomExPlayer_SetEnvelopeSustainLevel FCriWareApi::criAtomExPlayer_SetEnvelopeSustainLevel
#define criAtomExPlayer_SetDataRequestCallback FCriWareApi::criAtomExPlayer_SetDataRequestCallback
#define criAtomExPlayer_SetFilterCallback FCriWareApi::criAtomExPlayer_SetFilterCallback
#define criAtomExPlayer_SetRandomSeed FCriWareApi::criAtomExPlayer_SetRandomSeed
#define criAtomExPlayer_SetDspParameter FCriWareApi::criAtomExPlayer_SetDspParameter
#define criAtomExPlayer_AttachAisac FCriWareApi::criAtomExPlayer_AttachAisac
#define criAtomExPlayer_AttachAisacByIndex FCriWareApi::criAtomExPlayer_AttachAisacByIndex
#define criAtomExPlayer_DetachAisac FCriWareApi::criAtomExPlayer_DetachAisac
#define criAtomExPlayer_DetachAisacByIndex FCriWareApi::criAtomExPlayer_DetachAisacByIndex
#define criAtomExPlayer_DetachAisacAll FCriWareApi::criAtomExPlayer_DetachAisacAll
#define criAtomExPlayer_GetNumAttachedAisacs FCriWareApi::criAtomExPlayer_GetNumAttachedAisacs
#define criAtomExPlayer_GetAttachedAisacInfo FCriWareApi::criAtomExPlayer_GetAttachedAisacInfo
#define criAtomExPlayer_SetStreamingCacheId FCriWareApi::criAtomExPlayer_SetStreamingCacheId
#define criAtomExPlayer_AttachTween FCriWareApi::criAtomExPlayer_AttachTween
#define criAtomExPlayer_DetachTween FCriWareApi::criAtomExPlayer_DetachTween
#define criAtomExPlayer_DetachTweenAll FCriWareApi::criAtomExPlayer_DetachTweenAll
#define criAtomExPlayer_SetFirstBlockIndex FCriWareApi::criAtomExPlayer_SetFirstBlockIndex
#define criAtomExPlayer_SetBlockTransitionCallback FCriWareApi::criAtomExPlayer_SetBlockTransitionCallback
#define criAtomExPlayer_GetSoundObject FCriWareApi::criAtomExPlayer_GetSoundObject
#define criAtomExPlayer_SetDrySendLevel FCriWareApi::criAtomExPlayer_SetDrySendLevel
#define criAtomExPlayer_SetSelectorLabel FCriWareApi::criAtomExPlayer_SetSelectorLabel
#define criAtomExPlayer_ClearSelectorLabels FCriWareApi::criAtomExPlayer_ClearSelectorLabels
#define criAtomExPlayer_SetPlaybackTrackInfoNotificationCallback FCriWareApi::criAtomExPlayer_SetPlaybackTrackInfoNotificationCallback
#define criAtomExPlayback_Stop FCriWareApi::criAtomExPlayback_Stop
#define criAtomExPlayback_StopWithoutReleaseTime FCriWareApi::criAtomExPlayback_StopWithoutReleaseTime
#define criAtomExPlayback_Pause FCriWareApi::criAtomExPlayback_Pause
#define criAtomExPlayback_Resume FCriWareApi::criAtomExPlayback_Resume
#define criAtomExPlayback_IsPaused FCriWareApi::criAtomExPlayback_IsPaused
#define criAtomExPlayback_GetStatus FCriWareApi::criAtomExPlayback_GetStatus
#define criAtomExPlayback_GetFormatInfo FCriWareApi::criAtomExPlayback_GetFormatInfo
#define criAtomExPlayback_GetSource FCriWareApi::criAtomExPlayback_GetSource
#define criAtomExPlayback_GetAtomPlayer FCriWareApi::criAtomExPlayback_GetAtomPlayer
#define criAtomExPlayback_GetTime FCriWareApi::criAtomExPlayback_GetTime
#define criAtomExPlayback_GetTimeSyncedWithAudio FCriWareApi::criAtomExPlayback_GetTimeSyncedWithAudio
#define criAtomExPlayback_GetTimeSyncedWithAudioMicro FCriWareApi::criAtomExPlayback_GetTimeSyncedWithAudioMicro
#define criAtomExPlayback_GetSequencePosition FCriWareApi::criAtomExPlayback_GetSequencePosition
#define criAtomExPlayback_GetNumPlayedSamples FCriWareApi::criAtomExPlayback_GetNumPlayedSamples
#define criAtomExPlayback_GetParameterFloat32 FCriWareApi::criAtomExPlayback_GetParameterFloat32
#define criAtomExPlayback_GetParameterUint32 FCriWareApi::criAtomExPlayback_GetParameterUint32
#define criAtomExPlayback_GetParameterSint32 FCriWareApi::criAtomExPlayback_GetParameterSint32
#define criAtomExPlayback_GetAisacControlById FCriWareApi::criAtomExPlayback_GetAisacControlById
#define criAtomExPlayback_GetAisacControlByName FCriWareApi::criAtomExPlayback_GetAisacControlByName
#define criAtomExPlayback_SetNextBlockIndex FCriWareApi::criAtomExPlayback_SetNextBlockIndex
#define criAtomExPlayback_GetCurrentBlockIndex FCriWareApi::criAtomExPlayback_GetCurrentBlockIndex
#define criAtomExPlayback_GetPlaybackTrackInfo FCriWareApi::criAtomExPlayback_GetPlaybackTrackInfo
#define criAtomExPlayback_GetBeatSyncInfo FCriWareApi::criAtomExPlayback_GetBeatSyncInfo
#define criAtomExPlayer_CalculateWorkSizeForFader FCriWareApi::criAtomExPlayer_CalculateWorkSizeForFader
#define criAtomExPlayer_AttachFader FCriWareApi::criAtomExPlayer_AttachFader
#define criAtomExPlayer_DetachFader FCriWareApi::criAtomExPlayer_DetachFader
#define criAtomExPlayer_SetFadeOutTime FCriWareApi::criAtomExPlayer_SetFadeOutTime
#define criAtomExPlayer_GetFadeOutTime FCriWareApi::criAtomExPlayer_GetFadeOutTime
#define criAtomExPlayer_SetFadeInTime FCriWareApi::criAtomExPlayer_SetFadeInTime
#define criAtomExPlayer_GetFadeInTime FCriWareApi::criAtomExPlayer_GetFadeInTime
#define criAtomExPlayer_SetFadeInStartOffset FCriWareApi::criAtomExPlayer_SetFadeInStartOffset
#define criAtomExPlayer_GetFadeInStartOffset FCriWareApi::criAtomExPlayer_GetFadeInStartOffset
#define criAtomExPlayer_SetFadeOutEndDelay FCriWareApi::criAtomExPlayer_SetFadeOutEndDelay
#define criAtomExPlayer_GetFadeOutEndDelay FCriWareApi::criAtomExPlayer_GetFadeOutEndDelay
#define criAtomExPlayer_IsFading FCriWareApi::criAtomExPlayer_IsFading
#define criAtomExPlayer_ResetFaderParameters FCriWareApi::criAtomExPlayer_ResetFaderParameters
#define criAtomExSequencer_SetEventCallback FCriWareApi::criAtomExSequencer_SetEventCallback
#define criAtomExBeatSync_SetCallback FCriWareApi::criAtomExBeatSync_SetCallback
#define criAtomEx3dSource_CalculateWorkSize FCriWareApi::criAtomEx3dSource_CalculateWorkSize
#define criAtomEx3dSource_Create FCriWareApi::criAtomEx3dSource_Create
#define criAtomEx3dSource_Destroy FCriWareApi::criAtomEx3dSource_Destroy
#define criAtomEx3dSource_Update FCriWareApi::criAtomEx3dSource_Update
#define criAtomEx3dSource_ResetParameters FCriWareApi::criAtomEx3dSource_ResetParameters
#define criAtomEx3dSource_SetPosition FCriWareApi::criAtomEx3dSource_SetPosition
#define criAtomEx3dSource_GetPosition FCriWareApi::criAtomEx3dSource_GetPosition
#define criAtomEx3dSource_SetVelocity FCriWareApi::criAtomEx3dSource_SetVelocity
#define criAtomEx3dSource_SetOrientation FCriWareApi::criAtomEx3dSource_SetOrientation
#define criAtomEx3dSource_SetConeParameter FCriWareApi::criAtomEx3dSource_SetConeParameter
#define criAtomEx3dSource_ChangeDefaultConeParameter FCriWareApi::criAtomEx3dSource_ChangeDefaultConeParameter
#define criAtomEx3dSource_SetMinMaxAttenuationDistance FCriWareApi::criAtomEx3dSource_SetMinMaxAttenuationDistance
#define criAtomEx3dSource_ChangeDefaultMinMaxAttenuationDistance FCriWareApi::criAtomEx3dSource_ChangeDefaultMinMaxAttenuationDistance
#define criAtomEx3dSource_SetInteriorPanField FCriWareApi::criAtomEx3dSource_SetInteriorPanField
#define criAtomEx3dSource_ChangeDefaultInteriorPanField FCriWareApi::criAtomEx3dSource_ChangeDefaultInteriorPanField
#define criAtomEx3dSource_SetDopplerFactor FCriWareApi::criAtomEx3dSource_SetDopplerFactor
#define criAtomEx3dSource_ChangeDefaultDopplerFactor FCriWareApi::criAtomEx3dSource_ChangeDefaultDopplerFactor
#define criAtomEx3dSource_SetVolume FCriWareApi::criAtomEx3dSource_SetVolume
#define criAtomEx3dSource_ChangeDefaultVolume FCriWareApi::criAtomEx3dSource_ChangeDefaultVolume
#define criAtomEx3dSource_SetMaxAngleAisacDelta FCriWareApi::criAtomEx3dSource_SetMaxAngleAisacDelta
#define criAtomEx3dSource_SetDistanceAisacControlId FCriWareApi::criAtomEx3dSource_SetDistanceAisacControlId
#define criAtomEx3dSource_SetListenerBasedAngleAisacControlId FCriWareApi::criAtomEx3dSource_SetListenerBasedAngleAisacControlId
#define criAtomEx3dSource_SetSourceBasedAngleAisacControlId FCriWareApi::criAtomEx3dSource_SetSourceBasedAngleAisacControlId
#define criAtomEx3dSourceList_CalculateWorkSize FCriWareApi::criAtomEx3dSourceList_CalculateWorkSize
#define criAtomEx3dSourceList_Create FCriWareApi::criAtomEx3dSourceList_Create
#define criAtomEx3dSourceList_Destroy FCriWareApi::criAtomEx3dSourceList_Destroy
#define criAtomEx3dSourceList_Add FCriWareApi::criAtomEx3dSourceList_Add
#define criAtomEx3dSourceList_Remove FCriWareApi::criAtomEx3dSourceList_Remove
#define criAtomEx3dSourceList_RemoveAll FCriWareApi::criAtomEx3dSourceList_RemoveAll
#define criAtomEx3dListener_CalculateWorkSize FCriWareApi::criAtomEx3dListener_CalculateWorkSize
#define criAtomEx3dListener_Create FCriWareApi::criAtomEx3dListener_Create
#define criAtomEx3dListener_Destroy FCriWareApi::criAtomEx3dListener_Destroy
#define criAtomEx3dListener_Update FCriWareApi::criAtomEx3dListener_Update
#define criAtomEx3dListener_ResetParameters FCriWareApi::criAtomEx3dListener_ResetParameters
#define criAtomEx3dListener_SetPosition FCriWareApi::criAtomEx3dListener_SetPosition
#define criAtomEx3dListener_GetPosition FCriWareApi::criAtomEx3dListener_GetPosition
#define criAtomEx3dListener_SetVelocity FCriWareApi::criAtomEx3dListener_SetVelocity
#define criAtomEx3dListener_SetOrientation FCriWareApi::criAtomEx3dListener_SetOrientation
#define criAtomEx3dListener_SetDistanceFactor FCriWareApi::criAtomEx3dListener_SetDistanceFactor
#define criAtomEx3dListener_SetFocusPoint FCriWareApi::criAtomEx3dListener_SetFocusPoint
#define criAtomEx3dListener_SetDistanceFocusLevel FCriWareApi::criAtomEx3dListener_SetDistanceFocusLevel
#define criAtomEx3dListener_SetDirectionFocusLevel FCriWareApi::criAtomEx3dListener_SetDirectionFocusLevel
#define criAtomExVoicePool_DetachDsp FCriWareApi::criAtomExVoicePool_DetachDsp
#define criAtomExVoicePool_CalculateWorkSizeForDspPitchShifter FCriWareApi::criAtomExVoicePool_CalculateWorkSizeForDspPitchShifter
#define criAtomExVoicePool_AttachDspPitchShifter FCriWareApi::criAtomExVoicePool_AttachDspPitchShifter
#define criAtomExVoicePool_CalculateWorkSizeForDspTimeStretch FCriWareApi::criAtomExVoicePool_CalculateWorkSizeForDspTimeStretch
#define criAtomExVoicePool_AttachDspTimeStretch FCriWareApi::criAtomExVoicePool_AttachDspTimeStretch
#define criAtomExStreamingCache_IsCachedWaveformById FCriWareApi::criAtomExStreamingCache_IsCachedWaveformById
#define criAtomExStreamingCache_IsCachedWaveformByName FCriWareApi::criAtomExStreamingCache_IsCachedWaveformByName
#define criAtomExStreamingCache_LoadWaveformById FCriWareApi::criAtomExStreamingCache_LoadWaveformById
#define criAtomExStreamingCache_LoadWaveformByName FCriWareApi::criAtomExStreamingCache_LoadWaveformByName
#define criAtomExTween_CalculateWorkSize FCriWareApi::criAtomExTween_CalculateWorkSize
#define criAtomExTween_Create FCriWareApi::criAtomExTween_Create
#define criAtomExTween_Destroy FCriWareApi::criAtomExTween_Destroy
#define criAtomExTween_GetValue FCriWareApi::criAtomExTween_GetValue
#define criAtomExTween_MoveTo FCriWareApi::criAtomExTween_MoveTo
#define criAtomExTween_MoveFrom FCriWareApi::criAtomExTween_MoveFrom
#define criAtomExTween_Stop FCriWareApi::criAtomExTween_Stop
#define criAtomExTween_Reset FCriWareApi::criAtomExTween_Reset
#define criAtomEx_SetVoiceEventCallback FCriWareApi::criAtomEx_SetVoiceEventCallback
#define criAtomEx_EnumerateVoiceInfos FCriWareApi::criAtomEx_EnumerateVoiceInfos
#define criAtomEx_SetMonitoringVoiceStopCallback FCriWareApi::criAtomEx_SetMonitoringVoiceStopCallback
#define criAtomEx_SetMonitoringVoiceStopPlaybackId FCriWareApi::criAtomEx_SetMonitoringVoiceStopPlaybackId
#define criAtomExSoundObject_CalculateWorkSize FCriWareApi::criAtomExSoundObject_CalculateWorkSize
#define criAtomExSoundObject_Create FCriWareApi::criAtomExSoundObject_Create
#define criAtomExSoundObject_Destroy FCriWareApi::criAtomExSoundObject_Destroy
#define criAtomExSoundObject_AddPlayer FCriWareApi::criAtomExSoundObject_AddPlayer
#define criAtomExSoundObject_DeletePlayer FCriWareApi::criAtomExSoundObject_DeletePlayer
#define criAtomExSoundObject_DeleteAllPlayers FCriWareApi::criAtomExSoundObject_DeleteAllPlayers
#define criAtomExPlayer_GetTimeReal FCriWareApi::criAtomExPlayer_GetTimeReal
#define criAtomExPlayback_GetTimeReal FCriWareApi::criAtomExPlayback_GetTimeReal
#define criAtomExPlayback_EnumerateAtomPlayers FCriWareApi::criAtomExPlayback_EnumerateAtomPlayers
#define criAtomEx3dListener_GetFocusPoint FCriWareApi::criAtomEx3dListener_GetFocusPoint
#define criAtomEx3dListener_GetDistanceFocusLevel FCriWareApi::criAtomEx3dListener_GetDistanceFocusLevel
#define criAtomEx3dListener_GetDirectionFocusLevel FCriWareApi::criAtomEx3dListener_GetDirectionFocusLevel
#define criAtomExAcb_GetCurrentAcb FCriWareApi::criAtomExAcb_GetCurrentAcb
#define criAtomEx3dSource_SetAttenuationDistanceSetting FCriWareApi::criAtomEx3dSource_SetAttenuationDistanceSetting
#define criAtomEx3dSource_GetAttenuationDistanceSetting FCriWareApi::criAtomEx3dSource_GetAttenuationDistanceSetting
#define criAtomExPlayer_SetBusSendLevel FCriWareApi::criAtomExPlayer_SetBusSendLevel
#define criAtomExPlayer_SetBusSendLevelOffset FCriWareApi::criAtomExPlayer_SetBusSendLevelOffset
#define criAtomEx_GetNumUsedVirtualVoices FCriWareApi::criAtomEx_GetNumUsedVirtualVoices
#define criAtomEx_GetNumUsedSequences FCriWareApi::criAtomEx_GetNumUsedSequences
#define criAtomEx_GetNumUsedSequenceTracks FCriWareApi::criAtomEx_GetNumUsedSequenceTracks
#define criAtomEx_GetNumUsedSequenceTrackItems FCriWareApi::criAtomEx_GetNumUsedSequenceTrackItems
#define criAtomEx_GetNumUsedAisacAutoModulations FCriWareApi::criAtomEx_GetNumUsedAisacAutoModulations
#define criAtomEx3dSource_SetConeOrientation FCriWareApi::criAtomEx3dSource_SetConeOrientation
#define criAtomExMonitor_CalculateWorkSize FCriWareApi::criAtomExMonitor_CalculateWorkSize
#define criAtomExMonitor_Initialize FCriWareApi::criAtomExMonitor_Initialize
#define criAtomExMonitor_Finalize FCriWareApi::criAtomExMonitor_Finalize
#define criAtomExMonitor_GetServerIpString FCriWareApi::criAtomExMonitor_GetServerIpString
#define criAtomExMonitor_GetClientIpString FCriWareApi::criAtomExMonitor_GetClientIpString
#define criAtomExMonitor_IsConnected FCriWareApi::criAtomExMonitor_IsConnected
#define criAtomExMonitor_SetLogCallback FCriWareApi::criAtomExMonitor_SetLogCallback
#define criAtomExMonitor_SetLogMode FCriWareApi::criAtomExMonitor_SetLogMode
#define criAtomExMonitor_OutputUserLog FCriWareApi::criAtomExMonitor_OutputUserLog
#define criAtomExMonitor_SetDataUpdateNotificationCallback FCriWareApi::criAtomExMonitor_SetDataUpdateNotificationCallback
#endif

/* --- end of file --- */
