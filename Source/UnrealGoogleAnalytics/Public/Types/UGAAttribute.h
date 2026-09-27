// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

#include "UGAAttributeKey.h"
#include "UGAAttributeValue.h"
#include "UGAAttribute.generated.h"


/** 
 *  Pair of a Key and a Value. For example for an event this can be perceive as an event parameter.
 *  Value type can be: bool, int32, float, FString, FName.
 */
USTRUCT(BlueprintType, DisplayName="Google Analytic Attribute Key")
struct UNREALGOOGLEANALYTICS_API FUGAAttribute
{
	GENERATED_BODY()
	
public:
	FUGAAttribute();
	
	FUGAAttribute(FUGAAttributeKey InKey, FUGAAttributeValue InValue);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUGAAttributeKey Key;
	
	UPROPERTY()
	FUGAAttributeValue Value;
};
