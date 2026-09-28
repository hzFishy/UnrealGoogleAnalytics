// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

class UUGACoreSettings;
class SSimpleComboButton;
struct FUGAEventName;

class UNREALGOOGLEANALYTICSEDITOR_API FUGAEventNameCustomization : public IPropertyTypeCustomization
{
public:
	FUGAEventNameCustomization();
	
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
 
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

protected:
	const UUGACoreSettings* Settings;
	FUGAEventName* EventNamePtr;
	TSharedPtr<SSimpleComboButton> DropDownWidget;
	
	
	TSharedRef<SWidget> OnGenerateDropdownMenu();
	void OnDropDownEntrySelected(FName Name);
	FText GetTextDisplay() const;
};
