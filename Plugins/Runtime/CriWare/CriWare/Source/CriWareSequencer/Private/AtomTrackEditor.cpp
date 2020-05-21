/****************************************************************************
 *
 * CRI Middleware SDK
 *
 * Copyright (c) 2017-2018 CRI Middleware Co., Ltd.
 *
 * Library  : CRIWARE plugin for Unreal Engine 4
 * Module   : Atom Track Editor
 * File     : AtomTrackEditor.cpp
 *
 ****************************************************************************/

/***************************************************************************
 *      インクルードファイル
 *      Include files
 ***************************************************************************/
/* モジュールヘッダ */
#include "AtomTrackEditor.h"

/* CRIWAREプラグインヘッダ */
#include "CriWareSequencerPrivatePCH.h"
#include "Tracks/MovieSceneAtomTrack.h"
#include "Sections/MovieSceneAtomSection.h"

/* Unreal Engine 4関連ヘッダ */
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SBox.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "EditorStyleSet.h"
#include "SequencerUtilities.h"
#include "AssetRegistryModule.h"
#include "IContentBrowserSingleton.h"
#include "ContentBrowserModule.h"
#include "ISectionLayoutBuilder.h"
#include "CommonMovieSceneTools.h"
#include "DragAndDrop/AssetDragDropOp.h"
#include "Misc/QualifiedFrameTime.h"

/***************************************************************************
 *      定数マクロ
 *      Macro Constants
 ***************************************************************************/
#define LOCTEXT_NAMESPACE "FAtomTrackEditor"

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
FAtomTrackEditor::FAtomTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer)
{
}

FAtomTrackEditor::~FAtomTrackEditor()
{
}

TSharedRef<ISequencerTrackEditor> FAtomTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer)
{
	return MakeShareable(new FAtomTrackEditor(InSequencer));
}

void FAtomTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddTrack", "Atom Track"),
		LOCTEXT("AddTooltip", "Adds a new master audio track that can play sounds."),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Atom"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FAtomTrackEditor::HandleAddAtomTrackMenuEntryExecute)
		)
	);
}

bool FAtomTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const
{
	return Type == UMovieSceneAtomTrack::StaticClass();
}

void FAtomTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track)
{
}

const FSlateBrush* FAtomTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

bool FAtomTrackEditor::IsResizable(UMovieSceneTrack* InTrack) const
{
	return true;
}

void FAtomTrackEditor::Resize(float NewSize, UMovieSceneTrack* InTrack)
{
	UMovieSceneAtomTrack* AtomTrack = Cast<UMovieSceneAtomTrack>(InTrack);
	if (AtomTrack) {
		AtomTrack->Modify();

		int32 MaxNumRows = 1;
		for (UMovieSceneSection* Section : AtomTrack->GetAllSections()) {
			MaxNumRows = FMath::Max(MaxNumRows, Section->GetRowIndex() + 1);
		}

		AtomTrack->SetRowHeight(FMath::RoundToInt(NewSize) / MaxNumRows);
	}
}

bool FAtomTrackEditor::OnAllowDrop(const FDragDropEvent& DragDropEvent, UMovieSceneTrack* Track, int32 RowIndex, const FGuid& TargetObjectGuid)
{
	if (!Track->IsA(UMovieSceneAtomTrack::StaticClass())) {
		return false;
	}

	TSharedPtr<FDragDropOperation> Operation = DragDropEvent.GetOperation();

	if (!Operation.IsValid() || !Operation->IsOfType<FAssetDragDropOp>()) {
		return false;
	}

	TSharedPtr<FAssetDragDropOp> DragDropOp = StaticCastSharedPtr<FAssetDragDropOp>(Operation);

	for (const FAssetData& AssetData : DragDropOp->GetAssets()) {
		if (Cast<USoundAtomCue>(AssetData.GetAsset())) {
			return true;
		}
	}

	return false;
}

