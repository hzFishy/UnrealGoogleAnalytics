// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

#include "UGAEventName.generated.h"


/** Wrapper for an event name */
USTRUCT(BlueprintType, DisplayName="Event Name")
struct UNREALGOOGLEANALYTICS_API FUGAEventName
{
	GENERATED_BODY()
	
public:
	FUGAEventName();
	
	FUGAEventName(FName InEventName);
	
	UPROPERTY()
	FName EventName;
	
	bool operator==(const FUGAEventName& Other) const;
};
