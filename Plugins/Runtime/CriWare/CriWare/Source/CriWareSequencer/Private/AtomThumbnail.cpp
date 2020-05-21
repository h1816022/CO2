/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Atom Thumbnail
 * File     : AtomThumbnail.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "AtomThumbnail.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareSequencerPrivatePCH.h"
#include "Tracks/MovieSceneAtomTrack.h"
#include "Sections/MovieSceneAtomSection.h"
#include "SoundAtomCueSheet.h"

/* Unreal Engine 4関連ヘッダ */
#include "RenderUtils.h"
#include "Slate/SlateTextures.h"
#include "Engine/World.h"
#include "HAL/PlatformProcess.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "FAtomThumbnail"

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
namespace AtomThumbnail {
	struct FDecodeState {
		int32 Total;
		int32 Count;
		int16* Pcm;
	};
	float Modulate(float Value, float Delta, float Range);
	void LoadWaveform(USoundAtomCue* Cue);
	void CRIAPI OnDecode(void *obj, CriAtomPcmFormat format,
		CriSint32 num_channels, CriSint32 num_samples, void *data[]);
	void DrawPixel(TArray<uint8>& Data,
		int32 Width, int32 Height, int32 X, int32 Y, FLinearColor Color);
};

/***************************************************************************
 *      変数定義
 *      Variable Definition
 ***************************************************************************/

/***************************************************************************
 *      クラス定義
 *      Class Definition
 ***************************************************************************/
FAtomThumbnail::FAtomThumbnail(UMovieSceneSection& InSection, TRange<float> DrawRange, int32 InTextureSize, const FLinearColor& BaseColor, float DisplayScale)
	: Section(InSection)
	, Texture(NULL)
	, TextureSize(InTextureSize)
{
	UMovieSceneAtomSection* AtomSection = Cast<UMovieSceneAtomSection>(&Section);

	/* 背景色と被らない色を計算 */
	FillColor.R = BaseColor.R + 0.5f;
	FillColor.G = BaseColor.G + 0.5f;
	FillColor.B = BaseColor.B + 0.5f;
	if (FillColor.R > 1.0f) {
		FillColor.R -= 1.0f;
	}
	if (FillColor.G > 1.0f) {
		FillColor.G -= 1.0f;
	}
	if (FillColor.B > 1.0f) {
		FillColor.B -= 1.0f;
	}
	FillColor.A = 1.0f;

	if (ShouldRender()) {
		uint32 Size = GetSize().X * GetSize().Y * GPixelFormats[PF_B8G8R8A8].BlockBytes;
		TArray<uint8> RawData;
		RawData.AddZeroed(Size);

		GenerateWaveformPreview(RawData, DrawRange, DisplayScale);

		FSlateTextureDataPtr BulkData(new FSlateTextureData(GetSize().X, GetSize().Y, GPixelFormats[PF_B8G8R8A8].BlockBytes, RawData));

		Texture = new FSlateTexture2DRHIRef(GetSize().X, GetSize().Y, PF_B8G8R8A8, BulkData, TexCreate_Dynamic);

		BeginInitResource(Texture);
	}
}

FAtomThumbnail::~FAtomThumbnail()
{
	if (ShouldRender()) {
		BeginReleaseResource(Texture);

		FlushRenderingCommands();
	}

	if (Texture) {
		delete Texture;
	}
}

FIntPoint FAtomThumbnail::GetSize() const
{
	return FIntPoint(TextureSize, Section.GetTypedOuter<UMovieSceneAtomTrack>()->GetRowHeight());
}

FSlateShaderResource* FAtomThumbnail::GetViewportRenderTargetTexture() const
{
	return Texture;
}

bool FAtomThumbnail::RequiresVsync() const
{
	return false;
}

