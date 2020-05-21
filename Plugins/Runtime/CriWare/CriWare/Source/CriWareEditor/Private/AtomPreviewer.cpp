/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Previewer
 * File     : AtomPreviewer.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "AtomPreviewer.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareEditorPrivatePCH.h"
#include "CriWareInitializer.h"

/* Unreal Engine 4関連ヘッダ */
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Editor.h"

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

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/***************************************************************************
 *      変数定義
 *      Variable Definition
 ***************************************************************************/

/***************************************************************************
 *      クラス定義
 *      Class Definition
 ***************************************************************************/
FAtomPreviewer::FAtomPreviewer()
{
	bIsPreviewing = false;
	bIsPaused = false;
	bWasInGame = false;
	bWasSessionPaused = false;
	PreviewAtomComponent = nullptr;
}

void FAtomPreviewer::Tick(float DeltaTime)
{
	/* 初期化済みかどうかチェック */
	if (FCriWareApi::criAtomEx_IsInitialized() == CRI_FALSE) {
		return;
	}

	/* エディタのUWorldを取得 */
	UWorld* World = (GEditor ? (GEditor->PlayWorld) : nullptr);
	ULocalPlayer* LocalPlayer = (GEngine ? (GEngine->GetDebugLocalPlayer()) : nullptr);
	if(LocalPlayer) {
		UWorld* PlayerWorld = LocalPlayer->GetWorld();
		if(!World) {
			World = PlayerWorld;
		}
	}

	/* ゲーム実行中かどうかチェック */
	bool bInGame = FApp::IsGame();

	/* Widget表示中は以下の判定も行う必要あり */
	bool bIsDebugging = (World != nullptr);
	bInGame |= bIsDebugging;

	/* プレビュー開始判定 */
	if ((bInGame != false) && (bWasInGame == false)) {
		OnPreviewStart();
	}

	/* プレビュー終了判定 */
	if ((bInGame == false) && (bWasInGame != false)) {
		OnPreviewEnd();
	}

	/* 状態の更新 */
	bWasInGame = bInGame;

	/* ポーズ状態の監視 */
	bool bIsPlaySessionPaused = false;
	if (bInGame && GUnrealEd && GUnrealEd->PlayWorld) {
		bIsPlaySessionPaused = GUnrealEd->PlayWorld->bDebugPauseExecution;
	}

	/* ポーズ判定 */
	if ((bIsPlaySessionPaused != false) && (bWasSessionPaused == false)) {
		OnPreviewPaused();
	}

	/* ポーズ解除判定 */
	if ((bIsPlaySessionPaused == false) && (bWasSessionPaused != false)) {
		OnPreviewResumed();
	}

	/* 状態の更新 */
	bWasSessionPaused = bIsPlaySessionPaused;

	/* 以降の処理はプレビュー中のみ行う */
	if ((World == nullptr) || (bInGame == false)) {
		return;
	}
}

bool FAtomPreviewer::IsTickableInEditor() const
{
	return true;
}

bool FAtomPreviewer::IsTickable() const
{
	return true;
}

TStatId FAtomPreviewer::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FAtomPreviewer, STATGROUP_Tickables);
}

void FAtomPreviewer::OnPreviewStart()
{
	/* プレビューの開始を通知 */
	bIsPreviewing = true;

	/* アセットのプレビューを中断 */
	ResetPreviewAtomComponent();
}

void FAtomPreviewer::OnPreviewEnd()
{
	UAtomComponent::SetDefaultAttenuationEnable(true);

	/* プレビューの終了を通知 */
	bIsPreviewing = false;

	/* 再生の停止 */
	FCriWareApi::criAtomExPlayer_StopAllPlayersWithoutReleaseTime();

	/* ルート化されたコンポーネントの破棄 */
	TArray<UAtomComponent*> ArrayForIteration = UAtomComponent::AtomRootedComponentArray;
	for (UAtomComponent* AtomComponent : ArrayForIteration) {
		if (!IsValid(AtomComponent)) {
			continue;
		}
		if (AtomComponent->IsBeingDestroyed()) {
			continue;
		}
		AtomComponent->DestroyComponent();
	}

	/* カテゴリ情報のリセット */
	int32 NumCategories = FCriWareApi::criAtomExAcf_GetNumCategories();
	for (int32 i = 0; i < NumCategories; i++) {
		CriAtomExCategoryInfo CategoryInfo;
		FCriWareApi::criAtomExAcf_GetCategoryInfo((CriUint16)i, &CategoryInfo);
		FCriWareApi::criAtomExCategory_SetVolumeById(CategoryInfo.id, CategoryInfo.volume);
		FCriWareApi::criAtomExCategory_PauseById(CategoryInfo.id, CRI_FALSE);
	}

	/* リスナ位置のリセット */
	UCriWareInitializer::SetListenerLocation(FVector::ZeroVector);
	UCriWareInitializer::SetListenerRotation(FRotator::ZeroRotator);
}

void FAtomPreviewer::OnPreviewPaused()
{
	/* ポーズを通知 */
	bIsPaused = true;
}

void FAtomPreviewer::OnPreviewResumed()
{
	/* ポーズ解除を通知 */
	bIsPaused = false;

	/* アセットのプレビューを中断 */
	ResetPreviewAtomComponent();
}

UAtomComponent* FAtomPreviewer::GetPreviewAtomComponent()
{
	return PreviewAtomComponent;
}

UAtomComponent* FAtomPreviewer::ResetPreviewAtomComponent()
{
	/* プレビュー用のAtomComponentが作成済みかどうかチェック */
	if (PreviewAtomComponent) {
		/* 既存プレビューアを停止して再利用 */
		/* 注意）ACBファイルの再インポートで問題が発生するため、		*/
		/* 　　　停止時には音声データをnullptrで上書きする必要あり。	*/
		PreviewAtomComponent->Stop();
		PreviewAtomComponent->SetSound(nullptr);
	} else {
		/* 新規にプレビューアを作成して再利用 */
		PreviewAtomComponent = NewObject<UAtomComponent>();
		
		/* プロファイル対象から除外 */
		PreviewAtomComponent->bIsPreviewSound = true;
		
		/* GCを回避 */
		PreviewAtomComponent->AddToRoot();
	}

	return PreviewAtomComponent;
}

void FAtomPreviewer::PlayPreviewSound(USoundAtomCue* Sound)
{
	/* プレビュー中はアセットのプレビューを禁止 */
	if ((bIsPreviewing != false) && (bIsPaused == false)) {
		return;
	}

	/* アセットのプレビューを開始 */
	UAtomComponent* AtomComponent = ResetPreviewAtomComponent();
	if (AtomComponent) {
		AtomComponent->bAutoDestroy = false;
		AtomComponent->bIsUISound = true;
		AtomComponent->SetSound(Sound);
		AtomComponent->Play();	
	}
}

void FAtomPreviewer::ClearPreviewComponents()
{
	if (PreviewAtomComponent != nullptr) {
		/* GCを許可 */
		/* 備考）GCで破棄されるはずなのでDestroyComponentは呼ばない。 */
		PreviewAtomComponent->RemoveFromRoot();
		PreviewAtomComponent = nullptr;
	}
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/

/* --- end of file --- */
