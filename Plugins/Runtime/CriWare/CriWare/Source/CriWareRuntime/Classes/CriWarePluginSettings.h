/****************************************************************************
*
* CRI Middleware SDK
*
* Copyright (c) 2015-2017 CRI Middleware Co., Ltd.
*
* Library  : CRIWARE plugin for Unreal Engine 4
* Module   : PluginSettings
* File     : CriWarePluginSettings.h
*
****************************************************************************/

/* 備考）SSourceControlSubmit.cpp を参考に作成。 */

/* 多重定義防止 */
#pragma once

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* Unreal Engine 4関連ヘッダ */
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/ScriptMacros.h"
#include "Engine/EngineTypes.h"

/* モジュールヘッダ */
#include "CriWarePluginSettings.generated.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#if !defined(CRIWARE_UE4_LE)	/* <cri_delete_if_LE> */
#else	/* </cri_delete_if_LE> */
#define NUM_FILESYSTEM_SECTIONS 6
#define NUM_ATOM_SECTIONS 10

#define NUM_ENGINEDIR_INIFILE 2
#define NUM_PROJECTDIR_INIFILE 2
#endif
#define NUM_INIFILE (NUM_ENGINEDIR_INIFILE + NUM_PROJECTDIR_INIFILE)

/***************************************************************************
 *      処理マクロ
 *      Macro Functions
 ***************************************************************************/

/***************************************************************************
 *      データ型宣言
 *      Data Type Declarations
 ***************************************************************************/
/* CriWareIniPathに格納されるPathと配列の番号対応 */
UENUM()
namespace EEngineIniFileType
{
	enum Type
	{
		EngBaseEngineIni = 0,
		EngWindowsEngineIni,
#if !defined(CRIWARE_UE4_LE)	/* <cri_delete_if_LE> */
#endif	/* </cri_delete_if_LE> */
		ProjDefaultEngineIni,
		ProjWindowsEngineIni,
#if !defined(CRIWARE_UE4_LE)	/* <cri_delete_if_LE> */
#endif	/* </cri_delete_if_LE> */
	};
}

/* サウンドレンダラタイプ */
UENUM()
namespace EAtomSoundRendererType
{
	enum Type
	{
		/* 未指定 */
		Any = 0,

		/* Native Sound Renderer */
		Native = 1,

		/* Atom Sound Renderer */
		Asr = 2,

		/* Hardware */
		Hardware1 = 1,
		Hardware2 = 5,
		Hardware3 = 9,
		Hardware4 = 13,

		/* PS4 Pad Speaker */
		Pad = 255
	};
}

/* ASRラック設定 */
USTRUCT()
struct FAtomAsrRackConfigUI
{
	GENERATED_USTRUCT_BODY()

	/* サウンドレンダラタイプ */
	UPROPERTY(EditAnywhere, Category="AtomAsrRackConfig", meta = (DisplayName = "Sound Renderer Type"))
	TEnumAsByte<EAtomSoundRendererType::Type> SoundRendererTypeUI;

	/* ID */
	UPROPERTY(VisibleAnywhere, Category = "AtomAsrRackConfig")
	int32 ElementID;
};

/* ASRラック設定 */
USTRUCT()
struct FAtomAsrRackConfig
{
	GENERATED_USTRUCT_BODY()

	/* サウンドレンダラタイプ */
	UPROPERTY(VisibleAnywhere, Category = "AtomAsrRackConfig")
	int32 SoundRendererType;
};

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
UCLASS(config = Engine, defaultconfig, meta=(ToolTip="CriWarePluginSettings class."))
class CRIWARERUNTIME_API UCriWarePluginSettings : public UObject
{
	GENERATED_UCLASS_BODY()


