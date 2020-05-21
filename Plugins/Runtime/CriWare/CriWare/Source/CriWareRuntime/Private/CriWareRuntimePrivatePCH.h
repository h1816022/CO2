/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Precompiled header for CriWareEditor
 * File     : CriWareRuntimePrivatePCH.h
 *
 ****************************************************************************/

/* 多重定義防止 */
#pragma once

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
#include "Engine/Engine.h"
#include "Templates/SharedPointer.h"
#include "RenderResource.h"
#include "TextureResource.h"

#if WITH_EDITOR
#include "Editor.h"
#include "EditorModes.h"
#include "EdMode.h"
#include "EditorViewportClient.h"
#include "ISourceControlProvider.h"
#include "ISourceControlModule.h"
#endif

DECLARE_LOG_CATEGORY_EXTERN(LogCriWareRuntime, Log, All);
#include "CriWareApi.h"
#include "CriWareLocalization.h"
#include "CriWareInitializer.h"
#include "SoundAtomCueSheet.h"
#include "SoundAtomCue.h"
#include "AtomComponent.h"

/* --- end of file --- */
