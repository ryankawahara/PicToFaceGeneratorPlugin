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
#include "Widgets/Text/SMultiLineEditableText.h"
#include <filesystem>
#include "PluginRunnableThread.h"
#include "HAL/ThreadManager.h"
#include "Async/Async.h"
#include "InterchangePipelineBase.h"
#include "InterchangeSourceData.h"
#include "Nodes/InterchangeBaseNodeContainer.h"
#include "InterchangeGenericAssetsPipeline.h"
#include "InterchangeManager.h"
#include "Async/TaskGraphInterfaces.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"



static const FName FaceMeshGeneratorTabName("FaceMeshGenerator");

void ImportAssets(const FString& FileNames, const FString& DestinationFolderName);

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

	ExecuteButton = SNew(SButton)
		.Text(FText::FromString(TEXT("Generate Mesh")))
		.OnClicked(FOnClicked::CreateRaw(this, &FFaceMeshGeneratorModule::ExecuteButtonClicked));

	TSharedRef<SButton> realButton = ExecuteButton.ToSharedRef();

	FSlateColor darkBackground = FSlateColor(FLinearColor(125.0f / 255.0f, 125.0f / 255.0f, 125.0f / 255.0f, 1.0f));

	ConsoleDisplay = SNew(SMultiLineEditableTextBox);
	ConsoleDisplay->SetIsReadOnly(true);
	ConsoleDisplay->SetTextBoxBackgroundColor(darkBackground);
	TSharedRef<SMultiLineEditableTextBox> console = ConsoleDisplay.ToSharedRef();
	ImportTextureCheckbox = SNew(SCheckBox);
	TSharedRef<SCheckBox>textureCheckbox = ImportTextureCheckbox.ToSharedRef();

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[SNew(SVerticalBox)

		// Use our newly created widgets here!

		+SVerticalBox::Slot()
		.AutoHeight()
		[
			PropertyWidget.ToSharedRef()
		]		
		+ SVerticalBox::Slot()
		.Padding(FMargin(10.0f, 0.0f, 0.0f, 20.0f))
		.FillHeight(2.5)
		.MaxHeight(24)
		.HAlign(HAlign_Center)
		[
			realButton
		]
		+ SVerticalBox::Slot()
		.FillHeight(7.5)
		.HAlign(HAlign_Fill)
				[
					console
				]
		];
}

void FFaceMeshGeneratorModule::OnTaskCompleted()
{

	if (FPlatformTLS::GetCurrentThreadId() == ENamedThreads::GameThread)
	{
		// Code is running on the main thread (Game Thread)
		UE_LOG(LogTemp, Warning, TEXT("Code is running on the main thread"));
	}
	else
	{
		// Code is running on a background thread
		UE_LOG(LogTemp, Warning, TEXT("Code is running on a background thread"));
	}
}

FReply FFaceMeshGeneratorModule::ExecuteButtonClicked()
{

	if (SelectionPanelObject)
	{
		UTexture2D* SelectedMesh = SelectionPanelObject->InputFaceImage;

		FDirectoryPath OutputSavePath = SelectionPanelObject->OutputSavePath;


		if (SelectedMesh)
		{
		
			originalMeshName = SelectedMesh->AssetImportData->GetFirstFilename();

			FString imageSource = originalMeshName;

			std::filesystem::path filePath = std::filesystem::current_path();
			std::filesystem::path directory = filePath.parent_path();

			std::filesystem::path differentFile("testScript.py");

			// Append the different file's name to the directory path
			std::filesystem::path combinedPath = directory / differentFile;

			// Convert the combined path to a string and print it
			std::string combinedPathStr = combinedPath.string();
			FString testCommand = FString(combinedPathStr.c_str());
			FString pluginsPath = FPaths::ProjectPluginsDir();

			if (SelectionPanelObject->CropImage) {

				FString cropExecute = pluginsPath + FString("FaceMeshGenerator/crop.py");
				const FString FileName = FPaths::GetBaseFilename(imageSource);
				const FString extension = FPaths::GetExtension(imageSource);
				const FString cropName = FileName + "_crop" + "." + extension;

				FString cropCommand = FString((TEXT("py ") + cropExecute)) + FString(" --inputImage ") + '"' + imageSource + '"' + FString(" --outputFolderName ") + SelectionPanelObject->MeshFolderName;
				GEngine->Exec(NULL, *cropCommand);


				IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
				if (DesktopPlatform)
				{

					FString temp = DesktopPlatform->GetUserTempPath();
					// Now you can use 'temp' for further processing.
					FString tempImagePath = FPaths::Combine(temp, cropName);
					UE_LOG(LogTemp, Warning, TEXT("Temp folder is: %s"), *tempImagePath);
					imageSource = tempImagePath;

				}

			}

			FString execute = pluginsPath + FString("FaceMeshGenerator/execute.py");
			std::filesystem::path outputPath = std::filesystem::relative(*OutputSavePath.Path, directory);

			FString command = FString((TEXT("py ") + execute)) + FString(" --inputImage ") + '"' + imageSource + '"' + FString(" --outputPath ") + '"' + OutputSavePath.Path + '"';
			UE_LOG(LogTemp, Warning, TEXT("Command: %s"), *command);

			uint32 ThreadId = FPlatformTLS::GetCurrentThreadId();
			FString ThreadName = FThreadManager::Get().GetThreadName(ThreadId);
			UE_LOG(LogTemp, Warning, TEXT("Main thread running in: %s"), *ThreadName);


			PluginRunnableThread* Worker = new PluginRunnableThread(*imageSource, *pluginsPath, OutputSavePath, ExecuteButton, this);
			Worker->Start();
		}
		else
		{
			ConsoleDisplay->SetText(FText::FromString("Selected Mesh is null"));
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

void FFaceMeshGeneratorModule::OnWorkerThreadComplete() {

	uint32 ThreadId = FPlatformTLS::GetCurrentThreadId();
	FString ThreadName = FThreadManager::Get().GetThreadName(ThreadId);
	UE_LOG(LogTemp, Warning, TEXT("back on running in: %s"), *ThreadName);

	FGraphEventRef GameThreadTask = FFunctionGraphTask::CreateAndDispatchWhenReady([this]()
		{
			// This code will run on the GameThread
			UE_LOG(LogTemp, Warning, TEXT("ExecuteOnGameThread on GameThread"));
			uint32 ThreadId = FPlatformTLS::GetCurrentThreadId();
			FString ThreadName = FThreadManager::Get().GetThreadName(ThreadId);
			UE_LOG(LogTemp, Warning, TEXT("back on running in: %s"), *ThreadName);
		}, TStatId(), nullptr, ENamedThreads::GameThread);

}

void FFaceMeshGeneratorModule::UpdateUIFromMainThread(bool change)
{
	UE_LOG(LogTemp, Warning, TEXT("Button stuff"))
}


void ImportAssets(const FString& FileNames, const FString& DestinationFolderName)
{
	// Create an instance of InterchangeGenericAssetsPipeline
	//UInterchangeGenericAssetsPipeline Pipeline;
	UE_LOG(LogTemp, Warning, TEXT("Filename: %s"), *FileNames);
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