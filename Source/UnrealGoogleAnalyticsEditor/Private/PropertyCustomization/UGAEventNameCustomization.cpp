// By hzFishy - 2026 - Do whatever you want with it.


#include "PropertyCustomization/UGAEventNameCustomization.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "SSimpleComboButton.h"
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
	
	ChildBuilder.AddCustomRow(INVTEXT("")).NameContent()
		[
			PropertyHandle->CreatePropertyNameWidget()
		]
		.ValueContent()
		[
			SAssignNew(DropDownWidget, SSimpleComboButton)
				.OnGetMenuContent(this, &FUGAEventNameCustomization::OnGenerateDropdownMenu)
				.ToolTipText(INVTEXT("Select an entry"))
				.HasDownArrow(true)
				.UsesSmallText(true)
				.Text_Raw(this, &FUGAEventNameCustomization::GetTextDisplay)
		]; 
}

TSharedRef<SWidget> FUGAEventNameCustomization::OnGenerateDropdownMenu()
{
	FMenuBuilder MenuBuilder(true, nullptr, nullptr);
	
	for (FName EventName : Settings->EventNames)
	{
		if (EventName.IsNone()) { continue; }
		
		MenuBuilder.AddMenuEntry(
			FText::FromString(EventName.ToString()),
			FText(),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateSP(this, &FUGAEventNameCustomization::OnDropDownEntrySelected, EventName))
		);
	}
	
	return MenuBuilder.MakeWidget();
}

void FUGAEventNameCustomization::OnDropDownEntrySelected(FName Name)
{
	*EventNamePtr = FUGAEventName(Name);
}

FText FUGAEventNameCustomization::GetTextDisplay() const
{
	return FText::FromName(EventNamePtr->EventName);
}
