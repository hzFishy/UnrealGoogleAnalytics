// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

#include "UGAAttributeKey.generated.h"

/** 
 *  Key for an Attribute.
 *  Internally this is a plain FName but it wrapped to allow display customization.
 *  Configure the auto complete dropdown from the settings
 */
USTRUCT(BlueprintType, DisplayName="Google Analytics Attribute Key")
struct UNREALGOOGLEANALYTICS_API FUGAAttributeKey
{
	GENERATED_BODY()
	
public:
	
	FUGAAttributeKey();
	
	FUGAAttributeKey(FName InKeyName);
	
	FName KeyName;
	
	bool operator==(const FUGAAttributeKey& OtherKey) const;
};
