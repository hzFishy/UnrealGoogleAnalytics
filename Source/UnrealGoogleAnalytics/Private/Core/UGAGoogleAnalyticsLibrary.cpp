// By hzFishy - 2026 - Do whatever you want with it.


#include "Core/UGAGoogleAnalyticsLibrary.h"
#include "Core/UGACoreSettings.h"


FUGAEventName UUGAGoogleAnalyticsLibrary::MakeEventName(FName Name)
{
	return FUGAEventName(Name);
}


FUGAAttributeKey UUGAGoogleAnalyticsLibrary::MakeAttributeKey(FName Name)
{
	return FUGAAttributeKey(Name);
}


FUGAAttributeValue UUGAGoogleAnalyticsLibrary::MakeAttributeValueFromBool(bool bValue)
{
	return FUGAAttributeValue(bValue);
}

FUGAAttributeValue UUGAGoogleAnalyticsLibrary::MakeAttributeValueFromInteger(int32 Value)
{
	return FUGAAttributeValue(Value);
}

FUGAAttributeValue UUGAGoogleAnalyticsLibrary::MakeAttributeValueFromFloat(float Value)
{
	return FUGAAttributeValue(Value);
}

FUGAAttributeValue UUGAGoogleAnalyticsLibrary::MakeAttributeValueFromString(FString Value)
{
	return FUGAAttributeValue(Value);
}

FUGAAttributeValue UUGAGoogleAnalyticsLibrary::MakeAttributeValueFromName(FName Value)
{
	return FUGAAttributeValue(Value);
}


FUGAAttribute UUGAGoogleAnalyticsLibrary::MakeAttributeFromNameWithBool(FName Name, bool bValue)
{
	return FUGAAttribute(FUGAAttributeKey(Name), FUGAAttributeValue(bValue));
}

FUGAAttribute UUGAGoogleAnalyticsLibrary::MakeAttributeFromNameWithInteger(FName Name, int32 Value)
{
	return FUGAAttribute(FUGAAttributeKey(Name), FUGAAttributeValue(Value));
}

FUGAAttribute UUGAGoogleAnalyticsLibrary::MakeAttributeFromNameWithFloat(FName Name, float Value)
{
	return FUGAAttribute(FUGAAttributeKey(Name), FUGAAttributeValue(Value));
}

FUGAAttribute UUGAGoogleAnalyticsLibrary::MakeAttributeFromNameWithString(FName Name, FString Value)
{
	return FUGAAttribute(FUGAAttributeKey(Name), FUGAAttributeValue(Value));
}

FUGAAttribute UUGAGoogleAnalyticsLibrary::MakeAttributeFromNameWithName(FName Name, FName Value)
{
	return FUGAAttribute(FUGAAttributeKey(Name), FUGAAttributeValue(Value));
}

TArray<FName> UUGAGoogleAnalyticsLibrary::GetEventNameOptions()
{
	return GetDefault<UUGACoreSettings>()->EventNames;
}

TArray<FName> UUGAGoogleAnalyticsLibrary::GetAttributeKeyOptions()
{
	return GetDefault<UUGACoreSettings>()->AttributeKeys;
}