FReply FAtomTrackEditor::OnDrop(const FDragDropEvent& DragDropEvent, UMovieSceneTrack* Track, int32 RowIndex, const FGuid& TargetObjectGuid)
{
	if (!Track->IsA(UMovieSceneAtomTrack::StaticClass()))
	{
		return FReply::Unhandled();
	}

	TSharedPtr<FDragDropOperation> Operation = DragDropEvent.GetOperation();

	if (!Operation.IsValid() || !Operation->IsOfType<FAssetDragDropOp>()) {
		return FReply::Unhandled();
	}

	TSharedPtr<FAssetDragDropOp> DragDropOp = StaticCastSharedPtr<FAssetDragDropOp>(Operation);

	bool bAnyDropped = false;
	for (const FAssetData& AssetData : DragDropOp->GetAssets()) {
		USoundAtomCue* Sound = Cast<USoundAtomCue>(AssetData.GetAsset());

		if (Sound) {
			AnimatablePropertyChanged(FOnKeyProperty::CreateRaw(this, &FAtomTrackEditor::AddNewMasterSound, Sound, RowIndex));

			bAnyDropped = true;
		}
	}

	return bAnyDropped ? FReply::Handled() : FReply::Unhandled();
}

TSharedRef<ISequencerSection> FAtomTrackEditor::MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding)
{
	check(SupportsType(SectionObject.GetOuter()->GetClass()));
	return MakeShareable(new FAtomSection(SectionObject, GetSequencer()));
}

TSharedPtr<SWidget> FAtomTrackEditor::BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params)
{
	// Create a container edit box
	return SNew(SHorizontalBox)

	// Add the audio combo box
	+ SHorizontalBox::Slot()
	.AutoWidth()
	.VAlign(VAlign_Center)
	[
#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 22
		FSequencerUtilities::MakeAddButton(LOCTEXT("AtomText", "Atom"), FOnGetContent::CreateSP(this, &FAtomTrackEditor::BuildAtomSubMenu, Track), Params.NodeIsHovered, GetSequencer())
#else
		FSequencerUtilities::MakeAddButton(LOCTEXT("AtomText", "Atom"), FOnGetContent::CreateSP(this, &FAtomTrackEditor::BuildAtomSubMenu, Track), Params.NodeIsHovered)
#endif
	];
}

bool FAtomTrackEditor::HandleAssetAdded(UObject* Asset, const FGuid& TargetObjectGuid)
{
	if (Asset->IsA<USoundAtomCue>()) {
		auto Sound = Cast<USoundAtomCue>(Asset);

		const FScopedTransaction Transaction(LOCTEXT("AddAtom_Transaction", "Add Atom"));

		if (TargetObjectGuid.IsValid()) {
			TArray<TWeakObjectPtr<>> OutObjects;
			for (TWeakObjectPtr<> Object : GetSequencer()->FindObjectsInCurrentSequence(TargetObjectGuid)) {
				OutObjects.Add(Object);
			}

			AnimatablePropertyChanged(FOnKeyProperty::CreateRaw(this, &FAtomTrackEditor::AddNewAttachedSound, Sound, OutObjects));
		} else {
			int32 RowIndex = INDEX_NONE;
			AnimatablePropertyChanged( FOnKeyProperty::CreateRaw(this, &FAtomTrackEditor::AddNewMasterSound, Sound, RowIndex));
		}

		return true;
	}
	return false;
}

FKeyPropertyResult FAtomTrackEditor::AddNewMasterSound(FFrameNumber KeyTime, USoundAtomCue* Sound, int32 RowIndex)
{
	FKeyPropertyResult KeyPropertyResult;

	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	FocusedMovieScene->Modify();

	FFindOrCreateMasterTrackResult<UMovieSceneAtomTrack> TrackResult = FindOrCreateMasterTrack<UMovieSceneAtomTrack>();
	UMovieSceneTrack* Track = TrackResult.Track;
	Track->Modify();

	auto AtomTrack = Cast<UMovieSceneAtomTrack>(Track);
	UMovieSceneSection* NewSection = AtomTrack->AddNewSoundOnRow(Sound, KeyTime, RowIndex);

	if (TrackResult.bWasCreated) {
		AtomTrack->SetDisplayName(LOCTEXT("AtomTrackName", "Atom"));
	}

	KeyPropertyResult.bTrackModified = true;

	GetSequencer()->EmptySelection();
	GetSequencer()->SelectSection(NewSection);
	GetSequencer()->ThrobSectionSelection();

	return KeyPropertyResult;
}

