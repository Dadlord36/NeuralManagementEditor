/* Copyright 2024 LeastSquares. All Rights Reserved. */

#pragma once

#include "CoreMinimal.h"
#include "Structs/VoiceModelInformation.h"


class UDownloadTask;

struct NEURALMANAGEMENTEDITOR_API FModelsMenuEntry : TSharedFromThis<FModelsMenuEntry>
{
	const TObjectPtr<const UDownloadTask> ModelDownloadTask;
	const FAIModelIdentity Identity;
	const FResourcesLinks ResourcesLinks;

	FModelsMenuEntry(const TObjectPtr<const UDownloadTask>& ModelDownloadTask, const FAIModelIdentity& Identity, const FResourcesLinks& ResourcesLinks);

	FString ToString() const;
};

struct NEURALMANAGEMENTEDITOR_API FModelsMenuCategory : TSharedFromThis<FModelsMenuCategory>
{
	FModelsMenuCategory(FString&& Header, TArray<TSharedRef<const FModelsMenuEntry>>&& InMenuEntries);

	const FString& GetHeader() const
	{
		return Header;
	}

	const TArray<TSharedRef<const FModelsMenuEntry>>* GetMenuEntriesReflectingArray() const
	{
		return &MenuEntries;
	}

	FString ToString() const;

private:
	FString Header;
	TArray<TSharedRef<const FModelsMenuEntry>> MenuEntries;
};
