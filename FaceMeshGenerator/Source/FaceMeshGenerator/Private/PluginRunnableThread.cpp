// Fill out your copyright notice in the Description page of Project Settings.


#include "PluginRunnableThread.h"
#include "HAL/ThreadManager.h"
#include "Engine/Engine.h"
#include "Async/Async.h"
#include "InterchangePipelineBase.h"
#include "InterchangeSourceData.h"
#include "Nodes/InterchangeBaseNodeContainer.h"
#include "InterchangeGenericAssetsPipeline.h"
#include "InterchangeManager.h"
#include "InterchangeGenericMaterialPipeline.h"
#include "InterchangeGenericTexturePipeline.h"
#include "InterchangeGenericMeshPipeline.h"

#pragma region Main Thread Code

PluginRunnableThread::PluginRunnableThread(const FString& InMeshName, const FString& InPluginsPath, const FDirectoryPath& InOutputPath, TSharedPtr<SButton> ExecuteButton, FFaceMeshGeneratorModule* InOwner)
	: MeshName(InMeshName), pluginsPath(InPluginsPath), outputPath(InOutputPath), button(ExecuteButton), owner(InOwner)
{

	FString InExecute = InPluginsPath + FString("FaceMeshGenerator/execute.py");
	FString cropExecute = InPluginsPath + FString("FaceMeshGenerator/crop.py");
	CommandToExecute = FString((TEXT("py ") + InExecute)) + FString(" --inputImage ") + '"' + InMeshName + '"' + FString(" --outputPath ") + '"' + InOutputPath.Path + '"';
	cropCommand = FString((TEXT("py ") + cropExecute)) + FString(" --inputImage ") + '"' + InMeshName + '"' + FString(" --outputFolderName ") + owner->SelectionPanelObject->MeshFolderName;
	bShouldStartThread = false;
	Thread = FRunnableThread::Create(this, TEXT("Creating thread"));

}

PluginRunnableThread::~PluginRunnableThread()
{
	// Signal the thread to stop gracefully
	bRunThread = false;

	if (Thread)
	{
		Thread->WaitForCompletion();
		delete Thread;
	}
}

#pragma endregion

bool PluginRunnableThread::Init()
{
		return true;
}

uint32 PluginRunnableThread::Start() {
	bShouldStartThread = true;

	return 0;
}

