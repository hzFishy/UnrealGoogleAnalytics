// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

#include "UGAAttributeValue.generated.h"


/** 
 *  Value for an Attribute.
 *  Value type can be: bool, int32, float, FString, FName.
 */
USTRUCT(BlueprintType, DisplayName="Google Analytics Attribute Value", meta=(HiddenByDefault))
struct UNREALGOOGLEANALYTICS_API FUGAAttributeValue
{
	GENERATED_BODY()
	
public:
	FUGAAttributeValue();
	
	FUGAAttributeValue(bool InValue);
	
	FUGAAttributeValue(int32 InValue);
	
	FUGAAttributeValue(float InValue);
	
	FUGAAttributeValue(FString InValue);
	
	FUGAAttributeValue(FName InValue);
	
	
	/** 
	 * Get the stored value as a bool.
	 * Only use this if you know this is a bool.
	 * This will crash if the stored value is of another type.
	 */
	bool GetAsBool() const;
	
	/** 
	 * Get the stored value as a bool.
	 * Only use this if you know this is a bool.
	 * This will crash if the stored value is of another type.
	 */
	bool GetAsBool_Checked() const;
	
	/** 
	 * Get the stored value as a bool.
	 * Returns nullptr if not a bool
	 */
	const bool* TryGetAsBool() const;
	
	
	/** 
	 * Get the stored value as a int32.
	 * Only use this if you know this is a int32.
	 */
	int32 GetAsInt() const;
	
	/** 
	 * Get the stored value as a int32.
	 * Only use this if you know this is a int32.
	 * This will crash if the stored value is of another type.
	 */
	int32 GetAsInt_Checked() const;
	
	/** 
	 * Get the stored value as a int32.
	 * Returns nullptr if not a int32
	 */
	const int32* TryGetAsInt() const;
	
	
	/** 
	 * Get the stored value as a float.
	 * Only use this if you know this is a float.
	 */
	float GetAsFloat() const;
	
	/** 
	 * Get the stored value as a float.
	 * Only use this if you know this is a float.
	 * This will crash if the stored value is of another type.
	 */
	float GetAsFloat_Checked() const;
	
	/** 
	 * Get the stored value as a float.
	 * Returns nullptr if not a float
	 */
	const float* TryGetAsFloat() const;
	
	
	/** 
	 * Get the stored value as a FString.
	 * Only use this if you know this is a FString.
	 */
	FString GetAsString() const;
	
	/** 
	 * Get the stored value as a FString.
	 * Only use this if you know this is a FString.
	 * This will crash if the stored value is of another type.
	 */
	FString GetAsString_Checked() const;
	
	/** 
	 * Get the stored value as a FString.
	 * Returns nullptr if not a FString
	 */
	const FString* TryGetAsString() const;
	
	
	/** 
	 * Get the stored value as a FName.
	 * Only use this if you know this is a FName 
	 */
	FName GetAsName() const;
	
	/** 
	 * Get the stored value as a FName.
	 * Only use this if you know this is a FName.
	 * This will crash if the stored value is of another type.
	 */
	FName GetAsName_Checked() const;
	
	/** 
	 * Get the stored value as a FName.
	 * Returns nullptr if not a FName
	 */
	const FName* TryGetAsName() const;
	
	
	/** 
	 *  Get the stored value as a FString, this will work for any underlying type.
	 */
	FString ConvertToString() const;
	
protected:
	TVariant<bool, int32, float, FString, FName> Value;
};
