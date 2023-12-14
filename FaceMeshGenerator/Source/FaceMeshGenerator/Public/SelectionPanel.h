// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectionPanel.generated.h"


UCLASS(BlueprintType, AutoCollapseCategories = ("Optional"), config = EditorPerProjectUserSettings)
class FACEMESHGENERATOR_API USelectionPanel : public UObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	USelectionPanel()
	{
		// Initialize the default values for the properties
		InputFaceImage = nullptr;

		// Set FolderPathSelector to the project directory
		FString ProjectDirectory = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
		OutputSavePath.Path = ProjectDirectory+"/";

		ImportTexture = false;
		MeshFolderName = "FaceMesh";
		CropImage = false;

		//FString pluginsPath = FPaths::ProjectPluginsDir();

		//FString genericPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(pluginsPath, FString("FaceMeshGenerator")));

		//FlameModelPath.FilePath = genericPath;

	}
	UPROPERTY(EditAnywhere, meta=(Category = "Settings"))
	UTexture2D* InputFaceImage;

	UPROPERTY(EditAnywhere, Category = "Settings")
	FDirectoryPath OutputSavePath;

	UPROPERTY(EditAnywhere, Category = "Optional")
	bool CropImage;

	UPROPERTY(EditAnywhere, Category = "Optional", meta=(FilePathFilter = "pkl"))
	FFilePath FlameModelPath;

	UPROPERTY(EditAnywhere, Category = "Optional")
	bool ImportTexture;

	UPROPERTY(EditAnywhere, Category = "Optional")
	FString MeshFolderName;


};
