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

FUGAAttributeValue UUGAGoogleAnalyticsLibrary::MakeAttributeValueFromName(FName KeyName)
{
	return FUGAAttributeValue(KeyName);
}


FUGAAttribute UUGAGoogleAnalyticsLibrary::MakeAttributeFromNameWithBool(FName KeyName, bool bValue)
{
	return FUGAAttribute(FUGAAttributeKey(KeyName), FUGAAttributeValue(bValue));
}

FUGAAttribute UUGAGoogleAnalyticsLibrary::MakeAttributeFromNameWithInteger(FName KeyName, int32 Value)
{
	return FUGAAttribute(FUGAAttributeKey(KeyName), FUGAAttributeValue(Value));
}

FUGAAttribute UUGAGoogleAnalyticsLibrary::MakeAttributeFromNameWithFloat(FName KeyName, float Value)
{
	return FUGAAttribute(FUGAAttributeKey(KeyName), FUGAAttributeValue(Value));
}

FUGAAttribute UUGAGoogleAnalyticsLibrary::MakeAttributeFromNameWithString(FName KeyName, FString Value)
{
	return FUGAAttribute(FUGAAttributeKey(KeyName), FUGAAttributeValue(Value));
}

FUGAAttribute UUGAGoogleAnalyticsLibrary::MakeAttributeFromNameWithName(FName KeyName, FName Value)
{
	return FUGAAttribute(FUGAAttributeKey(KeyName), FUGAAttributeValue(Value));
}

TArray<FName> UUGAGoogleAnalyticsLibrary::GetEventNameOptions()
{
	return GetDefault<UUGACoreSettings>()->EventNames;
}

TArray<FName> UUGAGoogleAnalyticsLibrary::GetAttributeKeyOptions()
{
	return GetDefault<UUGACoreSettings>()->AttributeKeys;
}
