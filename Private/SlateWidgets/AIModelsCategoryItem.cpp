// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateWidgets/AIModelsCategoryItem.h"

#include "SlateOptMacros.h"
#include "Neural/WebOperator/Public/Managers/Tasks/DownloadTask.h"
#include "Settings/NeuralEditorSettings.h"

#include "Widgets/Notifications/SProgressBar.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SAIModelsCategoryItem::Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView,
                                      TSharedRef<const FModelsMenuEntry> MenuEntry, const bool IsOnline)
{
	auto CorrespondingTask = MenuEntry->ModelDownloadTask;
	const FAIModelIdentity& Identity = MenuEntry->Identity;
	ItemIndexDelegate = InArgs._InstallRemoveClicked;

	STableRow<TSharedPtr<FModelsMenuEntry>>::Construct(
		STableRow::FArguments()

		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .FillWidth(0.3f)
			  .Padding(5)
			[
				SNew(STextBlock)
		.TextStyle(GetDefault<UNeuralEditorSettings>()->GetMenuEntryNameTextStyle())
		.Text(FText::FromString(Identity.ModelName))
			]
			+ SHorizontalBox::Slot()
			  .FillWidth(0.3f)
			  .Padding(5)
			[
				SNew(STextBlock)
		.TextStyle(GetDefault<UNeuralEditorSettings>()->GetMenuEntryTextStyleSize())
		.Text(FText::FromString(Identity.Quality))
			]
			+ SHorizontalBox::Slot()
			  .FillWidth(0.2f)
			  .Padding(5)
			[
				SNew(SButton)

		.Visibility_Lambda([CorrespondingTask]
				             {
					             return CorrespondingTask->IsDownloading() ? EVisibility::Collapsed : EVisibility::Visible;
				             })
		.ButtonColorAndOpacity(IsOnline ? FLinearColor::Green : FLinearColor::Red)
		.OnClicked(this, &SAIModelsCategoryItem::OnInstallRemoveClicked)
				[
					SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
			.Text(IsOnline ? FText::FromString("Install") : FText::FromString("Remove"))
			.TextStyle(GetDefault<UNeuralEditorSettings>()->GetMenuEntryTextStyleFunction())
					]]
			]
			+ SHorizontalBox::Slot()
			  .FillWidth(0.2f)
			  .Padding(5)
			[
				SNew(SProgressBar)
		.Percent(0.0)
		.Percent_Lambda([CorrespondingTask]
				                  {
					                  return CorrespondingTask->GetProgressValue();
				                  })
		.Visibility_Lambda([CorrespondingTask]
				                  {
					                  return CorrespondingTask->IsDownloading() ? EVisibility::Visible : EVisibility::Collapsed;
				                  })
			]
		], InOwnerTableView);
}

FReply SAIModelsCategoryItem::OnInstallRemoveClicked()
{
	ItemIndexDelegate.Execute(GetIndexInList());
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
