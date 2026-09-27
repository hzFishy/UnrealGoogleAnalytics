// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

class UUGACoreSettings;
class SSimpleComboButton;


class UNREALGOOGLEANALYTICSEDITOR_API FUGAEventNameCustomization : public IPropertyTypeCustomization
{
public:
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
 
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

protected:
	UPROPERTY()
	TObjectPtr<const UUGACoreSettings> Settings;
	TSharedPtr<IPropertyHandle> EventNameProperty;
	TSharedPtr<SSimpleComboButton> DropDownWidget;
	
	
	TSharedRef<SWidget> OnGenerateDropdownMenu();
	
	void OnDropDownEntrySelected(FName Name);
};