FKeyPropertyResult FAtomTrackEditor::AddNewAttachedSound(FFrameNumber KeyTime, USoundAtomCue* Sound, TArray<TWeakObjectPtr<UObject>> ObjectsToAttachTo)
{
	FKeyPropertyResult KeyPropertyResult;

	for(int32 ObjectIndex = 0; ObjectIndex < ObjectsToAttachTo.Num(); ++ObjectIndex) {
		UObject* Object = ObjectsToAttachTo[ObjectIndex].Get();

		FFindOrCreateHandleResult HandleResult = FindOrCreateHandleToObject(Object);
		FGuid ObjectHandle = HandleResult.Handle;
		KeyPropertyResult.bHandleCreated |= HandleResult.bWasCreated;

		if (ObjectHandle.IsValid()) {
			FFindOrCreateTrackResult TrackResult = FindOrCreateTrackForObject(ObjectHandle, UMovieSceneAtomTrack::StaticClass());
			UMovieSceneTrack* Track = TrackResult.Track;
			KeyPropertyResult.bTrackCreated |= TrackResult.bWasCreated;

			if (ensure(Track)) {
				auto AtomTrack = Cast<UMovieSceneAtomTrack>(Track);
				AtomTrack->Modify();
				UMovieSceneSection* NewSection = AtomTrack->AddNewSound(Sound, KeyTime);
				AtomTrack->SetDisplayName(LOCTEXT("AtomTrackName", "Atom"));
				KeyPropertyResult.bTrackModified = true;

				GetSequencer()->EmptySelection();
				GetSequencer()->SelectSection(NewSection);
				GetSequencer()->ThrobSectionSelection();
			}
		}
	}

	return KeyPropertyResult;
}

void FAtomTrackEditor::HandleAddAtomTrackMenuEntryExecute()
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	if (FocusedMovieScene == nullptr) {
		return;
	}

	const FScopedTransaction Transaction(NSLOCTEXT("Sequencer", "AddAtomTrack_Transaction", "Add Atom Track"));
	FocusedMovieScene->Modify();

	auto NewTrack = FocusedMovieScene->AddMasterTrack<UMovieSceneAtomTrack>();
	ensure(NewTrack);
	NewTrack->SetDisplayName(LOCTEXT("AtomTrackName", "Atom"));

	if (GetSequencer().IsValid()) {
#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION > 22
		GetSequencer()->OnAddTrack(NewTrack, FGuid());
#else
		GetSequencer()->OnAddTrack(NewTrack);
#endif
	}

	GetSequencer()->NotifyMovieSceneDataChanged(EMovieSceneDataChangeType::MovieSceneStructureItemAdded);
}

TSharedRef<SWidget> FAtomTrackEditor::BuildAtomSubMenu(UMovieSceneTrack* Track)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	TArray<FName> ClassNames;
	ClassNames.Add(USoundAtomCue::StaticClass()->GetFName());
	TSet<FName> DerivedClassNames;
	AssetRegistryModule.Get().GetDerivedClassNames(ClassNames, TSet<FName>(), DerivedClassNames);

	FMenuBuilder MenuBuilder(true, nullptr);

	FAssetPickerConfig AssetPickerConfig;
	{
		AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateRaw(this, &FAtomTrackEditor::OnAtomAssetSelected, Track);
		AssetPickerConfig.OnAssetEnterPressed = FOnAssetEnterPressed::CreateRaw( this, &FAtomTrackEditor::OnAtomAssetEnterPressed, Track);
		AssetPickerConfig.bAllowNullSelection = false;
		AssetPickerConfig.InitialAssetViewType = EAssetViewType::List;
		for (auto ClassName : DerivedClassNames) {
			AssetPickerConfig.Filter.ClassNames.Add(ClassName);
		}
	}

	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>(TEXT("ContentBrowser"));

	TSharedPtr<SBox> MenuEntry = SNew(SBox)
		.WidthOverride(300.0f)
		.HeightOverride(300.f)
		[
			ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig)
		];

	MenuBuilder.AddWidget(MenuEntry.ToSharedRef(), FText::GetEmpty(), true);

	return MenuBuilder.MakeWidget();
}

void FAtomTrackEditor::OnAtomAssetSelected(const FAssetData& AssetData, UMovieSceneTrack* Track)
{
	FSlateApplication::Get().DismissAllMenus();

	UObject* SelectedObject = AssetData.GetAsset();

	if (SelectedObject) {
		USoundAtomCue* NewSound = CastChecked<USoundAtomCue>(AssetData.GetAsset());
		if (NewSound != nullptr) {
			const FScopedTransaction Transaction(NSLOCTEXT("Sequencer", "AddAtom_Transaction", "Add Atom"));

			auto AtomTrack = Cast<UMovieSceneAtomTrack>(Track);
			AtomTrack->Modify();

			FFrameTime KeyTime = GetSequencer()->GetLocalTime().Time;
			UMovieSceneSection* NewSection = AtomTrack->AddNewSound(NewSound, KeyTime.FrameNumber);

			GetSequencer()->EmptySelection();
			GetSequencer()->SelectSection(NewSection);
			GetSequencer()->ThrobSectionSelection();

			GetSequencer()->NotifyMovieSceneDataChanged(EMovieSceneDataChangeType::MovieSceneStructureItemAdded);
		}
	}
}

