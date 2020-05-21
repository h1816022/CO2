/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2013-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Listener
 * File     : AtomListener.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "AtomListener.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareRuntimePrivatePCH.h"
#include "AtomListenerFocusPoint.h"

/* Unreal Engine 4関連ヘッダ */
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "HeadMountedDisplay.h"
#include "HeadMountedDisplayFunctionLibrary.h"

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
TArray<FAtomListener*> FAtomListener::Listeners;

/***************************************************************************
 *      クラス定義
 *      Class Definition
 ***************************************************************************/
/* コンストラクタ */
FAtomListener::FAtomListener()
{
	/* リスナハンドルを作成 */
	ListenerHandle = criAtomEx3dListener_Create(NULL, NULL, 0);

	/* 距離係数の保存 */
	DistanceFactor = 1.0f;

	/* リスナを自動で操作するよう設定 */
	bAutoUpdateEnabled = true;

	/* リスナ位置の初期化 */
	ListenerLocation = FVector::ZeroVector;
	ListenerRotation = FRotator::ZeroRotator;

	/* プレーヤコントローラ、Pawnとの紐づけをクリア */
	PlayerControllerID = INDEX_NONE;
	PawnID = 0;
	ViewTargetID = 0;

	/* リストに登録 */
	Listeners.Add(this);
}

/* デストラクタ */
FAtomListener::~FAtomListener()
{
	/* 備考）リスナハンドルは破棄しない。				*/
	/* 　　　AtomExプレーヤより先に破棄できないので、	*/
	/* 　　　Finalizeで自動的に破棄されるのを待つ。		*/

	/* リストから破棄 */
	Listeners.Remove(this);
}

/* 全てのリスナの状態を更新 */
void FAtomListener::UpdateAllListeners()
{
#if WITH_EDITOR
	/* プレビュー実行中かどうかチェック */
	bool bIsDebugging = (GEditor ? (GEditor->PlayWorld != nullptr) : false);
	if ((GIsEditor != false) && (bIsDebugging == false)) {
		/* エディタ上ではプレビュー中のみリスナの更新を行う */
		return;
	}
#endif

	/* 初期化済みかどうかチェック */
	if (criAtomEx_IsInitialized() == CRI_FALSE) {
		return;
	}

	/* リスナの更新 */
	int32 PlayerIndex = 0;
	for (FAtomListener* Listener : Listeners) {
		if (Listener != nullptr) {
			Listener->UpdateListener(PlayerIndex);
			PlayerIndex++;
		}
	}
}

/* 距離係数の設定 */
void FAtomListener::SetDistanceFactor(float InDistanceFactor)
{
	/* 距離係数の保存 */
	DistanceFactor = InDistanceFactor;

	/* 距離係数の更新 */
	if (ListenerHandle != nullptr) {
		/* UE4の単位系はcm系(1→0.01m)*/
		/* UE4の座標系をmにするにはUE4の座標系に0.01を乗算する必要がある			*/
		/* プロジェクト設定で設定したInDistanceFactor値をUE4の座標値に乗算し、		*/
		/* AtomEx3dListenerのDistanceFactorとしたい場合は単位系を揃えるために、		*/
		/* InDistanceFactorに100を乗算したものを引数として用いる。					*/
		criAtomEx3dListener_SetDistanceFactor(ListenerHandle, InDistanceFactor * 100.0f);
	}
}

/* 距離係数の取得 */
float FAtomListener::GetDistanceFactor()
{
	return DistanceFactor;
}

/* 有効／無効の切り替え */
void FAtomListener::SetAutoUpdateEnabled(bool bEnabled)
{
	bAutoUpdateEnabled = bEnabled;
}

/* リスナ位置の指定 */
void FAtomListener::SetListenerLocation(FVector Location)
{
	ListenerLocation = Location;
}

/* リスナの向きの指定 */
void FAtomListener::SetListenerRotation(FRotator Rotation)
{
	ListenerRotation = Rotation;
	ListenerRotation_Quat = ListenerRotation.Quaternion();
}

/* リスナ位置の取得 */
FVector FAtomListener::GetListenerLocation()
{
	return ListenerLocation;
}

/* リスニングポイントの取得 */
FVector FAtomListener::GetListeningPoint()
{
	CriAtomExVector pos;
	FVector ListeningPoint;
	float level;

	/* フォーカスポイントの取得 */
	criAtomEx3dListener_GetFocusPoint(ListenerHandle, &pos);

	/* Distance Focus Levelの取得 */
	level = criAtomEx3dListener_GetDistanceFocusLevel(ListenerHandle);

	/* リスニングポイントの計算 */
	ListeningPoint.X = pos.x / DistanceFactor;
	ListeningPoint.Y = pos.y / DistanceFactor;
	ListeningPoint.Z = pos.z / DistanceFactor;

	/* リスニングポイントの計算 */
	ListeningPoint = ListeningPoint * level + ListenerLocation * (1.0f - level);

	return ListeningPoint;
}

