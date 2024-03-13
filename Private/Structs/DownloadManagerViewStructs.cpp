/* Copyright 2024 LeastSquares. All Rights Reserved. */


#include "Structs/DownloadManagerViewStructs.h"


FModelsMenuEntry::FModelsMenuEntry(const TObjectPtr<const UDownloadTask>& ModelDownloadTask, const FAIModelIdentity& Identity,
                                   const FResourcesLinks& ResourcesLinks): ModelDownloadTask(ModelDownloadTask), Identity(Identity),
                                                                           ResourcesLinks(ResourcesLinks)
{
}

FString FModelsMenuEntry::ToString() const
{
	return FString::Printf(TEXT("ModelName: %s, ModelRelativeSize: %s"), *Identity.ModelName, *Identity.Quality);
}

FModelsMenuCategory::FModelsMenuCategory(FString&& Header, TArray<TSharedRef<const FModelsMenuEntry>>&& InMenuEntries): Header(MoveTemp(Header)),
	MenuEntries(MoveTemp(InMenuEntries))
{
}

FString FModelsMenuCategory::ToString() const
{
	FString OutString = FString::Printf(TEXT("Header: %s, MenuEntries:\n"), *Header);
	for (const auto& Entry : MenuEntries)
	{
		OutString += Entry->ToString() + TEXT("\n");
	}
	return OutString;
}