void FAtomTrackEditor::OnAtomAssetEnterPressed(const TArray<FAssetData>& AssetData, UMovieSceneTrack* Track)
{
	if (AssetData.Num() > 0) {
		OnAtomAssetSelected(AssetData[0].GetAsset(), Track);
	}
}

FAtomSection::FAtomSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer)
	: Sequencer(InSequencer)
	, Section(InSection)
	, StoredDrawRange(TRange<float>::Empty())
	, StoredSectionHeight(0.f)
	, InitialStartOffsetDuringResize(0)
	, InitialStartTimeDuringResize(0)
{
}

FAtomSection::~FAtomSection()
{
}

UMovieSceneSection* FAtomSection::GetSectionObject()
{
	return &Section;
}

FText FAtomSection::GetSectionTitle() const
{
	UMovieSceneAtomSection* AtomSection = Cast<UMovieSceneAtomSection>(&Section);
	if (AtomSection && AtomSection->GetSound()) {
		return FText::FromString(AtomSection->GetSound()->GetName());
	}

	return NSLOCTEXT("FAtomSection", "NoAtomTitleName", "No Atom");
}

float FAtomSection::GetSectionHeight() const
{
	return Section.GetTypedOuter<UMovieSceneAtomTrack>()->GetRowHeight();
}

int32 FAtomSection::OnPaintSection(FSequencerSectionPainter& Painter) const
{
	int32 LayerId = Painter.PaintSectionBackground();

	if (WaveformThumbnail.IsValid() && WaveformThumbnail->ShouldRender())
	{
		// @todo Sequencer draw multiple times if looping possibly - requires some thought about SoundCues
		FSlateDrawElement::MakeViewport(
			Painter.DrawElements,
			++LayerId,
			Painter.SectionGeometry.ToPaintGeometry(FVector2D(StoredXOffset, 0), FVector2D(StoredXSize, GetSectionHeight() + 8.f)),
			WaveformThumbnail,
			(Painter.bParentEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect) | ESlateDrawEffect::NoGamma,
			FLinearColor::White
		);
	}

	return LayerId;
}

void FAtomSection::Tick(const FGeometry& AllottedGeometry, const FGeometry& ParentGeometry, const double InCurrentTime, const float InDeltaTime)
{
	UMovieSceneAtomSection* AtomSection = Cast<UMovieSceneAtomSection>(&Section);
	UMovieSceneTrack* Track = Section.GetTypedOuter<UMovieSceneTrack>();

	USoundAtomCue* SoundAtomCue = AtomSection->GetSound();
	if (Track && SoundAtomCue) {
		const FSlateRect ParentRect = TransformRect(
			Concatenate(
				ParentGeometry.GetAccumulatedLayoutTransform(),
				AllottedGeometry.GetAccumulatedLayoutTransform().Inverse()
			),
			FSlateRect(FVector2D(0, 0), ParentGeometry.GetLocalSize())
		);

		const float LeftMostVisiblePixel = FMath::Max(ParentRect.Left, 0.f);
		const float RightMostVisiblePixel = FMath::Min(ParentRect.Right, AllottedGeometry.GetLocalSize().X);

		FFrameRate   TickResolution = AtomSection->GetTypedOuter<UMovieScene>()->GetTickResolution();
		FTimeToPixel TimeToPixel( AllottedGeometry, AtomSection->GetRange() / TickResolution, TickResolution );

		TRange<float> DrawRange = TRange<float>(
			TimeToPixel.PixelToSeconds(LeftMostVisiblePixel),
			TimeToPixel.PixelToSeconds(RightMostVisiblePixel)
			);

		// generate texture x offset and x size
		int32 XOffset = LeftMostVisiblePixel;//PixelRange.GetLowerBoundValue() - TimeToPixelConverter.TimeToPixel(SectionRange.GetLowerBoundValue());
		int32 XSize = RightMostVisiblePixel - LeftMostVisiblePixel;//PixelRange.Size<int32>();

		if (!FMath::IsNearlyEqual(DrawRange.GetLowerBoundValue(), StoredDrawRange.GetLowerBoundValue()) ||
			!FMath::IsNearlyEqual(DrawRange.GetUpperBoundValue(), StoredDrawRange.GetUpperBoundValue()) ||
			XOffset != StoredXOffset || XSize != StoredXSize || Track->GetColorTint() != StoredColor ||
			StoredSoundAtomCue != SoundAtomCue ||
			StoredSectionHeight != GetSectionHeight() ||
			StoredStartOffset != AtomSection->GetStartOffset())
		{
			float DisplayScale = XSize / DrawRange.Size<float>();

			// Use the view range if possible, as it's much more stable than using the texture size and draw range
			TSharedPtr<ISequencer> SequencerPin = Sequencer.Pin();
			if (SequencerPin.IsValid())
			{
				DisplayScale = SequencerPin->GetViewRange().Size<float>() / ParentGeometry.GetLocalSize().X;
			}

			RegenerateWaveforms(DrawRange, XOffset, XSize, Track->GetColorTint(), DisplayScale);
			StoredSoundAtomCue = SoundAtomCue;
		}
	} else {
		WaveformThumbnail.Reset();
		StoredDrawRange = TRange<float>::Empty();
		StoredSoundAtomCue.Reset();
		return;
	}
}