uint32 PluginRunnableThread::Run()
{
	while (!bShouldStartThread)
	{
		// Sleep or yield to avoid busy-waiting
		FPlatformProcess::Sleep(0.1f);
	}

	TSharedPtr<SButton> buttonPtr = button;
	FFunctionGraphTask::CreateAndDispatchWhenReady([buttonPtr]()
		{
			buttonPtr->SetEnabled(false);
		}, TStatId(), nullptr, ENamedThreads::GameThread);

	ClearWidgetConsole();
	WriteToWidgetConsole(FString(TEXT("Running... This can take a few minutes...")));

	FString pkl = FPaths::ConvertRelativePathToFull(owner->SelectionPanelObject->FlameModelPath.FilePath);

	if (pkl != "") {
		CommandToExecute = CommandToExecute + FString(" --custom_flame_model ") + '"' + pkl + '"';
		UE_LOG(LogTemp, Warning, TEXT("Model is %s"), *pkl);
	}
	UE_LOG(LogTemp, Warning, TEXT("My custom thread is running with command: %s"), *CommandToExecute);

	GEngine->Exec(NULL, *CommandToExecute);

	uint32 ThreadId = FPlatformTLS::GetCurrentThreadId();
	FString ThreadName = FThreadManager::Get().GetThreadName(ThreadId);
	UE_LOG(LogTemp, Warning, TEXT("Thread running in: %s"), *ThreadName);

	AsyncTask(ENamedThreads::GameThread, [this]()
		{

			uint32 stopThreadId = FPlatformTLS::GetCurrentThreadId();
			FString ThreadName = FThreadManager::Get().GetThreadName(stopThreadId);
			UE_LOG(LogTemp, Warning, TEXT("Stop running : %s"), *ThreadName);

			WriteToWidgetConsole(FString(TEXT("Importing...")));

			UInterchangeGenericAssetsPipeline* Pipeline = NewObject<UInterchangeGenericAssetsPipeline>();
			Pipeline->ImportOffsetRotation = FRotator(0, 0, 90);
			Pipeline->ImportOffsetTranslation = FVector(0, 0, 0);
			Pipeline->ImportOffsetUniformScale = 400.0f;
			Pipeline->bUseSourceNameForAsset = true;
			
			Pipeline->MaterialPipeline->TexturePipeline->bImportTextures = owner->SelectionPanelObject->ImportTexture;
			Pipeline->MaterialPipeline->bImportMaterials = owner->SelectionPanelObject->ImportTexture;

			FString DestinationFolderName = owner->SelectionPanelObject->MeshFolderName;

			const FString FileName = FPaths::GetBaseFilename(MeshName);

			FString DestinationFolderPath = FString(TEXT("/Game/")) + DestinationFolderName + FString(TEXT("/")) + FileName;

			//const FString FileName = FPaths::GetBaseFilename(MeshName);
			UE_LOG(LogTemp, Warning, TEXT("Mesh name: %s"), *FileName);

			FString OutputBaseFolder = FPaths::Combine(outputPath.Path, FileName);

			FString ObjPath = FPaths::Combine(OutputBaseFolder, FileName + TEXT(".obj"));
			UE_LOG(LogTemp, Warning, TEXT("Mesh is at: %s"), *ObjPath);
			UE_LOG(LogTemp, Warning, TEXT("Gonna put it at : %s"), *DestinationFolderPath);


			UInterchangeSourceData* SourceData = UInterchangeManager::CreateSourceData(ObjPath);

			// Create import asset parameters
			FImportAssetParameters ImportAssetParameters;
			ImportAssetParameters.OverridePipelines.Add(Pipeline);

			UInterchangeManager* InterchangeManager = UInterchangeManager::GetInterchangeManagerScripted();

			InterchangeManager->ImportSceneAsync(DestinationFolderPath, SourceData, ImportAssetParameters);

			TSharedPtr<SButton> buttonPtr = button;
			FFunctionGraphTask::CreateAndDispatchWhenReady([buttonPtr]()
				{
					// This code is on game thread
					buttonPtr->SetEnabled(true);

				}, TStatId(), nullptr, ENamedThreads::GameThread);
			
			WriteToWidgetConsole(FString(TEXT("Import Sucessful!")));
		});
	return 0;
}

void PluginRunnableThread::WriteToWidgetConsole(const FString& text) {

	TSharedPtr<SMultiLineEditableTextBox> consolePtr = owner->ConsoleDisplay;
	FFunctionGraphTask::CreateAndDispatchWhenReady([consolePtr, text]()
		{
			FString current = consolePtr->GetText().ToString();
			if (current == "") {
				consolePtr->SetText(FText::FromString(text));
			}
			else {
				current += ("\n" + text);
				consolePtr->SetText(FText::FromString(current));
			}
		}, TStatId(), nullptr, ENamedThreads::GameThread);

}

void PluginRunnableThread::ClearWidgetConsole() {

	TSharedPtr<SMultiLineEditableTextBox> consolePtr = owner->ConsoleDisplay;
	FFunctionGraphTask::CreateAndDispatchWhenReady([consolePtr]()
		{

			consolePtr->SetText(FText::FromString(""));

		}, TStatId(), nullptr, ENamedThreads::GameThread);

}

void PluginRunnableThread::Stop()
{
	// Clean up memory usage here, and make sure the Run() function stops soon
	// The main thread will be stopped until this finishes!

	bRunThread = false;
	uint32 stopThreadId = FPlatformTLS::GetCurrentThreadId();
	FString ThreadName = FThreadManager::Get().GetThreadName(stopThreadId);
	UE_LOG(LogTemp, Warning, TEXT("Stop running : %s"), *ThreadName);
}

bool PluginRunnableThread::IsDone() const
{
	return bIsThreadComplete;
}
