// By hzFishy - 2026 - Do whatever you want with it.

#include "UnrealGoogleAnalyticsEditor.h"
#include "PropertyCustomization/UGAAttributeKeyCustomization.h"
#include "PropertyCustomization/UGAEventNameCustomization.h"
#include "Types/UGAAttributeKey.h"
#include "Types/UGAEventName.h"

#define LOCTEXT_NAMESPACE "FUnrealGoogleAnalyticsEditorModule"

void FUnrealGoogleAnalyticsEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomPropertyTypeLayout(
		FUGAEventName::StaticStruct()->GetFName(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FUGAEventNameCustomization::MakeInstance)
	);
	
	PropertyModule.RegisterCustomPropertyTypeLayout(
		FUGAAttributeKey::StaticStruct()->GetFName(),
		FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FUGAAttributeKeyCustomization::MakeInstance)
	);
}

void FUnrealGoogleAnalyticsEditorModule::ShutdownModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.UnregisterCustomPropertyTypeLayout(FUGAEventName::StaticStruct()->GetFName());
	PropertyModule.UnregisterCustomPropertyTypeLayout(FUGAAttributeKey::StaticStruct()->GetFName());
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FUnrealGoogleAnalyticsEditorModule, UnrealGoogleAnalyticsEditor)