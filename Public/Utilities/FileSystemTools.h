// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetToolsModule.h"
#include "Editor.h"
#include "IAssetTools.h"
#include "Engine/AssetManager.h"
#include "Subsystems/EditorAssetSubsystem.h"

/**
 * 
 */
namespace FileSystemTools
{
	template <class T>
	struct TIsDataAsset : TEnableIf<TIsDerivedFrom<T, UDataAsset>::IsDerived>::Type
	{
	};

	static void DeleteAssetIfExistAt(const FString& Path)
	{
		UEditorAssetSubsystem* EditorAssetSubsystem = GEditor->GetEditorSubsystem<UEditorAssetSubsystem>();
		if (EditorAssetSubsystem->DoesAssetExist(Path))
		{
			checkf(EditorAssetSubsystem->DeleteAsset(Path), TEXT("File was not deleted for some reason"));
		}
	}

	static void DeleteAssetIfExistAt(const FSoftObjectPath& SoftObjectPath)
	{
		DeleteAssetIfExistAt(SoftObjectPath.GetAssetPathString());
	}

	template <class T, class = TIsDataAsset<T>>
	static TObjectPtr<T> LoadExistingAssetAt(const FString& FilePath)
	{
		auto& StreamableManager = UAssetManager::Get().GetStreamableManager();
		const FSoftObjectPath AssetObjectPath(FilePath);
		auto LoadedModel = StreamableManager.LoadSynchronous<T>(AssetObjectPath);
		checkf(LoadedModel, TEXT("For some reason loading of the model was unsuccessful"))
		return LoadedModel;
	}

	static TObjectPtr<UDataAsset> LoadAssetIfExistsAt(const FString& Path)
	{
		UEditorAssetSubsystem* EditorAssetSubsystem = GEditor->GetEditorSubsystem<UEditorAssetSubsystem>();
		if (EditorAssetSubsystem->DoesAssetExist(Path))
		{
			return Cast<UDataAsset>(EditorAssetSubsystem->LoadAsset(Path));
		}
		return nullptr;
	}

	static void SaveAssetAt(const FString& Path)
	{
		UEditorAssetSubsystem* EditorAssetSubsystem = GEditor->GetEditorSubsystem<UEditorAssetSubsystem>();
		EditorAssetSubsystem->SaveAsset(Path);
	}

	template <class T, class = TIsDataAsset<T>>
	static TObjectPtr<T> CreateOrOverrideAssetForChecked(const FString& FileName, const FString& Directory)
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

		const FString AssetPath = FPaths::Combine(Directory, FileName);
		DeleteAssetIfExistAt(AssetPath);

		const auto Asset = AssetTools.CreateAsset(FileName, Directory, T::StaticClass(), nullptr);
		checkf(Asset, TEXT("Asset was not created for some reason"))
		// SaveAssetAt(AssetPath);

		return Cast<T>(Asset);
	}

	template <class T, class = TIsDataAsset<T>>
	static TObjectPtr<T> CreateOrLodeAssetForChecked(const FString& FileName, const FString& Directory)
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

		const FString AssetPath = FPaths::Combine(Directory, FileName);

		TObjectPtr<T> Asset = Cast<T>(LoadAssetIfExistsAt(AssetPath));
		if (Asset)
		{
			return Asset;
		}

		Asset = Cast<T>(AssetTools.CreateAsset(FileName, Directory, T::StaticClass(), nullptr));
		checkf(Asset, TEXT("Asset was not created for some reason"))
		// SaveAssetAt(AssetPath);

		return Asset;
	}
}