void FAtomSection::BeginSlipSection()
{
	UMovieSceneAtomSection* AtomSection = Cast<UMovieSceneAtomSection>(&Section);
	InitialStartOffsetDuringResize = static_cast<int32>(AtomSection->GetStartOffset());
	double StartFrame = static_cast<double>(AtomSection->HasStartFrame() ? AtomSection->GetInclusiveStartFrame().Value : 0.0);
	double TickResolution = AtomSection->GetTypedOuter<UMovieScene>()->GetTickResolution().AsDecimal();
	InitialStartTimeDuringResize = FFrameNumber(static_cast<int32>(StartFrame / TickResolution));
}

#if ENGINE_MAJOR_VERSION == 4 && ENGINE_MINOR_VERSION >= 22
void FAtomSection::SlipSection(FFrameNumber SlipTime)
{
	UMovieSceneAtomSection* AtomSection = Cast<UMovieSceneAtomSection>(&Section);

	FFrameNumber StartOffset = (SlipTime - InitialStartTimeDuringResize);
	StartOffset += InitialStartOffsetDuringResize;

	// Ensure start offset is not less than 0
	StartOffset = FMath::Max(StartOffset.Value, 0);

	AtomSection->SetStartOffset(StartOffset.Value);

	ISequencerSection::SlipSection(SlipTime);
}
#else
void FAtomSection::SlipSection(double InSlipTime)
{
	UMovieSceneAtomSection* AtomSection = Cast<UMovieSceneAtomSection>(&Section);

	double TickResolution = AtomSection->GetTypedOuter<UMovieScene>()->GetTickResolution().AsDecimal();
	FFrameNumber SlipTime = FFrameNumber(static_cast<int32>(InSlipTime / TickResolution));

	FFrameNumber StartOffset = (SlipTime - InitialStartTimeDuringResize);
	StartOffset += InitialStartOffsetDuringResize;

	// Ensure start offset is not less than 0
	StartOffset = FMath::Max(StartOffset.Value, 0);

	AtomSection->SetStartOffset(StartOffset.Value);

	ISequencerSection::SlipSection(InSlipTime);
}
#endif

void FAtomSection::RegenerateWaveforms(TRange<float> DrawRange, int32 XOffset, int32 XSize, const FColor& ColorTint, float DisplayScale)
{
	UMovieSceneAtomSection* AtomSection = Cast<UMovieSceneAtomSection>(&Section);

	StoredDrawRange = DrawRange;
	StoredXOffset = XOffset;
	StoredXSize = XSize;
	StoredColor = ColorTint;
	StoredStartOffset = AtomSection->GetStartOffset();
	StoredSectionHeight = GetSectionHeight();

	if (DrawRange.IsDegenerate() || DrawRange.IsEmpty() || AtomSection->GetSound() == NULL) {
		WaveformThumbnail.Reset();
	} else {
		WaveformThumbnail = MakeShareable(new FAtomThumbnail(Section, DrawRange, XSize, ColorTint, DisplayScale));
	}
}

/***************************************************************************
 *      関数定義
 *      Function Definition
 ***************************************************************************/

#undef LOCTEXT_NAMESPACE

/* --- end of file --- */
