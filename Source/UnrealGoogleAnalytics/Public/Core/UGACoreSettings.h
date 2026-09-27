// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "UGACoreSettings.generated.h"


namespace UGA
{
	inline FName NAME_AttributeKey_ClientId = "client_id";
	inline FName NAME_AttributeKey_SessionId = "session_id";
	inline FName NAME_AttributeKey_EngagementTime = "engagement_time_msec";
}


UCLASS(Config=Engine, DefaultConfig, DisplayName="Unreal Google Analytics Settings")
class UNREALGOOGLEANALYTICS_API UUGACoreSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UUGACoreSettings();
	
	UPROPERTY(Config, EditAnywhere, Category="Core")
	bool bAutoSetClientId;
	
	UPROPERTY(Config, EditAnywhere, Category="Core")
	bool bAutoStartSession;
	
	/** In milliseconds */
	UPROPERTY(Config, EditAnywhere, Category="Core", meta=(ForceUnits="Milliseconds"))
	float DefaultEngagementTime;
	
	/** 
	 * Measurement ID, starts with G-
	 * 
	 * Should be found in Property Settings -> Data Streams -> Measurement ID
	 */
	UPROPERTY(Config, EditAnywhere, Category="Core", meta=(PasswordField=true))
	FString MeasurementID;
	
	/** 
	 * Secret
	 * 
	 * Should be found in Property Settings -> Data Streams -> Measurement Protocol API secrets.
	 * If you don't have any secret you should generate a new one
	 */
	UPROPERTY(Config, EditAnywhere, Category="Core", meta=(PasswordField=true))
	FString Secret;
	
	/** 
	 *  List here all possible attribute keys.
	 *  Note: if you rename an existing key, it won't be updated where you used it.
	 *  TODO: Add validation to detect renamed exisitng keys
	 */
	UPROPERTY(Config, EditAnywhere, Category="Attributes")
	TArray<FName> AttributeKeys;
	
	/** 
	 *  List here all possible event names.
	 *  Note: if you rename an existing event name, it won't be updated where you used it.
	 *  TODO: Add validation to detect renamed exisitng event names
	 */
	UPROPERTY(Config, EditAnywhere, Category="Attributes")
	TArray<FName> EventNames;
	
	
	virtual FName GetCategoryName() const override { return "Plugins"; };
};
