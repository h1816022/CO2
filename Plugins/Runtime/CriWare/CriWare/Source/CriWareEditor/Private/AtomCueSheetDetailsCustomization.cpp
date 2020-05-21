/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2015-2017 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Details Customization for Atom Cue Sheet Asset
 * File     : AtomCueSheetDetailsCustomization.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "AtomCueSheetDetailsCustomization.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareEditorPrivatePCH.h"
#include "CriWareInitializer.h"
#include "SoundAtomCueSheet.h"

/* Unreal Engine 4関連ヘッダ */
#include "Widgets/Input/SButton.h"
#include "Widgets/Docking/SDockTab.h"
#include "DetailWidgetRow.h"
#include "DetailCategoryBuilder.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "AtomCueSheetDetailsCustomization"

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
TSharedRef<IDetailCustomization> FAtomCueSheetDetailsCustomization::MakeInstance()
{
	return MakeShareable(new FAtomCueSheetDetailsCustomization);
}

void FAtomCueSheetDetailsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailLayout)
{
	struct Local {
		static FReply OnContainClicked(USoundAtomCueSheet* CueSheet)
		{
			/* ファイルパスの作成 */
			FString ResolvedSourceFilePath = CueSheet->AssetImportData->GetFirstFilename();
			if (!ResolvedSourceFilePath.Len()) {
				return FReply::Unhandled();
			}

			UE_LOG(LogCriWareEditor, Log, TEXT("Performing atomic import of [%s]"), *ResolvedSourceFilePath);

			/* ファイルの読み込み */
			IFileHandle* File = FPlatformFileManager::Get().GetPlatformFile().OpenRead(*ResolvedSourceFilePath);
			if (File == NULL) {
				UE_LOG(LogCriWareEditor, Warning, TEXT("Failed to open file."));
				return FReply::Unhandled();
			}
			int64 FileSize = File->Size();

			/* 既存のRawDataを一旦破棄 */
			CueSheet->RawData.RemoveBulkData();

			/* バッファの確保 */
			CueSheet->RawData.Lock(LOCK_READ_WRITE);
			void* LockedData = CueSheet->RawData.Realloc(FileSize);

			/* ファイルの読み込み */
			bool Result = File->Read((uint8*)LockedData, FileSize);

			/* バッファのアンロック */
			CueSheet->RawData.Unlock();

			/* ファイルクローズ */
			delete File;

			/* アセットの保存を促す */
			CueSheet->MarkPackageDirty();

			/* エラーチェック */
			if (Result == false) {
				UE_LOG(LogCriWareEditor, Warning, TEXT("Failed to read file."));
				return FReply::Unhandled();
			}

			/* ACBデータが含まれたことを通知 */
			CueSheet->Contains = true;

			return FReply::Handled();
		}

		static FReply OnRemoveClicked(USoundAtomCueSheet* CueSheet)
		{
			/* RawDataを破棄 */
			CueSheet->RawData.RemoveBulkData();

			/* ACBデータが削除されたことを通知 */
			CueSheet->Contains = false;

			/* アセットの保存を促す */
			CueSheet->MarkPackageDirty();

			return FReply::Handled();
		}

		static EVisibility GetContainVisibility(TSharedPtr<IPropertyHandle> InPropertyHandle)
		{
			check(InPropertyHandle.IsValid());

			bool Value;
			if(InPropertyHandle->GetValue(Value) == FPropertyAccess::Success) {
				if (Value != false) {
					return EVisibility::Collapsed;
				}
			}

			return EVisibility::Visible;
		}

		static EVisibility GetRemoveVisibility(TSharedPtr<IPropertyHandle> InPropertyHandle)
		{
			check(InPropertyHandle.IsValid());

			bool Value;
			if(InPropertyHandle->GetValue(Value) == FPropertyAccess::Success) {
				if (Value != false) {
					return EVisibility::Visible;
				}
			}

			return EVisibility::Collapsed;
		}
	};

	/* Atom Cue Sheetアセットにアクセス */
	TArray<TWeakObjectPtr<UObject>> Objects;
	DetailLayout.GetObjectsBeingCustomized(Objects);
	check(Objects.Num() > 0);
	USoundAtomCueSheet* CueSheet = CastChecked<USoundAtomCueSheet>(Objects[0].Get());

	/* ACBデータの現在の状態を取得 */
	if (CueSheet->RawData.GetBulkDataSize() > 0) {
		CueSheet->Contains = true;
	} else {
		CueSheet->Contains = false;
	}

	/* メニュー表示切り替え用にContainsの状態を取得 */
	TSharedPtr<IPropertyHandle> PropertyHandle = DetailLayout.GetProperty("Contains", USoundAtomCueSheet::StaticClass());

	/* メニューの追加表示 */
	IDetailCategoryBuilder& CategoryBuilder = DetailLayout.EditCategory(TEXT("AcbDataHandling"), LOCTEXT("AcbDataHandlingSection", "Acb Data Handling"), ECategoryPriority::Important);
	CategoryBuilder.AddCustomRow(FText::GetEmpty())
	.WholeRowContent()
	.VAlign(VAlign_Center)
	.HAlign(HAlign_Left)
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			SNew(SButton)
			.OnClicked(FOnClicked::CreateStatic(&Local::OnContainClicked, CueSheet))
			.Text(LOCTEXT("ContainButtonLabel", "Contain"))
			.ToolTipText(LOCTEXT("ContainButtonTooltip", "Contain ACB data into the uasset."))
			.Visibility_Static(&Local::GetContainVisibility, PropertyHandle)
		]
		+ SVerticalBox::Slot()
		[
			SNew(SButton)
			.OnClicked(FOnClicked::CreateStatic(&Local::OnRemoveClicked, CueSheet))
			.Text(LOCTEXT("RemoveButtonLabel", "Remove"))
			.ToolTipText(LOCTEXT("RemoveButtonTooltip", "Remove ACB data from the uasset. (To use this uasset, external ACB file is required.)"))
			.Visibility_Static(&Local::GetRemoveVisibility, PropertyHandle)
		]
	];
}

#undef LOCTEXT_NAMESPACE

/* --- end of file --- */
