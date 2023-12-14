// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FaceMeshGenerator/Public/SelectionPanel.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSelectionPanel() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FDirectoryPath();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FFilePath();
	ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
	FACEMESHGENERATOR_API UClass* Z_Construct_UClass_USelectionPanel();
	FACEMESHGENERATOR_API UClass* Z_Construct_UClass_USelectionPanel_NoRegister();
	UPackage* Z_Construct_UPackage__Script_FaceMeshGenerator();
// End Cross Module References
	void USelectionPanel::StaticRegisterNativesUSelectionPanel()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(USelectionPanel);
	UClass* Z_Construct_UClass_USelectionPanel_NoRegister()
	{
		return USelectionPanel::StaticClass();
	}
	struct Z_Construct_UClass_USelectionPanel_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InputFaceImage_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_InputFaceImage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OutputSavePath_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_OutputSavePath;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_CropImage_MetaData[];
#endif
		static void NewProp_CropImage_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_CropImage;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_FlameModelPath_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_FlameModelPath;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ImportTexture_MetaData[];
#endif
		static void NewProp_ImportTexture_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ImportTexture;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_MeshFolderName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_MeshFolderName;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_USelectionPanel_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_FaceMeshGenerator,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectionPanel_Statics::Class_MetaDataParams[] = {
		{ "AutoCollapseCategories", "Optional" },
		{ "BlueprintType", "true" },
		{ "IncludePath", "SelectionPanel.h" },
		{ "ModuleRelativePath", "Public/SelectionPanel.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectionPanel_Statics::NewProp_InputFaceImage_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/SelectionPanel.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_USelectionPanel_Statics::NewProp_InputFaceImage = { "InputFaceImage", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(USelectionPanel, InputFaceImage), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(Z_Construct_UClass_USelectionPanel_Statics::NewProp_InputFaceImage_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USelectionPanel_Statics::NewProp_InputFaceImage_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectionPanel_Statics::NewProp_OutputSavePath_MetaData[] = {
		{ "Category", "Settings" },
		{ "ModuleRelativePath", "Public/SelectionPanel.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USelectionPanel_Statics::NewProp_OutputSavePath = { "OutputSavePath", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(USelectionPanel, OutputSavePath), Z_Construct_UScriptStruct_FDirectoryPath, METADATA_PARAMS(Z_Construct_UClass_USelectionPanel_Statics::NewProp_OutputSavePath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USelectionPanel_Statics::NewProp_OutputSavePath_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectionPanel_Statics::NewProp_CropImage_MetaData[] = {
		{ "Category", "Optional" },
		{ "ModuleRelativePath", "Public/SelectionPanel.h" },
	};
#endif
	void Z_Construct_UClass_USelectionPanel_Statics::NewProp_CropImage_SetBit(void* Obj)
	{
		((USelectionPanel*)Obj)->CropImage = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USelectionPanel_Statics::NewProp_CropImage = { "CropImage", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(USelectionPanel), &Z_Construct_UClass_USelectionPanel_Statics::NewProp_CropImage_SetBit, METADATA_PARAMS(Z_Construct_UClass_USelectionPanel_Statics::NewProp_CropImage_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USelectionPanel_Statics::NewProp_CropImage_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectionPanel_Statics::NewProp_FlameModelPath_MetaData[] = {
		{ "Category", "Optional" },
		{ "FilePathFilter", "pkl" },
		{ "ModuleRelativePath", "Public/SelectionPanel.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_USelectionPanel_Statics::NewProp_FlameModelPath = { "FlameModelPath", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(USelectionPanel, FlameModelPath), Z_Construct_UScriptStruct_FFilePath, METADATA_PARAMS(Z_Construct_UClass_USelectionPanel_Statics::NewProp_FlameModelPath_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USelectionPanel_Statics::NewProp_FlameModelPath_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectionPanel_Statics::NewProp_ImportTexture_MetaData[] = {
		{ "Category", "Optional" },
		{ "ModuleRelativePath", "Public/SelectionPanel.h" },
	};
#endif
	void Z_Construct_UClass_USelectionPanel_Statics::NewProp_ImportTexture_SetBit(void* Obj)
	{
		((USelectionPanel*)Obj)->ImportTexture = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_USelectionPanel_Statics::NewProp_ImportTexture = { "ImportTexture", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(USelectionPanel), &Z_Construct_UClass_USelectionPanel_Statics::NewProp_ImportTexture_SetBit, METADATA_PARAMS(Z_Construct_UClass_USelectionPanel_Statics::NewProp_ImportTexture_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USelectionPanel_Statics::NewProp_ImportTexture_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_USelectionPanel_Statics::NewProp_MeshFolderName_MetaData[] = {
		{ "Category", "Optional" },
		{ "ModuleRelativePath", "Public/SelectionPanel.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_USelectionPanel_Statics::NewProp_MeshFolderName = { "MeshFolderName", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(USelectionPanel, MeshFolderName), METADATA_PARAMS(Z_Construct_UClass_USelectionPanel_Statics::NewProp_MeshFolderName_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_USelectionPanel_Statics::NewProp_MeshFolderName_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USelectionPanel_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectionPanel_Statics::NewProp_InputFaceImage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectionPanel_Statics::NewProp_OutputSavePath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectionPanel_Statics::NewProp_CropImage,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectionPanel_Statics::NewProp_FlameModelPath,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectionPanel_Statics::NewProp_ImportTexture,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USelectionPanel_Statics::NewProp_MeshFolderName,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_USelectionPanel_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USelectionPanel>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_USelectionPanel_Statics::ClassParams = {
		&USelectionPanel::StaticClass,
		"EditorPerProjectUserSettings",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_USelectionPanel_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_USelectionPanel_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_USelectionPanel_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_USelectionPanel_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_USelectionPanel()
	{
		if (!Z_Registration_Info_UClass_USelectionPanel.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USelectionPanel.OuterSingleton, Z_Construct_UClass_USelectionPanel_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_USelectionPanel.OuterSingleton;
	}
	template<> FACEMESHGENERATOR_API UClass* StaticClass<USelectionPanel>()
	{
		return USelectionPanel::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(USelectionPanel);
	USelectionPanel::~USelectionPanel() {}
	struct Z_CompiledInDeferFile_FID_Users_ryryk_Documents_UnrealProjects_SeniorProjectDemo_Plugins_FaceMeshGenerator_Source_FaceMeshGenerator_Public_SelectionPanel_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ryryk_Documents_UnrealProjects_SeniorProjectDemo_Plugins_FaceMeshGenerator_Source_FaceMeshGenerator_Public_SelectionPanel_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_USelectionPanel, USelectionPanel::StaticClass, TEXT("USelectionPanel"), &Z_Registration_Info_UClass_USelectionPanel, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USelectionPanel), 1413523283U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ryryk_Documents_UnrealProjects_SeniorProjectDemo_Plugins_FaceMeshGenerator_Source_FaceMeshGenerator_Public_SelectionPanel_h_1089254526(TEXT("/Script/FaceMeshGenerator"),
		Z_CompiledInDeferFile_FID_Users_ryryk_Documents_UnrealProjects_SeniorProjectDemo_Plugins_FaceMeshGenerator_Source_FaceMeshGenerator_Public_SelectionPanel_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ryryk_Documents_UnrealProjects_SeniorProjectDemo_Plugins_FaceMeshGenerator_Source_FaceMeshGenerator_Public_SelectionPanel_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