/* リスナハンドルの取得 */
CriAtomEx3dListenerHn FAtomListener::GetListenerHandle(void)
{
	return ListenerHandle;
}

/* リスナの状態を更新 */
void FAtomListener::UpdateListener(int32 PlayerIndex)
{
	/* 初期化済みかどうかチェック */
	if (ListenerHandle == NULL) {
		return;
	}

	/* リスナ座標を自動更新するかどうかのチェック */
	if (bAutoUpdateEnabled != false) {
		/* プレーヤコントローラの取得 */
		APlayerController* PlayerController = GetPlayerController(PlayerIndex);

		/* プレーヤコントローラの有無をチェック */
		if (PlayerController != nullptr) {
			if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled()) {
				/* VR Modeの場合HMDのポジションと角度を加える */
				PlayerController->GetPlayerViewPoint(ListenerLocation, ListenerRotation);
				FVector HMDLocation;
				FRotator HMDRotation;
				UHeadMountedDisplayFunctionLibrary::GetOrientationAndPosition(HMDRotation, HMDLocation);
				ListenerLocation += HMDLocation;
				ListenerRotation += HMDRotation;
			} else {
				/* プレーヤが存在する場合はプレーヤのビューポートを取得 */
				FVector FrontDir, RightDir;
				PlayerController->GetAudioListenerPosition(ListenerLocation, FrontDir, RightDir);
				ListenerRotation = FRotationMatrix::MakeFromXY(FrontDir, RightDir).Rotator();
			}

			/* ビューターゲットの取得 */
			AActor* NewViewTarget = PlayerController->GetViewTarget();
			if (NewViewTarget != nullptr) {
				uint32 NewViewTargetID = NewViewTarget->GetUniqueID();
				if (ViewTargetID != NewViewTargetID) {
					/* カメラ切り替え時はフォーカスレベルをクリア */
					criAtomEx3dListener_SetDistanceFocusLevel(ListenerHandle, 0.0f);
					criAtomEx3dListener_SetDirectionFocusLevel(ListenerHandle, 0.0f);
					ViewTargetID = NewViewTargetID;
				}

				/* 新規ビューターゲットにフォーカスポイントの更新を要請 */
				UAtomListenerFocusPoint* FocusPoint = Cast<UAtomListenerFocusPoint>(
					NewViewTarget->GetComponentByClass(UAtomListenerFocusPoint::StaticClass()));
				if (FocusPoint != nullptr) {
					FocusPoint->UpdateFocusPoint();
				}
			}

			/* プレーヤコントローラのIDを取得 */
			int32 NewPlayerControllerID = UGameplayStatics::GetPlayerControllerID(PlayerController);
			if (PlayerControllerID != NewPlayerControllerID) {
				/* プレーヤコントローラ変更時はフォーカスレベルをクリア */
				criAtomEx3dListener_SetDistanceFocusLevel(ListenerHandle, 0.0f);
				criAtomEx3dListener_SetDirectionFocusLevel(ListenerHandle, 0.0f);
				PlayerControllerID = NewPlayerControllerID;
			}

			/* PawnのIDを取得 */
			APawn* NewPawn = PlayerController->GetPawn();
			if (NewPawn != nullptr) {
				uint32 NewPawnID = NewPawn->GetUniqueID();
				if (PawnID != NewPawnID) {
					/* Possess時はフォーカスレベルをクリア */
					criAtomEx3dListener_SetDistanceFocusLevel(ListenerHandle, 0.0f);
					criAtomEx3dListener_SetDirectionFocusLevel(ListenerHandle, 0.0f);
					PawnID = NewPawnID;

					/* 新規Pawnにフォーカスポイントの更新を要請 */
					UAtomListenerFocusPoint* FocusPoint = Cast<UAtomListenerFocusPoint>(
						NewPawn->GetComponentByClass(UAtomListenerFocusPoint::StaticClass()));
					if (FocusPoint != nullptr) {
						FocusPoint->UpdateFocusPoint();
					}
				}
			}
		} else {
			/* 非アクティブであることを通知 */
			PlayerControllerID = INDEX_NONE;
			PawnID = 0;
		}

		ListenerRotation_Quat = ListenerRotation.Quaternion();
	}

	/* 非アクティブなリスナは処理しない */
	if (PlayerControllerID == INDEX_NONE) {
		return;
	}

	/* リスナの座標を設定 */
	CriAtomExVector pos, front, top;
	pos.x = ListenerLocation.X * DistanceFactor;
	pos.y = ListenerLocation.Y * DistanceFactor;
	pos.z = ListenerLocation.Z * DistanceFactor;
	criAtomEx3dListener_SetPosition(ListenerHandle, &pos);

	/* リスナの向きを設定 */
	/* クオータニオンから前方ベクトルと上方ベクトルを取得 */
	FVector FrontVector = ListenerRotation_Quat.GetForwardVector();
	FVector TopVector = ListenerRotation_Quat.GetUpVector();
	front.x = FrontVector.X;
	front.y = FrontVector.Y;
	front.z = FrontVector.Z;
	top.x = TopVector.X;
	top.y = TopVector.Y;
	top.z = TopVector.Z;
	criAtomEx3dListener_SetOrientation(ListenerHandle, &front, &top);

	/* リスナの更新 */
	criAtomEx3dListener_Update(ListenerHandle);
}

