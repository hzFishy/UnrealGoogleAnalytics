// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

class UUGACoreSettings;
struct FUGAAttributeKey;


class UNREALGOOGLEANALYTICSEDITOR_API FUGAAttributeKeyCustomization : public IPropertyTypeCustomization
{
public:
	FUGAAttributeKeyCustomization();
	
	static TSharedRef<IPropertyTypeCustomization> MakeInstance();
 
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	
	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

protected:
	const UUGACoreSettings* Settings;
	FUGAAttributeKey* AttributeKeyPtr;
	TSharedPtr<SComboBox<FName>> DropDownWidget;
	TSharedPtr<SBox> ComboBoxContent;
	TArray<FName> Options;
	FName CurrentSelection;
	
	TSharedRef<SWidget> HandleGenerateItemWidget(FName Name);
	void HandleSelectionChanged(FName Name, ESelectInfo::Type Arg);
	
	void RefreshContent();
};
