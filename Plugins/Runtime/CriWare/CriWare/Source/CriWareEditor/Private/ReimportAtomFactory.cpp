/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2015-2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Reimport Factory of Atom Data
 * File     : ReimportAtomFactory.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "ReimportAtomFactory.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareEditorPrivatePCH.h"
#include "CriWarePreviewer.h"
#include "CriWareInitializer.h"
#include "SoundAtomCueSheet.h"

/* Unreal Editor関連ヘッダ */
#include "EditorFramework/AssetImportData.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "ReimportAtomFactory"

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
UReimportAtomFactory::UReimportAtomFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UReimportAtomFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	USoundAtomCueSheet* AcbObject = Cast<USoundAtomCueSheet>(Obj);

	if (AcbObject && AcbObject->AssetImportData) {
		AcbObject->AssetImportData->ExtractFilenames(OutFilenames);
		return true;
	}

	return false;
}

void UReimportAtomFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
	USoundAtomCueSheet* AcbObject = Cast<USoundAtomCueSheet>(Obj);
	if (AcbObject && ensure(NewReimportPaths.Num() == 1)) {
		AcbObject->AssetImportData->UpdateFilenameOnly(NewReimportPaths[0]);
	}
}

EReimportResult::Type UReimportAtomFactory::Reimport(UObject* Obj)
{
	/* プレビューを停止 */
	UCriWarePreviewer::StopPreviewing();

	/* インポート情報の取得 */
	USoundAtomCueSheet* AcbObject = Cast<USoundAtomCueSheet>(Obj);
	if (!AcbObject || !AcbObject->AssetImportData) {
		return EReimportResult::Failed;
	}

	/* ACB使用中にリロードは行えない */
	if (AcbObject->GetAcbHn() != nullptr) {
		UE_LOG(LogCriWareEditor, Error, TEXT("Cannot reimport: ACB file is in use."));
		return EReimportResult::Failed;
	}

	/* ファイルパスの作成 */
	FString ResolvedSourceFilePath = AcbObject->AssetImportData->GetFirstFilename();
	if (!ResolvedSourceFilePath.Len()) {
		return EReimportResult::Failed;
	}

	UE_LOG(LogCriWareEditor, Log, TEXT("Performing atomic reimport of [%s]"), *ResolvedSourceFilePath);

	/* ファイルの有無をチェック */
	if (IFileManager::Get().FileSize(*ResolvedSourceFilePath) == INDEX_NONE) {
		UE_LOG(LogCriWareEditor, Error, TEXT("Cannot reimport: source file cannot be found."));
		return EReimportResult::Failed;
	}

	/* パラメータを一旦退避 */
	/* 備考）Contextにハンドルを渡してもFactoryCreateBinaryには届かない模様。 */
	bool bOverrideAwbDirectory = AcbObject->bOverrideAwbDirectory;
	FDirectoryPath AwbDirectory = AcbObject->AwbDirectory;

	/* アセットの差し替え */
	if (UFactory::StaticImportObject(AcbObject->GetClass(), AcbObject->GetOuter(), *AcbObject->GetName(),
		RF_Public | RF_Standalone, *ResolvedSourceFilePath, NULL, this)) {
		UE_LOG(LogCriWareEditor, Log, TEXT("Imported successfully"));

		/* パラメータの復元 */
		AcbObject->bOverrideAwbDirectory = bOverrideAwbDirectory;
		AcbObject->AwbDirectory = AwbDirectory;

		// Try to find the outer package so we can dirty it up
		if (AcbObject->GetOuter()) {
			AcbObject->GetOuter()->MarkPackageDirty();
		} else {
			AcbObject->MarkPackageDirty();
		}
	} else {
		UE_LOG(LogCriWareEditor, Warning, TEXT("-- import failed"));
	}

	return EReimportResult::Succeeded;
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/
#undef LOCTEXT_NAMESPACE

/* --- end of file --- */
