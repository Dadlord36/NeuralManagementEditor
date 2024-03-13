// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structs/DownloadManagerViewStructs.h"
#include "Widgets/SCompoundWidget.h"

DECLARE_DELEGATE_OneParam(FItemIndexDelegate, int32 /*IndexInList*/)

/**
 * 
 */
class NEURALMANAGEMENTEDITOR_API SAIModelsCategoryItem : public STableRow<TSharedPtr<FModelsMenuEntry>>
{
public:
	SLATE_BEGIN_ARGS(SAIModelsCategoryItem)
		{
		}
	SLATE_EVENT(FItemIndexDelegate, InstallRemoveClicked)
	SLATE_END_ARGS()

	
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const TSharedRef<STableViewBase>& InOwnerTableView, TSharedRef<const FModelsMenuEntry> MenuEntry,
	               const bool IsOnline);

private:
	FReply OnInstallRemoveClicked();

private:
	FItemIndexDelegate ItemIndexDelegate;
};