/* 指定したプレーヤのリスナを取得 */
FAtomListener* FAtomListener::GetListener(int32 PlayerIndex)
{
	/* 指定範囲のチェック */
	if (!Listeners.IsValidIndex(PlayerIndex)) {
		return nullptr;
	}

	/* リスナを返す */
	return Listeners[PlayerIndex];
}

/* 指定したプレーヤコントローラIDに対応するリスナを取得 */
FAtomListener* FAtomListener::GetListenerByPlayerControllerID(int32 PlayerControllerID)
{
	for (FAtomListener* Listener : Listeners) {
		if ((Listener != nullptr) && (Listener->PlayerControllerID != INDEX_NONE)
			&& (Listener->PlayerControllerID == PlayerControllerID)) {
			return Listener;
		}
	}

	return nullptr;
}

/* 最も距離の近いリスナを取得 */
FAtomListener* FAtomListener::GetNearestListener(FVector Location)
{
	FAtomListener* MinListener = nullptr;
	float MinDistance = 0.0f;

	/* 最小距離の計算 */
	for (FAtomListener* Listener : Listeners) {
		/* 非アクティブなリスナは無視 */
		if ((Listener == nullptr) || (Listener->PlayerControllerID == INDEX_NONE)) {
			continue;
		}

		/* リスニングポイントからの距離を計算 */
		float Distance = FVector::DistSquared(Listener->GetListeningPoint(), Location);

		/* 最小距離のリスナを選択 */
		if ((MinListener == nullptr) || (Distance < MinDistance)) {
			MinListener = Listener;
			MinDistance = Distance;
		}
	}

	return MinListener;
}

/* プレーヤコントローラの取得 */
APlayerController* FAtomListener::GetPlayerController(int32 PlayerIndex)
{
	/* ワールドの取得 */
	UWorld* World = GWorld;

	/* プレーヤコントローラの取得 */
	APlayerController* PlayerController = nullptr;
	if (World != nullptr) {
		PlayerController = UGameplayStatics::GetPlayerController(World, PlayerIndex);
	}

#if WITH_EDITOR
	/* 備考）PIE時は上記処理でプレーヤコントローラが取得できない可能性あり */
	if (PlayerController == nullptr) {
		/* エディタワールドの取得 */
		World = (GEditor ? (GEditor->PlayWorld) : nullptr);

		/* ローカルプレーヤの取得 */
		ULocalPlayer* LocalPlayer = (GEngine ? (GEngine->GetDebugLocalPlayer()) : nullptr);
		if (LocalPlayer != nullptr) {
			/* ローカルプレーヤのワールドを取得 */
			UWorld* PlayerWorld = LocalPlayer->GetWorld();
			if(!World) {
				World = PlayerWorld;
			}
		}

		/* ワールドが取得できた場合はプレーヤコントローラを再取得 */
		if (World != nullptr) {
			PlayerController = UGameplayStatics::GetPlayerController(World, PlayerIndex);
		}
	}
#endif

	/* プレーヤコントローラが描画対象かどうかチェック */
	if (PlayerController != nullptr) {
		/* プレーヤコントローラがローカルプレーヤかどうかチェック */
		ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
		if (LocalPlayer == nullptr) {
			return nullptr;
		}

		/* ローカルプレーヤビューの描画が有効かどうかチェック */
		if ((LocalPlayer->Size.X <= 0.f) || (LocalPlayer->Size.Y <= 0.f)) {
			return nullptr;
		}
	}

	return PlayerController;
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/

/* --- end of file --- */
