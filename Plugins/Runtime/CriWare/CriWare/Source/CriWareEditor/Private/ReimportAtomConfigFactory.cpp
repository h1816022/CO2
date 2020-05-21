/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2015-2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Reimport Factory of Atom Data
 * File     : ReimportAtomConfigFactory.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "ReimportAtomConfigFactory.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareEditorPrivatePCH.h"
#include "SoundAtomConfig.h"
#include "CriWareInitializer.h"

/* Unreal Editor関連ヘッダ */
#include "UnrealEdMisc.h"
#include "EditorFramework/AssetImportData.h"
#include "HAL/FileManager.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "ReimportAtomConfigFactory"

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
UReimportAtomConfigFactory::UReimportAtomConfigFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UReimportAtomConfigFactory::CanReimport(UObject* Obj, TArray<FString>& OutFilenames)
{
	USoundAtomConfig* AcfObject = Cast<USoundAtomConfig>(Obj);

	if (AcfObject && AcfObject->AssetImportData) {
		AcfObject->AssetImportData->ExtractFilenames(OutFilenames);
		return true;
	}

	return false;
}

void UReimportAtomConfigFactory::SetReimportPaths(UObject* Obj, const TArray<FString>& NewReimportPaths)
{
}

EReimportResult::Type UReimportAtomConfigFactory::Reimport(UObject* Obj)
{
	USoundAtomConfig* AcfObject = Cast<USoundAtomConfig>(Obj);
	if (!AcfObject) {
		return EReimportResult::Failed;
	}

	/* ファイルパスの作成 */
	FString ResolvedSourceFilePath = AcfObject->AssetImportData->GetFirstFilename();
	if (!ResolvedSourceFilePath.Len()) {
		return EReimportResult::Failed;
	}

	UE_LOG(LogCriWareEditor, Log, TEXT("Performing atomic reimport of [%s]"), *ResolvedSourceFilePath);

	/* 相対パスを絶対パスに変換 */
	bool bIsRelative = FPaths::IsRelative(ResolvedSourceFilePath);
	if (bIsRelative != false) {
		ResolvedSourceFilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir(), ResolvedSourceFilePath);
	}

	/* ファイルの有無をチェック */
	if (IFileManager::Get().FileSize(*ResolvedSourceFilePath) == INDEX_NONE) {
		UE_LOG(LogCriWareEditor, Warning, TEXT("Cannot reimport: source file cannot be found."));
		return EReimportResult::Failed;
	}

	if (UFactory::StaticImportObject(AcfObject->GetClass(), AcfObject->GetOuter(), *AcfObject->GetName(),
		RF_Public | RF_Standalone, *ResolvedSourceFilePath, NULL, this)) {
		UE_LOG(LogCriWareEditor, Log, TEXT("Imported successfully"));
		// Try to find the outer package so we can dirty it up
		if (AcfObject->GetOuter()) {
			AcfObject->GetOuter()->MarkPackageDirty();
		} else {
			AcfObject->MarkPackageDirty();
		}
	} else {
		UE_LOG(LogCriWareEditor, Warning, TEXT("-- import failed"));
		return EReimportResult::Failed;
	}

	if (AcfObject != nullptr) {
		/* ACFを解放 */
		criAtomEx_UnregisterAcf();

		FMemory::Free(UCriWareInitializer::AcfData);
		UCriWareInitializer::AcfData = nullptr;

		/* ACFデータの取得 */
		int32 AcfDataSize = AcfObject->RawData.GetBulkDataSize();
		AcfObject->RawData.GetCopy((void**)&UCriWareInitializer::AcfData, false);

		/* ACFを再登録 */
		criAtomEx_RegisterAcfData(UCriWareInitializer::AcfData, AcfDataSize, NULL, 0);
		UE_LOG(LogCriWareEditor, Display, TEXT("Atom Config is updated."));
	}

	/* ACFアセットの参照の更新 */
	UCriWareInitializer::AcfAssetReference = FSoftObjectPath(AcfObject);

	return EReimportResult::Succeeded;
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/
#undef LOCTEXT_NAMESPACE

/* --- end of file --- */
