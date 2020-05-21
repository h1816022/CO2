/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Listener
 * File     : AtomListener.h
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

/* CRIWAREプラグインヘッダ */
#include "CriWareApi.h"

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
class APlayerController;

/***************************************************************************
 *      変数宣言
 *      Prototype Variables
 ***************************************************************************/

/***************************************************************************
 *      クラス宣言
 *      Prototype Classes
 ***************************************************************************/
class CRIWARERUNTIME_API FAtomListener
{
public:
	/* コンストラクタ */
	FAtomListener();

	/* デストラクタ */
	~FAtomListener();

	/* 全てのリスナの状態を更新 */
	static void UpdateAllListeners();

	/* リスナの状態を更新 */
	void UpdateListener(int32 PlayerIndex);

	/* 距離係数の設定 */
	void SetDistanceFactor(float InDistanceFactor);

	/* 距離係数の取得 */
	float GetDistanceFactor();

	/* 有効／無効の切り替え */
	void SetAutoUpdateEnabled(bool bEnabled);

	/* リスナ位置の指定 */
	void SetListenerLocation(FVector Location);

	/* リスナの向きの指定 */
	void SetListenerRotation(FRotator Rotation);

	/* リスナ位置の取得 */
	FVector GetListenerLocation();

	/* リスニングポイント（フォーカスポイントを加味した位置）の取得 */
	FVector GetListeningPoint();

	/* リスナハンドルの取得 */
	CriAtomEx3dListenerHn GetListenerHandle(void);

	/* 指定したプレーヤのリスナを取得 */
	static FAtomListener* GetListener(int32 PlayerIndex = 0);

	/* 指定したプレーヤコントローラIDに対応するリスナを取得 */
	static FAtomListener* GetListenerByPlayerControllerID(int32 PlayerControllerID);

	/* 最も距離の近いリスナを取得 */
	static FAtomListener* GetNearestListener(FVector Location);

	/* リスナに関連付けられたプレーヤコントローラのID */
	int32 PlayerControllerID;

	/* リスナに関連付けられたPawnのID */
	uint32 PawnID;

	/* ビューターゲットのID */
	uint32 ViewTargetID;

private:
	/* リスナリスト */
	static TArray<FAtomListener*> Listeners;

	/* リスナ */
	CriAtomEx3dListenerHn ListenerHandle;

	/* 距離係数 */
	float DistanceFactor;

	/* リスナを自動で操作するかどうか */
	bool bAutoUpdateEnabled;

	/* リスナの位置 */
	FVector ListenerLocation;

	/* リスナの向き */
	FRotator ListenerRotation;
	FQuat ListenerRotation_Quat;

	/* プレーヤコントローラの取得 */
	APlayerController* GetPlayerController(int32 PlayerIndex);
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
