// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "Types/UBAEvent.h"
#include "Types/UGAAttribute.h"
#include "Types/UGAEventName.h"
#include "UGASubsystem.generated.h"
class UUGACoreSettings;


UCLASS(DisplayName="Google Analytics Subsystem")
class UNREALGOOGLEANALYTICS_API UUGASubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	
	/*----------------------------------------------------------------------------
		Properties
	----------------------------------------------------------------------------*/
protected:
	UPROPERTY()
	TObjectPtr<const UUGACoreSettings> CoreSettings;
	
	
	//////////////////////////////////
	// Runtime
	FString CliendId;
	FString SessionId;
	/** In milliseconds */
	float DefaultEngagementTime;
	
	TArray<FUGAEvent> CachedEvents;
	
	/** Parameters that will always be added to events */
	TArray<FUGAAttribute> GlobalEventParameters;
	
	
	/*----------------------------------------------------------------------------
		Defaults
	----------------------------------------------------------------------------*/
public:
	UUGASubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	
	/*----------------------------------------------------------------------------
		Core
	----------------------------------------------------------------------------*/
protected:
	void SetClient();
	
	void StartSession();
	
	void EndSession();
	
	UFUNCTION(BlueprintCallable, Category="Attribute")
	void AddGlobalEventParameter(FUGAAttribute Attribute);
	
	UFUNCTION(BlueprintCallable, Category="Attribute")
	void RemoveGlobalEventParameter(FUGAAttributeKey AttributeKey);
	
	UFUNCTION(BlueprintCallable, Category="Event")
	void SendEvent(FUGAEventName EventName);
	
	UFUNCTION(BlueprintCallable, Category="Event")
	void SendEventWithAttribute(FUGAEventName EventName, FUGAAttribute Parameter);
	
	UFUNCTION(BlueprintCallable, Category="Event")
	void SendEventWithAttributes(FUGAEventName EventName, const TArray<FUGAAttribute>& Parameters);
	
	void SendEvent(const FUGAEvent& Event);
	
	UFUNCTION(BlueprintCallable, Category="Event")
	void FlushEvents();
};
