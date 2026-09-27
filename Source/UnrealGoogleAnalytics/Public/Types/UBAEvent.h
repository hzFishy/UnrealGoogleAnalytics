// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

#include "UGAAttribute.h"
#include "UGAEventName.h"


struct FUGAEvent
{
public:
	FUGAEvent();
	
	FUGAEvent(FUGAEventName InName);
	
	FUGAEvent(FUGAEventName InName, const FUGAAttribute& Attribute);
	
	FUGAEvent(FUGAEventName InName, const TArray<FUGAAttribute>& Attributes);
	
	
	FUGAEventName Name;
	/** Parameters */
	TArray<FUGAAttribute> Attributes;
};
