  // Copyright Epic Games, Inc. All Rights Reserved.

#include "FaceMeshGenerator.h"
#include "FaceMeshGeneratorStyle.h"
#include "FaceMeshGeneratorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "EditorFramework/AssetImportData.h"
#include "Engine/Engine.h"
#include <filesystem>


static const FName FaceMeshGeneratorTabName("FaceMeshGenerator");

#define LOCTEXT_NAMESPACE "FFaceMeshGeneratorModule"

void FFaceMeshGeneratorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FFaceMeshGeneratorStyle::Initialize();
	FFaceMeshGeneratorStyle::ReloadTextures();

	FFaceMeshGeneratorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FFaceMeshGeneratorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FFaceMeshGeneratorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FFaceMeshGeneratorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FaceMeshGeneratorTabName, FOnSpawnTab::CreateRaw(this, &FFaceMeshGeneratorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FFaceMeshGeneratorTabTitle", "FaceMeshGenerator"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FFaceMeshGeneratorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FFaceMeshGeneratorStyle::Shutdown();

	FFaceMeshGeneratorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FaceMeshGeneratorTabName);
}

TSharedRef<SDockTab> FFaceMeshGeneratorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FFaceMeshGeneratorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("FaceMeshGenerator.cpp"))
		);

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;

	PropertyWidget = PropertyModule.CreateDetailView(Args);

	SelectionPanelObject = GetMutableDefault<USelectionPanel>();
	PropertyWidget->SetObject(SelectionPanelObject);



	TSharedRef<SButton> ExecuteButton = SNew(SButton)
		.Text(FText::FromString(TEXT("Generate Mesh")))
		.OnClicked(FOnClicked::CreateRaw(this, &FFaceMeshGeneratorModule::ExecuteButtonClicked));

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[			SNew(SVerticalBox)

			// Use our newly created widgets here!

				+ SVerticalBox::Slot()
				.FillHeight(15.0)
				[
					PropertyWidget.ToSharedRef()
				]
				+ SVerticalBox::Slot()
				.FillHeight(2.5)
				.HAlign(HAlign_Center)
				[
					ExecuteButton
				]
		];
}

FReply FFaceMeshGeneratorModule::ExecuteButtonClicked()
{

	if (SelectionPanelObject)
	{
		UTexture2D* SelectedMesh = SelectionPanelObject->InputFaceImage;

		FDirectoryPath OutputSavePath = SelectionPanelObject->OutputSavePath;

		if (SelectedMesh)
		{
			//FString MeshName = SelectedMesh->GetPathName();
			FString MeshName = SelectedMesh->AssetImportData->GetFirstFilename();
			UE_LOG(LogTemp, Warning, TEXT("Selected Mesh Name: %s"), *MeshName);
			std::filesystem::path filePath = std::filesystem::current_path();
			std::filesystem::path directory = filePath.parent_path();

			std::filesystem::path differentFile("testScript.py");

			// Append the different file's name to the directory path
			std::filesystem::path combinedPath = directory / differentFile;

			// Convert the combined path to a string and print it
			std::string combinedPathStr = combinedPath.string();
			FString testCommand = FString(combinedPathStr.c_str());
			FString pluginsPath = FPaths::ProjectPluginsDir();
			FString execute = pluginsPath + FString("FaceMeshGenerator/execute.py");
			std::filesystem::path outputPath = std::filesystem::relative(*OutputSavePath.Path, directory);
			UE_LOG(LogTemp, Warning, TEXT("Output: %s"), outputPath.c_str());



			UE_LOG(LogTemp, Warning, TEXT("Execute: %s"), *execute);
			UE_LOG(LogTemp, Warning, TEXT("Plugin Path: %s"), *pluginsPath);



			FString command = FString((TEXT("py ") + execute)) + FString(" --inputImage ") + '"' + MeshName + '"' + FString(" --outputPath ") + '"' + OutputSavePath.Path + '"';
			UE_LOG(LogTemp, Warning, TEXT("Command: %s"), *command);


			GEngine->Exec(NULL, *command);



		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Selected Mesh is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CustomSettings is null"));
	}



	return FReply::Handled();
}

void FFaceMeshGeneratorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FaceMeshGeneratorTabName);
}

void FFaceMeshGeneratorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FFaceMeshGeneratorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FFaceMeshGeneratorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFaceMeshGeneratorModule, FaceMeshGenerator)