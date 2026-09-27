// By hzFishy - 2026 - Do whatever you want with it.


#include "PropertyCustomization/UGAEventNameCustomization.h"
#include "DetailWidgetRow.h"
#include "IDetailChildrenBuilder.h"
#include "SSimpleComboButton.h"
#include "Core/UGACoreSettings.h"


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
	
	EventNameProperty = PropertyHandle->GetChildHandle(0);
	
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
				.Text_Lambda( [this]()
				{
					FName Value;
					EventNameProperty->GetValue(Value);
					return FText::FromString(Value.ToString());
				})
		];
}

TSharedRef<SWidget> FUGAEventNameCustomization::OnGenerateDropdownMenu()
{
	FMenuBuilder MenuBuilder(true, nullptr, nullptr);
	
	for (FName EventName : Settings->EventNames)
	{
		MenuBuilder.AddMenuEntry(
			FText::FromString(EventName.ToString()),
			FText(),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateSP(this, &FUGAEventNameCustomization::OnDropDownEntrySelected, EventName)
			)
		);
	}
	
	return MenuBuilder.MakeWidget();
}

void FUGAEventNameCustomization::OnDropDownEntrySelected(FName Name)
{
	EventNameProperty->SetValue(Name);
}