void FAtomThumbnail::GenerateWaveformPreview(TArray<uint8>& OutData, TRange<float> DrawRange, float DisplayScale)
{
	UMovieSceneAtomSection* AtomSection = Cast<UMovieSceneAtomSection>(&Section);
	if (AtomSection == nullptr) {
		return;
	}

	/* キューの情報を取得 */
	USoundAtomCue* Cue = AtomSection->GetSound();
	if (Cue == nullptr) {
		return;
	}

	/* PCMデータがロード済みかどうかチェック */
	if (Cue->RawPCMData == nullptr) {
		/* PCMデータのロード */
		AtomThumbnail::LoadWaveform(Cue);
	}

	/* ロード結果の確認 */
	const int16* LookupData = (int16*)Cue->RawPCMData;
	const int32 NumChannels = Cue->RawPCMDataChannels;
	const int32 SamplingRate = Cue->RawPCMDataSamplingRate;
	const int32 NumSamples = Cue->RawPCMDataSamples;
	if ((LookupData == nullptr) || (NumChannels <= 0) || (SamplingRate <= 0) || (NumSamples < 0)
		|| !AtomSection->HasStartFrame() || !AtomSection->HasEndFrame()) {
		return;
	}

 	/* セクション開始位置の計算 */
	FFrameRate FrameRate = AtomSection->GetTypedOuter<UMovieScene>()->GetTickResolution();
	double SectionStartTime = AtomSection->GetInclusiveStartFrame() / FrameRate;

	/* ピッチの計算 */
	float PitchMultiplierValue = AtomSection->GetPitchMultiplierChannel().GetDefault().Get(1.f);

	/* ループを考慮しない波形の長さを計算 */
	float UnloopedDuration = (float)NumSamples / (float)SamplingRate;

	/* 波形の描画範囲を計算 */
	TRange<float> AtomTrueRange = TRange<float>(
		SectionStartTime - AtomSection->GetStartOffset(),
		SectionStartTime - AtomSection->GetStartOffset() + UnloopedDuration * PitchMultiplierValue);
	float TrueRangeSize = AtomTrueRange.Size<float>();

	/* オブジェクトの左端の位置を取得 */
	float AtomSectionLower = SectionStartTime;

	/* 描画範囲を取得 */
	float DrawRangeSize = DrawRange.Size<float>();

	/* 左画面外に隠れている領域のサイズを計算 */
	float LowerTrim = DrawRange.GetLowerBoundValue() - AtomSectionLower;

	/* 見えている領域の幅と高さを取得 */
	int32 Width = GetSize().X;
	int32 Height = GetSize().Y;

	/* 波形の参照開始位置を計算 */
	int32 DrawOffsetPx = FMath::Max(FMath::RoundToInt((DrawRange.GetLowerBoundValue() - SectionStartTime) / DisplayScale), 0);

	/* チャンネル当たりの描画領域の高さを計算 */
	const int32 MaxAmplitude = GetSize().Y / NumChannels;

	/* @todo シーク位置を考慮する必要あり。 */
	// float StartOffset = AtomSection->GetStartOffset();

	/* 隠れている左端から見えている右端までのサンプル数を計算 */
	int32 DrawSamples = (int32)(NumSamples * ((LowerTrim + DrawRangeSize) / TrueRangeSize));

	/* 1ピクセルにどれだけのサンプルを描画するか計算 */
	int32 Step = DrawSamples / (Width + DrawOffsetPx);
	if (Step <= 0) {
		Step = 1;
	}

	for (int32 n = 0; n < NumChannels; n++) {
		for (int32 x = DrawOffsetPx; x < (Width + DrawOffsetPx); x++) {
			/* 波形終端以降は描画不可 */
			if (((x + 1) * Step) > NumSamples) {
				/* 備考）AtomSectionが波形より長い場合にここに到達し得る。 */
				break;
			}

			/* 振幅の取得 */
			int32 MaxValue = 0;
			int32 MinValue = 0;
			for (int32 s = 0; s < Step; s++) {
				int32 Amplitude = LookupData[(x * Step + s) * NumChannels + n];
				if (MaxValue < Amplitude) {
					MaxValue = Amplitude;
				}
				if (MinValue > Amplitude) {
					MinValue = Amplitude;
				}
			}

			/* 振幅の描画 */
			int32 Y = MaxAmplitude * n + (MaxAmplitude / 2);
			int32 StartY = Y - MaxValue * (MaxAmplitude / 2) / 32768;
			int32 EndY = Y - MinValue * (MaxAmplitude / 2) / 32768;
			for (int32 y = StartY; y < EndY; y++) {
				AtomThumbnail::DrawPixel(OutData, Width, Height, x - DrawOffsetPx, y, FillColor);
			}
		}
	}
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/
float AtomThumbnail::Modulate(float Value, float Delta, float Range)
{
	Value = FMath::Fmod(Value + Delta, Range);
	if (Value < 0.0f) {
		Value += Range;
	}

	return Value;
}

void AtomThumbnail::LoadWaveform(USoundAtomCue* Cue)
{
	/* キューシートの参照 */
	USoundAtomCueSheet* CueSheet = Cue->CueSheet;
	if (CueSheet == nullptr) {
		return;
	}

	/* キューシートのロード確認 */
	bool bIsLoaded = CueSheet->IsLoaded();
	if (bIsLoaded == false) {
		USoundAtomCueSheet::LoadAtomCueSheet(CueSheet);
	}

	/* ACBハンドルの取得 */
	CriAtomExAcbHn AcbHn = CueSheet->GetAcbHn();
	if (AcbHn == nullptr) {
		return;
	}

	/* 再生するキューに含まれる波形データの情報を取得 */
	CriAtomExWaveformInfo WaveInfo;
	criAtomExAcb_GetWaveformInfoByName(AcbHn, TCHAR_TO_UTF8(*Cue->CueName), &WaveInfo);
	if (WaveInfo.num_channels <= 0) {
		return;
	}

	/* 波形データがストリーム再生用かどうかをチェック */
	CriAtomAwbHn AwbHn;
	if (WaveInfo.streaming_flag == CRI_FALSE) {
		/* ACBハンドルからオンメモリ再生用のAWBハンドルを取得 */
		AwbHn = criAtomExAcb_GetOnMemoryAwbHandle(AcbHn);
	} else {
		/* ACBハンドルからストリーム再生用のAWBハンドルを取得 */
		AwbHn = criAtomExAcb_GetStreamingAwbHandle(AcbHn);
	}

	/* Atomプレーヤの作成 */
	CriAtomStandardPlayerConfig PlayerConfig;
	criAtomPlayer_SetDefaultConfigForStandardPlayer(&PlayerConfig);
	PlayerConfig.max_channels = WaveInfo.num_channels;
	PlayerConfig.max_sampling_rate = WaveInfo.sampling_rate;
	PlayerConfig.streaming_flag = WaveInfo.streaming_flag;
	CriAtomPlayerHn Player = criAtomPlayer_CreateStandardPlayer(&PlayerConfig, NULL, 0);
	if (Player == NULL) {
		return;
	}

	/* 出力バッファの確保 */
	AtomThumbnail::FDecodeState DecodeState;
	DecodeState.Total = WaveInfo.num_samples;
	DecodeState.Count = 0;
	DecodeState.Pcm = (int16*)FMemory::Malloc(
		sizeof(int16) * WaveInfo.num_channels * WaveInfo.num_samples);
	if (DecodeState.Pcm == nullptr) {
		return;
	}

	/* フィルタコールバックを設定 */
	criAtomPlayer_SetDecodeCallback(Player, AtomThumbnail::OnDecode, &DecodeState);

	/* ループ再生を無効化 */
	criAtomPlayer_LimitLoopCount(Player, CRIATOMPLAYER_IGNORE_LOOP);

	/* ミュート */
	criAtomPlayer_SetVolume(Player, 0.0f);

	/* 再生準備の開始 */
	criAtomPlayer_SetWaveId(Player, AwbHn, WaveInfo.wave_id);
	criAtomPlayer_Pause(Player, CRI_TRUE);
	criAtomPlayer_Start(Player);

	/* 準備完了待ち */
	for (;;) {
		/* 再生状態の取得 */
		CriAtomPlayerStatus Status = criAtomPlayer_GetStatus(Player);
		if (Status != CRIATOMPLAYER_STATUS_PREP) {
			break;
		}

		/* しばらく待機 */
		FPlatformProcess::Sleep(0.01);
	}

	/* サンプルを全て破棄 */
	criAtomPlayer_DiscardSamples(Player, WaveInfo.num_samples);
	criAtomPlayer_Pause(Player, CRI_FALSE);

	/* 再生完了待ち */
	for (;;) {
		/* 再生状態の取得 */
		CriAtomPlayerStatus Status = criAtomPlayer_GetStatus(Player);
		if (Status != CRIATOMPLAYER_STATUS_PLAYING) {
			break;
		}

		/* しばらく待機 */
		FPlatformProcess::Sleep(0.01);
	}

	/* プレーヤの破棄 */
	criAtomPlayer_Destroy(Player);

	/* デコード結果の確認 */
	if (DecodeState.Count != DecodeState.Total) {
		FMemory::Free(DecodeState.Pcm);
		return;
	}

	/* 結果の保存 */
	Cue->RawPCMData = (uint8*)DecodeState.Pcm;
	Cue->RawPCMDataChannels = WaveInfo.num_channels;
	Cue->RawPCMDataSamplingRate = WaveInfo.sampling_rate;
	Cue->RawPCMDataSamples = WaveInfo.num_samples;
}

void CRIAPI AtomThumbnail::OnDecode(void *obj, CriAtomPcmFormat format,
	CriSint32 num_channels, CriSint32 num_samples, void *data[])
{
	AtomThumbnail::FDecodeState* DecodeStatePtr = (AtomThumbnail::FDecodeState*)obj;

	/* クリッピング */
	num_channels = FMath::Min((int32)num_channels, 8);
	num_samples = FMath::Min((int32)num_samples, (DecodeStatePtr->Total - DecodeStatePtr->Count));

	/* 入力データの参照 */
	float* Source[8];
	for (int32 n = 0; n < num_channels; n++) {
		Source[n] = (float*)data[n];
	}

	/* デコード結果の保存 */
	int16* Dest = &DecodeStatePtr->Pcm[DecodeStatePtr->Count * num_channels];
	for (int32 i = 0; i < num_samples; i++) {
		for (int32 n = 0; n < num_channels; n++) {
			int32 Value = Source[n][i] * 32768.0f;
			Value = FMath::Clamp(Value, (int32)MIN_int16, (int32)MAX_int16);
			Dest[i * num_channels + n] = (int16)Value;
		}
	}

	/* サンプル数の更新 */
	DecodeStatePtr->Count += num_samples;
}

void AtomThumbnail::DrawPixel(TArray<uint8>& Data,
	int32 Width, int32 Height, int32 X, int32 Y, FLinearColor Color)
{
	/* 領域外のアクセスを防止 */
	if ((X < 0) || (X >= Width) || (Y < 0) || (Y >= Height)) {
		return;
	}

	/* ピクセル位置の計算 */
	int32 Index = (Y * Width + X) * GPixelFormats[PF_B8G8R8A8].BlockBytes;

	/* ピクセルの色を設定 */
	uint8* Pixel = &Data[Index];
	*Pixel++ = Color.B * 255;
	*Pixel++ = Color.G * 255;
	*Pixel++ = Color.R * 255;
	*Pixel++ = Color.A * 255;
}

#undef LOCTEXT_NAMESPACE

/* --- end of file --- */