	/* false:CriWare.iniが存在する、true:CriWare.iniが存在しない */
	/* CriWare.iniが存在する場合ProjectSettingsからのパラメータ編集を可否を決定するeditcondition用の変数 */
	/* ProjectSettingsからのパラメータ変更をできなくするための変数 */
	UPROPERTY(config, VisibleDefaultsOnly, Category = "CheckExistingOldConfigrationFiles", AdvancedDisplay,
		meta = (
			ConsoleVariable = "IsExistingOldFormatConfigFile",
			DisplayName = "Is Not Existing Old Format Configration File",
			Tooltip = "Not existing: checked, existing: unchecked."
			)
	)
	bool bNoExistCriWareIni;

	/* === FileSystem関連パラメータ === */
	/* コンテンツ配置場所のパス（UI表示用） */
	UPROPERTY(EditAnyWhere, Category = "FileSystem",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ConsoleVariable = "NonAssetContentDir",
			DisplayName = "Non-Asset Content Directory",
			Tooltip = "Content directory where non-asset files are stored."
			)
	)
	FDirectoryPath NonAssetContentDir;

	/* コンテンツ配置場所のパス文字列（iniファイル書き込み用） */
	UPROPERTY(config)
	FString ContentDir;
	FString AppliedContentDir;

	/* バインダ数 */
	UPROPERTY(config, EditAnyWhere, Category = "FileSystem",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "NumBinders",
			DisplayName = "Number of Binders",
			Tooltip = "Number of binders."
		)
	)
	int32 NumBinders;
	int32 AppliedNumBinders;

	/* 最大バインド回数 */
	UPROPERTY(config, EditAnyWhere, Category = "FileSystem",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "MaxBinds",
			DisplayName = "Maximum Number of Binds",
			Tooltip = "Maximum number of binds."
		)
	)
	int32 MaxBinds;
	int32 AppliedMaxBinds;

	/* ローダ数 */
	UPROPERTY(config, EditAnyWhere, Category = "FileSystem",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "NumLoaders",
			DisplayName = "Number of Loaders",
			Tooltip = "Number of loaders."
		)
	)
	int32 NumLoaders;
	int32 AppliedNumLoaders;

	/* パスの最大長 */
	UPROPERTY(config, EditAnyWhere, Category = "FileSystem",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "MaxPath",
			DisplayName = "Maximum Path Length",
			Tooltip = "Maximum length for a path."
		)
	)
	int32 MaxPath;
	int32 AppliedMaxPath;

	/* ログ出力を行うかどうかの指定値 */
	UPROPERTY(config, EditAnyWhere, Category = "FileSystem",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ConsoleVariable = "OutputsLogFileSystem",
			DisplayName = "Output log",
			Tooltip = "Enable log output."
		)
	)
	bool OutputsLogFileSystem;
	bool AppliedOutputsLogFileSystem;

	/* <cri_delete_if_LE> */
	/* </cri_delete_if_LE> */

	/* === ATOM関連パラメータ === */
	/* キューアセットを自動的に作成するかどうかの指定値 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ConsoleVariable = "AutomaticallyCreateCueAsset",
			DisplayName = "Automatically Create Cue Asset",
			Tooltip = "Automatically create cue asset at ACB file import."
		)
	)
	bool AutomaticallyCreateCueAsset;

	/* インゲームプレビューを使用するかどうかの指定値 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ConsoleVariable = "UsesInGamePreview",
			DisplayName = "Use In Game Preview",
			Tooltip = "Enable In-Game-Preview functionality."
		)
	)
	bool UsesInGamePreview;
	bool AppliedUsesInGamePreview;

	/* ログ出力を行うかどうかの指定値 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ConsoleVariable = "OutputsLogAtom",
			DisplayName = "Output Log",
			Tooltip = "Enable log output."
		)
	)
	bool OutputsLogAtom;
	bool AppliedOutputsLogAtom;

	/* 最大バーチャルボイス数 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ClampMax = "32767",
			ConsoleVariable = "MaxVirtualVoices",
			DisplayName = "Maximum Number of Virtual Voices",
			Tooltip = "Maximum number of virtual voices."
		)
	)
	int32 MaxVirtualVoices;
	int32 AppliedMaxVirtualVoices;

	/* メモリ再生に使用するボイス数 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "NumStandardMemoryVoices",
			DisplayName = "Number of Standard Memory Voices",
			Tooltip = "Number of standard memory voices."
		)
	)
	int32 NumStandardMemoryVoices;
	int32 AppliedNumStandardMemoryVoices;

	/* メモリ再生用ボイスで再生可能な最大チャンネル数 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "StandardMemoryVoiceNumChannels",
			DisplayName = "Number of Channels of Standard Memory Voice",
			Tooltip = "Number of channels of standard memory voice."
		)
	)
	int32 StandardMemoryVoiceNumChannels;
	int32 AppliedStandardMemoryVoiceNumChannels;

	/* メモリ再生用ボイスで再生可能な最大サンプリングレート */
	UPROPERTY(config, EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ConsoleVariable = "StandardMemoryVoiceSamplingRate",
			DisplayName = "Sampling Rate of Standard Memory Voice",
			Tooltip = "Standard memory voice sampling rate."
		)
	)
	int32 StandardMemoryVoiceSamplingRate;
	int32 AppliedStandardMemoryVoiceSamplingRate;

	/* ストリーム再生兼用（メモリ再生とストリーム再生の両方が可能な）ボイスの数 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "NumStandardStreamingVoices",
			DisplayName = "Number of Standard Streaming Voices",
			Tooltip = "Number of standard streaming voices."
		)
	)
	int32 NumStandardStreamingVoices;
	int32 AppliedNumStandardStreamingVoices;

	/* ストリーム再生兼用ボイスで再生可能な最大チャンネル数 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "StandardStreamingVoiceNumChannels",
			DisplayName = "Number of Channels of Standard Streaming Voice",
			Tooltip = "Number of channels of standard streaming voice."
		)
	)
	int32 StandardStreamingVoiceNumChannels;
	int32 AppliedStandardStreamingVoiceNumChannels;

	/* ストリーム再生兼用ボイスで再生可能な最大サンプリングレート */
	UPROPERTY(config, EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "StandardStreamingVoiceSamplingRate",
			DisplayName = "Sampling Rate of Standard Streaming Voice",
			Tooltip = "Standard streaming voice sampling rate."
		)
	)
	int32 StandardStreamingVoiceSamplingRate;
	int32 AppliedStandardStreamingVoiceSamplingRate;

	UPROPERTY(config, EditAnywhere, Category="Atom",
		meta=(
			editcondition = "bNoExistCriWareIni",
			AllowedClasses="SoundAtomConfig",
			ConsoleVariable = "AtomConfig",
			DisplayName = "Atom Config",
			Tooltip = "Atom Config asset."
		)
	)
	FSoftObjectPath AtomConfig;
	FSoftObjectPath AppliedAtomConfig;

	/* DEPRECATED - Use AtomConfig instead. */
	UPROPERTY(config)
	FString AcfFileName;

	/* 距離係数 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "DistanceFactor",
			DisplayName = "Distance Factor",
			Tooltip = "Atom distance factor."
		)
	)
	float DistanceFactor;
	float AppliedDistanceFactor;

	/* サウンドレンダラタイプ */
	UPROPERTY(EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ConsoleVariable = "SoundRendererType",
			DisplayName = "Sound Renderer Type",
			Tooltip = "Sound renderer type of library output."
		)
	)
	TEnumAsByte<EAtomSoundRendererType::Type> SoundRendererTypeUI;

	UPROPERTY(config)
	int32 SoundRendererType;
	int32 AppliedSoundRendererType;

	/* ASRラック設定 */
	UPROPERTY(EditAnyWhere, Category = "Atom",
		meta = (
			editcondition = "bNoExistCriWareIni",
			ConsoleVariable = "AsrRackConfig",
			DisplayName = "Asr Rack Config",
			Tooltip = "Configuration of additional ASR Rack."
		)
	)
	TArray<FAtomAsrRackConfigUI> AsrRackConfigUI;

	UPROPERTY(config)
	TArray<FAtomAsrRackConfig> AsrRackConfig;
	TArray<FAtomAsrRackConfig> AppliedAsrRackConfig;

	UPROPERTY(config)
	FString Hardware1;

	UPROPERTY(config)
	FString Hardware2;

	UPROPERTY(config)
	FString Hardware3;

	UPROPERTY(config)
	FString Hardware4;

	/* HCA-MXボイスのサンプリングレート */
	UPROPERTY(config, EditAnyWhere, Category = "Atom", AdvancedDisplay,
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "HcaMxVoiceSamplingRate",
			DisplayName = "Sampling Rate of HCA-MX Voice",
			Tooltip = "HCA-MX voice sampling rate."
		)
	)
	int32 HcaMxVoiceSamplingRate;
	int32 AppliedHcaMxVoiceSamplingRate;

	/* HCA-MXメモリ再生に使用するボイス数 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom", AdvancedDisplay,
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "NumHcaMxMemoryVoices",
			DisplayName = "Number of HCA-MX Memory Voices",
			Tooltip = "Number of HCA-MX memory voices."
		)
	)
	int32 NumHcaMxMemoryVoices;
	int32 AppliedNumHcaMxMemoryVoices;

	/* HCA-MXメモリ再生用ボイスで再生可能な最大チャンネル数 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom", AdvancedDisplay,
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "HcaMxMemoryVoiceNumChannels",
			DisplayName = "Number of Channels of HCA-MX Memory Voice",
			Tooltip = "Number of channels of HCA-MX memory voice."
		)
	)
	int32 HcaMxMemoryVoiceNumChannels;
	int32 AppliedHcaMxMemoryVoiceNumChannels;

	/* HCA-MXストリーム再生兼用（メモリ再生とストリーム再生の両方が可能な）ボイスの数 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom", AdvancedDisplay,
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "NumHcaMxStreamingVoices",
			DisplayName = "Number of HCA-MX Streaming Voices",
			Tooltip = "Number of HCA-MX streaming voices."
		)
	)
	int32 NumHcaMxStreamingVoices;
	int32 AppliedNumHcaMxStreamingVoices;

	/* HCA-MXストリーム再生兼用ボイスで再生可能な最大チャンネル数 */
	UPROPERTY(config, EditAnyWhere, Category = "Atom", AdvancedDisplay,
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "HcaMxStreamingVoiceNumChannels",
			DisplayName = "Number of Channels of HCA-MX Streaming Voice",
			Tooltip = "Number of channels of HCA-MX streaming voice."
		)
	)
	int32 HcaMxStreamingVoiceNumChannels;
	int32 AppliedHcaMxStreamingVoiceNumChannels;

	UPROPERTY(config, EditAnyWhere, Category = "Atom", AdvancedDisplay,
		meta = (
			editcondition = "bNoExistCriWareIni",
			ConsoleVariable = "WASAPI_IsExclusive",
			DisplayName = "WASAPI Is Exclusive",
			Tooltip = "WASAPI is exclusive."
		)
	)
	bool WASAPI_IsExclusive;
	bool AppliedWASAPI_IsExclusive;

	UPROPERTY(config, EditAnyWhere, Category = "Atom", AdvancedDisplay,
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "WASAPI_BitsPerSample",
			DisplayName = "WASAPI Bits Per Sample",
			Tooltip = "WASAPI bits per sample."
		)
	)
	int32 WASAPI_BitsPerSample;
	int32 AppliedWASAPI_BitsPerSample;

	UPROPERTY(config, EditAnyWhere, Category = "Atom", AdvancedDisplay,
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "WASAPI_SamplingRate",
			DisplayName = "WASAPI Sampling Rate",
			Tooltip = "WASAPI sampling rate."
		)
	)
	int32 WASAPI_SamplingRate;
	int32 AppliedWASAPI_SamplingRate;

	UPROPERTY(config, EditAnyWhere, Category = "Atom", AdvancedDisplay,
		meta = (
			editcondition = "bNoExistCriWareIni",
			ClampMin = "0",
			ConsoleVariable = "WASAPI_NumChannels",
			DisplayName = "WASAPI Number of Output Channels",
			Tooltip = "WASAPI number of output channels."
		)
	)
	int32 WASAPI_NumChannels;
	int32 AppliedWASAPI_NumChannels;

	/* <cri_delete_if_LE> */
	/* </cri_delete_if_LE> */

