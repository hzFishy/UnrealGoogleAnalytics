// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Types/UGAAttribute.h"
#include "Types/UGAAttributeKey.h"
#include "Types/UGAAttributeValue.h"
#include "Types/UGAEventName.h"
#include "UGAGoogleAnalyticsLibrary.generated.h"


UCLASS(DisplayName="Google Analytics Library")
class UNREALGOOGLEANALYTICS_API UUGAGoogleAnalyticsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAEventName MakeEventName(UPARAM(meta=(GetOptions="UnrealGoogleAnalytics.UGAGoogleAnalyticsLibrary.GetEventNameOptions")) FName Name);
	
	
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAAttributeKey MakeAttributeKey(UPARAM(meta=(GetOptions="UnrealGoogleAnalytics.UGAGoogleAnalyticsLibrary.GetAttributeKeyOptions")) FName Name);
	
	
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAAttributeValue MakeAttributeValueFromBool(bool bValue);
	
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAAttributeValue MakeAttributeValueFromInteger(int32 Value);
	
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAAttributeValue MakeAttributeValueFromFloat(float Value);
	
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAAttributeValue MakeAttributeValueFromString(FString Value);
	
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAAttributeValue MakeAttributeValueFromName(FName Value);
	
	
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAAttribute MakeAttributeFromNameWithBool(UPARAM(meta=(GetOptions="UnrealGoogleAnalytics.UGAGoogleAnalyticsLibrary.GetAttributeKeyOptions")) FName Name, bool bValue);
	
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAAttribute MakeAttributeFromNameWithInteger(UPARAM(meta=(GetOptions="UnrealGoogleAnalytics.UGAGoogleAnalyticsLibrary.GetAttributeKeyOptions")) FName Name, int32 Value);
	
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAAttribute MakeAttributeFromNameWithFloat(UPARAM(meta=(GetOptions="UnrealGoogleAnalytics.UGAGoogleAnalyticsLibrary.GetAttributeKeyOptions")) FName Name, float Value);
	
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAAttribute MakeAttributeFromNameWithString(UPARAM(meta=(GetOptions="UnrealGoogleAnalytics.UGAGoogleAnalyticsLibrary.GetAttributeKeyOptions")) FName Name, FString Value);
	
	UFUNCTION(BlueprintPure, Category="GoogleAnalytics", meta=(BlueprintThreadSafe))
	static FUGAAttribute MakeAttributeFromNameWithName(UPARAM(meta=(GetOptions="UnrealGoogleAnalytics.UGAGoogleAnalyticsLibrary.GetAttributeKeyOptions")) FName Name, FName Value);
	
	
	UFUNCTION()
	static TArray<FName> GetEventNameOptions();
	
	UFUNCTION()
	static TArray<FName> GetAttributeKeyOptions();
};
