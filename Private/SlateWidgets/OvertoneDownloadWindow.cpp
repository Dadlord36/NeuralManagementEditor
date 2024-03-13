/* Copyright 2024 LeastSquares. All Rights Reserved. */

#include "SlateWidgets/OvertoneDownloadWindow.h"

#include "Settings/NeuralEditorSettings.h"
#include "SlateWidgets/AIModelsCategoryItem.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SDownloadManagerWindow::Construct(const FArguments& InArgs)
{
	InstallRemoveClickedDelegate = InArgs._InstallRemoveClicked;

	const auto OnlineModelsMenuCategories = InArgs._OnlineModelsMenuCategories;
	const auto OfflineModelsMenuCategories = InArgs._OfflineModelsMenuCategories;

	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SVerticalBox)

			// Title
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .Padding(5)
			[
				SNew(STextBlock)
            .Text(FText::FromString(TEXT("Voice Models Management")))
            .TextStyle(GetDefault<UNeuralEditorSettings>()->GetHeaderTitleTextStyle())
			]

			// Total Models Available
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .Padding(5)
			[
				SAssignNew(TotalModelsTextBlock, STextBlock)
				// .TextStyle(&HeaderTextStyle->TextBlockStyle)
				.Text(FText::FromString(TEXT("Total models available: ...")))
			]
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .Padding(5)
			[
				SNew(STextBlock)
				.Visibility_Lambda([=]
				                {
					                return OfflineModelsMenuCategories->IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible;
				                })
				.Text(FText::FromString(TEXT("Installed Models:")))
				.TextStyle(GetDefault<UNeuralEditorSettings>()->GetHeaderTextStyleRoot())
			]
			// Offline Models List View
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .Padding(5)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					SAssignNew(OfflineModelsListView, SListView<TSharedRef<const FModelsMenuCategory>>)
					.Visibility_Lambda([=]
					{
						return OfflineModelsMenuCategories->IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible;
					})
					.ItemHeight(24)
					.SelectionMode(ESelectionMode::None)
					.ListItemsSource(OfflineModelsMenuCategories)
					.OnGenerateRow(this, &SDownloadManagerWindow::GenerateMenuCategoryOnlineItem, false)
				]
			]
			+ SVerticalBox::Slot()
			  .AutoHeight()
			  .Padding(5)
			[
				SNew(STextBlock)
				.Visibility_Lambda([=]
				                {
					                return OnlineModelsMenuCategories->IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible;
				                })
				.Text(FText::FromString(TEXT("Available for Download")))
				.TextStyle(GetDefault<UNeuralEditorSettings>()->GetHeaderTextStyleRoot())
			]
			// Online Models List View
			+ SVerticalBox::Slot()
			  .FillHeight(1.0f)
			  .Padding(5)
			[
				SNew(SScrollBox)
				+ SScrollBox::Slot()
				[
					SAssignNew(OnlineModelsListView, SListView<TSharedRef<const FModelsMenuCategory>>)
					.Visibility_Lambda([=]
					{
						return OnlineModelsMenuCategories->IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible;
					})
					.ItemHeight(24)
					.SelectionMode(ESelectionMode::None)
					.ListItemsSource(OnlineModelsMenuCategories)
					.OnGenerateRow(this, &SDownloadManagerWindow::GenerateMenuCategoryOnlineItem, true)
				]
			]
		];
}

TSharedRef<ITableRow> SDownloadManagerWindow::GenerateMenuCategoryOnlineItem(TSharedRef<const FModelsMenuCategory> ModelsMenuCategory,
                                                                             const TSharedRef<STableViewBase>& OwnerTable, const bool IsOnline)
{
	return SNew(STableRow< TSharedRef<FModelsMenuCategory> >, OwnerTable)
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		  .AutoHeight()
		  .Padding(FMargin(0.f, 2.f, 3.f, 2.f))
		[
			SNew(STextBlock)
			.TextStyle(GetDefault<UNeuralEditorSettings>()->GetHeaderTextStyleSubroot())
			.Text(FText::FromString(ModelsMenuCategory->GetHeader()))
		]
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			SNew(SListView<TSharedRef<const FModelsMenuEntry>>)
            .ItemHeight(30)
            .ListItemsSource(ModelsMenuCategory->GetMenuEntriesReflectingArray())
            .OnGenerateRow_Lambda([this,IsOnline](TSharedRef<const FModelsMenuEntry> ModelsMenuEntry, const TSharedRef<STableViewBase>& TableViewBase)
			                                                   {
				                                                   return SNew(SAIModelsCategoryItem, TableViewBase, ModelsMenuEntry, IsOnline)
					                                                   .InstallRemoveClicked(
						                                                   this, &SDownloadManagerWindow::OnInstallRemoveClicked, ModelsMenuEntry);
			                                                   })
            .SelectionMode(ESelectionMode::None)
		]
	];
}

void SDownloadManagerWindow::RefreshModelsListView(const int32 TotalModelsNum) const
{
	if (OnlineModelsListView.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("ModelsListView is going to refresh!"))
		OnlineModelsListView->RequestListRefresh();
	}
	if (OfflineModelsListView.IsValid())
	{
		OfflineModelsListView->RequestListRefresh();
	}
	if (TotalModelsTextBlock.IsValid())
	{
		TotalModelsTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Total models available: %d"), TotalModelsNum)));
	}
}

void SDownloadManagerWindow::UpdateButtons(const bool bIsModelInstalled) const
{
	if (bIsModelInstalled)
	{
		if (DeleteButton.IsValid())
		{
			DeleteButton->SetVisibility(EVisibility::Visible);
		}
		if (DownloadButton.IsValid())
		{
			DownloadButton->SetVisibility(EVisibility::Collapsed);
		}
	}
	else
	{
		if (DeleteButton.IsValid())
		{
			DeleteButton->SetVisibility(EVisibility::Collapsed);
		}
		if (DownloadButton.IsValid())
		{
			DownloadButton->SetVisibility(EVisibility::Visible);
		}
	}
}

void SDownloadManagerWindow::OnInstallRemoveClicked(int32 IndexInList, TSharedRef<const FModelsMenuEntry> ModelsMenuEntry)
{
	InstallRemoveClickedDelegate.Execute(ModelsMenuEntry);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