public:
#if WITH_EDITOR
	/* Try to load any configuration possible, convert then if needed or update from source control if new version available. */
	void InitializeSettings();

	/* CriWare.iniが存在するか確認する関数 */
	bool IsExistingCriWareIniFile() const;

	/* ConfigファイルをCriWare.iniからEngine.iniにコンバートするための関数 */
	bool ConvertConfigrationFile();

	bool IsMixedConfigFiles() const;

	/* コンバート時に削除するCriWare.iniのファイルの名前を取得する関数 */
	TArray<FString> GetDeletedFilesName() const;

	/* UE4がProjectSettingでの変数の変更をチェックする関数 */
	bool HasPendingChanges() const;

	/** Returns an event delegate that is executed when a setting has changed. */
	DECLARE_EVENT(UCriWarePluginSetting, FSettingChangedEvent);
	FSettingChangedEvent& OnSettingChanged() { return SettingChangedEvent; }

	/* SourceControl接続時ファイルをチェックアウトするための関数 */
	/* filenameにパスを含むファイル名を入力することでそのファイルをチェックアウトすることができる */
	void CheckoutConfigFile(FString fileName);

	/* 各ヒエラルキーに該当するCriWare.iniファイルパス格納用アレイ */
	TArray<FString> CriWareIniFilePath;
