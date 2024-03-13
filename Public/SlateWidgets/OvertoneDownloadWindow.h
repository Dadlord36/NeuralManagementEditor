/* Copyright 2024 LeastSquares. All Rights Reserved. */

#pragma once

#include "Widgets/SCompoundWidget.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Structs/DownloadManagerViewStructs.h"


class UOvertoneModelsManagementEditorSubsystem;

DECLARE_DELEGATE_OneParam(FModelIdentityDelegate, TSharedRef<const FModelsMenuEntry>)


class NEURALMANAGEMENTEDITOR_API SDownloadManagerWindow final : public SCompoundWidget
{
	TSharedPtr<STextBlock> TotalModelsTextBlock;
	TSharedPtr<SButton> DownloadButton;
	TSharedPtr<SButton> DeleteButton;
	TSharedPtr<SListView<TSharedRef<const FModelsMenuCategory>>> OnlineModelsListView;
	TSharedPtr<SListView<TSharedRef<const FModelsMenuCategory>>> OfflineModelsListView;

	bool bIsDownloading = true;
	float DownloadProgress = 0.0f;

public:
	SLATE_BEGIN_ARGS(SDownloadManagerWindow)
		{
		}

		SLATE_ARGUMENT(const TArray<TSharedRef<const FModelsMenuCategory>>*, OnlineModelsMenuCategories)
		SLATE_ARGUMENT(const TArray<TSharedRef<const FModelsMenuCategory>>*, OfflineModelsMenuCategories)

		SLATE_EVENT(FModelIdentityDelegate, InstallRemoveClicked)

	SLATE_END_ARGS()


	void Construct(const FArguments& InArgs);
	void RefreshModelsListView(const int32 TotalModelsNum) const;

private:
	TSharedRef<ITableRow> GenerateMenuCategoryOnlineItem(TSharedRef<const FModelsMenuCategory> ModelsMenuCategory,
	                                                     const TSharedRef<STableViewBase>& OwnerTable, bool IsOnline);
	void UpdateButtons(bool bIsModelInstalled) const;
	void OnInstallRemoveClicked(int32 IndexInList, TSharedRef<const FModelsMenuEntry> ModelsMenuEntry);

private:
	FDelegateHandle OnAvailableModelsNumberChangedHandle;
	FModelIdentityDelegate InstallRemoveClickedDelegate;
};
