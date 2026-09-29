// By hzFishy - 2026 - Do whatever you want with it.


#include "PropertyCustomization/UGAEventNameCustomization.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "Core/UGACoreSettings.h"
#include "Types/UGAEventName.h"


FUGAEventNameCustomization::FUGAEventNameCustomization():
	Settings(nullptr), 
	EventNamePtr(nullptr)
{}

TSharedRef<IPropertyTypeCustomization> FUGAEventNameCustomization::MakeInstance()
{
	return MakeShared<FUGAEventNameCustomization>();
}

void FUGAEventNameCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	HeaderRow
		.NameContent()
		[
			PropertyHandle->CreatePropertyNameWidget()
		];
}

void FUGAEventNameCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	Settings = GetDefault<UUGACoreSettings>();
	
	void* ValuePtr;
	PropertyHandle->GetValueData(ValuePtr);
	EventNamePtr = static_cast<FUGAEventName*>(ValuePtr);
	
	Options.Reserve(Settings->EventNames.Num());
	int32 SelectedIndex = -1;
	for (int32 i = 0; i < Settings->EventNames.Num(); ++i)
	{
		const FName EventName = Settings->EventNames[i];
		
		if (!EventName.IsValid()) { continue; }
		
		Options.Emplace(EventName);
		
		if (EventNamePtr->EventName == EventName)
		{
			SelectedIndex = i;
		}
	}
	
	if (SelectedIndex >= 0)
	{
		CurrentSelection = Options[SelectedIndex];
	}
	
	ChildBuilder.AddCustomRow(INVTEXT("")).NameContent()
		[
			PropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			SAssignNew(DropDownWidget, SComboBox<FName>)
				.OptionsSource(&Options)
				.InitiallySelectedItem(CurrentSelection)
				.ContentPadding(FMargin(4, 2))
				.MaxListHeight(450)
				.HasDownArrow(true)
				.OnGenerateWidget_Raw(this, &FUGAEventNameCustomization::HandleGenerateItemWidget)
				.OnSelectionChanged_Raw(this, &FUGAEventNameCustomization::HandleSelectionChanged)
				[
					SAssignNew(ComboBoxContent, SBox)
				]
		];
	
	RefreshContent();
}

TSharedRef<SWidget> FUGAEventNameCustomization::HandleGenerateItemWidget(FName Name)
{
	return SNew(STextBlock)
		.Text(FText::FromName(Name));
}

void FUGAEventNameCustomization::HandleSelectionChanged(FName Name, ESelectInfo::Type Arg)
{
	*EventNamePtr = FUGAEventName(Name);
	CurrentSelection = Name;
	RefreshContent();
}

void FUGAEventNameCustomization::RefreshContent()
{
	if (ComboBoxContent.IsValid())
	{
		auto Widget = HandleGenerateItemWidget(CurrentSelection);
		ComboBoxContent->SetContent(Widget);
	}
}
