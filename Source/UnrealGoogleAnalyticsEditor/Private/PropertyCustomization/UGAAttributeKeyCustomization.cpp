// By hzFishy - 2026 - Do whatever you want with it.


#include "PropertyCustomization/UGAAttributeKeyCustomization.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "Core/UGACoreSettings.h"
#include "Types/UGAAttributeKey.h"


FUGAAttributeKeyCustomization::FUGAAttributeKeyCustomization():
	Settings(nullptr), 
	AttributeKeyPtr(nullptr)
{}

TSharedRef<IPropertyTypeCustomization> FUGAAttributeKeyCustomization::MakeInstance()
{
	return MakeShared<FUGAAttributeKeyCustomization>();
}

void FUGAAttributeKeyCustomization::CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	HeaderRow
		.NameContent()
		[
			PropertyHandle->CreatePropertyNameWidget()
		];
}

void FUGAAttributeKeyCustomization::CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils)
{
	Settings = GetDefault<UUGACoreSettings>();
	
	void* ValuePtr;
	PropertyHandle->GetValueData(ValuePtr);
	AttributeKeyPtr = static_cast<FUGAAttributeKey*>(ValuePtr);
	
	Options.Reserve(Settings->AttributeKeys.Num());
	int32 SelectedIndex = -1;
	for (int32 i = 0; i < Settings->AttributeKeys.Num(); ++i)
	{
		const FName KeyName = Settings->AttributeKeys[i];
		
		if (!KeyName.IsValid()) { continue; }
		
		Options.Emplace(KeyName);
		
		if (AttributeKeyPtr->KeyName == KeyName)
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
				.OnGenerateWidget_Raw(this, &FUGAAttributeKeyCustomization::HandleGenerateItemWidget)
				.OnSelectionChanged_Raw(this, &FUGAAttributeKeyCustomization::HandleSelectionChanged)
				[
					SAssignNew(ComboBoxContent, SBox)
				]
		];
	
	RefreshContent();
}

TSharedRef<SWidget> FUGAAttributeKeyCustomization::HandleGenerateItemWidget(FName Name)
{
	return SNew(STextBlock)
		.Text(FText::FromName(Name));
}

void FUGAAttributeKeyCustomization::HandleSelectionChanged(FName Name, ESelectInfo::Type Arg)
{
	*AttributeKeyPtr = FUGAAttributeKey(Name);
	CurrentSelection = Name;
	RefreshContent();
}

void FUGAAttributeKeyCustomization::RefreshContent()
{
	if (ComboBoxContent.IsValid())
	{
		auto Widget = HandleGenerateItemWidget(CurrentSelection);
		ComboBoxContent->SetContent(Widget);
	}
}