#endif

	/* 各ヒエラルキーに該当するEngine.iniファイルパス格納用アレイ */
	TArray<FString> EngineIniFilePath;

protected:
#if WITH_EDITOR
	/** Called when a property on this object is changed */
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
#if WITH_EDITOR
	bool CreateEngineIniFile(FString EngineIniFileName, FString CriWareIniFileName);
#endif

	void UpdateUProperty(int isConvert);

	/* GConfig->GetSectionでとりだしたセクション情報が"ContentDir=AudioData"というようにセクション名とパラメタ情報がセットとなっている */
	/* 取得した情報の"="以下を取得するための関数 */
	FString GetParameterString(const TArray<FString>& str, FString SelectorName);

	/* Same as GetParameterString() but for arrays. */
	TArray<FString> GetParemeterArray(const TArray<FString>& str, FString SelectorName);
	TArray<FAtomAsrRackConfig> GetParemeterArrayAsr(const TArray<FString>& str, FString SelectorName);

	/* UProperty変数にConfigファイルから取得したパラメータを代入する関数 */
	void InitializeCriWarePlugins(const TArray<FString>& Section_UClass);

	/* Iniファイルに記載されるパラメータが空の場合にデフォルト値を設定するための関数 */
	FString CheckIniParamString(FString ini_param_string, int Ddefault_value);
	FString CheckIniParamString(FString ini_param_string, float Ddefault_value);
	FString CheckIniParamString(FString ini_param_string, FString default_value);

#if WITH_EDITOR
	/* 旧フォーマットのデータを新フォーマットのデータに上書きするための関数 */
	void UpdateCriData(TArray<FString> Section_Old, TArray<FString>* Section_New, FString CategoryType);
	void ConvertCriData(TArray<FString> Section_Old, TArray<FString>* Section_New, FString CategoryType);
#endif

#if WITH_EDITOR
	/** Holds an event delegate that is executed when a setting has changed. */
	FSettingChangedEvent SettingChangedEvent;
#endif
};

/***************************************************************************
 *      関数宣言
 *      Prototype Functions
 ***************************************************************************/

/* --- end of file --- */
