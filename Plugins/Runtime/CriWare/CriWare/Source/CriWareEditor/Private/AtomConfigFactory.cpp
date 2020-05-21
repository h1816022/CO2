/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2015-2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Factory of Atom Config File
 * File     : AtomConfigFactory.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "AtomConfigFactory.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareEditorPrivatePCH.h"
#include "SoundAtomConfig.h"
#include "AssetTypeActions_SoundAtomConfig.h"

/* Unreal Engine 4関連ヘッダ */
#include "PackageTools.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "AtomConfigFactory"

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
bool UAtomConfigFactory::bIsActionRegistered = false;

/***************************************************************************
 *      クラス定義
 *      Class Definition
 ***************************************************************************/
UAtomConfigFactory::UAtomConfigFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* Content BrowserでACFファイルをImportできるようにする */
	Formats.Add(TEXT("acf;Atom Config File"));

	/* バイナリとして読み込む */
	bText = false;
	bCreateNew = false;
	bEditorImport = true;

	SupportedClass = USoundAtomConfig::StaticClass();
}

void UAtomConfigFactory::PostInitProperties()
{
	Super::PostInitProperties();

	/* アクションの登録 */
	if (UAtomConfigFactory::bIsActionRegistered == false) {
		FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
		AssetToolsModule.Get().RegisterAssetTypeActions(MakeShareable(new FAssetTypeActions_SoundAtomConfig));
		UAtomConfigFactory::bIsActionRegistered = true;
	}
}

void UAtomConfigFactory::BeginDestroy()
{
	Super::BeginDestroy();
}

UObject* UAtomConfigFactory::FactoryCreateBinary
(
	UClass*				Class,
	UObject*			InParent,
	FName				Name,
	EObjectFlags		Flags,
	UObject*			Context,
	const TCHAR*		FileType,
	const uint8*&		Buffer,
	const uint8*		BufferEnd,
	FFeedbackContext*	Warn
)
{
	/* ACFオブジェクトの作成 */
	USoundAtomConfig* AcfObject = NewObject<USoundAtomConfig>(InParent, Name, Flags);

	/* データを別のメモリ領域にコピー */
	/* 備考）メモリ領域がconstなのでそのままではロードできないため。 */
	FByteBulkData RawData;
	RawData.Lock(LOCK_READ_WRITE);
	void* LockedData = RawData.Realloc(BufferEnd - Buffer);
	FMemory::Memcpy(LockedData, Buffer, BufferEnd - Buffer);
	RawData.Unlock();

	/* ACFデータをuasset内に取り込み */
	AcfObject->RawData.Lock(LOCK_READ_WRITE);
	LockedData = AcfObject->RawData.Realloc(BufferEnd - Buffer);
	FMemory::Memcpy(LockedData, Buffer, BufferEnd - Buffer);
	AcfObject->RawData.Unlock();

	/* ACBファイル情報の保存領域を確保 */
	if(AcfObject->AssetImportData == nullptr) {
		AcfObject->AssetImportData = NewObject<UAssetImportData>(AcfObject, TEXT("AssetImportData"));
	}

	/* ACBファイル再インポート用に情報を保存 */
	if (AcfObject->AssetImportData != nullptr) {
		AcfObject->AssetImportData->Update(CurrentFilename);
	}

	return AcfObject;
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/
#undef LOCTEXT_NAMESPACE

/* --- end of file --- */
