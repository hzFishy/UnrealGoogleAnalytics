// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

#include "Interfaces/IHttpRequest.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ThirdParty/BMJson.h"
#include "Types/UGAEvent.h"
#include "Types/UGAAttribute.h"
#include "Types/UGAEventName.h"
#include "Types/UGAFlushEventType.h"
#include "UGAGoogleAnalyticsSubsystem.generated.h"
class UUGACoreSettings;


UCLASS(DisplayName="Google Analytics Subsystem")
class UNREALGOOGLEANALYTICS_API UUGAGoogleAnalyticsSubsystem : public UGameInstanceSubsystem
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
	FString ClientId;
	
	FString SessionId;
	
	/** In milliseconds */
	float DefaultEngagementTime;
	
	float EventFlushIntervalTime;
	
	float ElapsedTimeSinceLastEventFlush;
	
	TArray<FUGAEvent> CachedEvents;
	
	/** Parameters that will always be added to events */
	TArray<FUGAAttribute> GlobalEventParameters;
	
	
	/*----------------------------------------------------------------------------
		Defaults
	----------------------------------------------------------------------------*/
public:
	UUGAGoogleAnalyticsSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
protected:
	bool Tick(float DeltaTime);
	
	
	/*----------------------------------------------------------------------------
		Core
	----------------------------------------------------------------------------*/
public:
	UFUNCTION(BlueprintCallable, Category="Core")
	void SetClient(FString NewClientId);
	
	UFUNCTION(BlueprintCallable, Category="Core")
	void SetEventFlushIntervalTime(float NewEventFlushIntervalTime);
	
	
	/** 
	 *  Start a new session, a Client Id is required.
	 *  This does nothing if a session is already set, unless bForceNew is true.
	 */
	UFUNCTION(BlueprintCallable, Category="Session")
	void StartSession(bool bForceNew = false);
	
	/** 
	 *  Ends the current session.
	 *  Does nothing if no session was active.
	 */
	UFUNCTION(BlueprintCallable, Category="Session")
	void EndSession();
	
	UFUNCTION(BlueprintPure, Category="Session")
	FString GetSessionId() const;
	
	
	UFUNCTION(BlueprintCallable, Category="Attribute")
	void AddGlobalEventParameter(FUGAAttribute Attribute);
	
	UFUNCTION(BlueprintCallable, Category="Attribute")
	void RemoveGlobalEventParameter(FUGAAttributeKey AttributeKey);
	
	UFUNCTION(BlueprintCallable, Category="Attribute")
	void RemoveGlobalEventParameterByName(UPARAM(meta=(GetOptions="UnrealGoogleAnalytics.UGAGoogleAnalyticsLibrary.GetAttributeKeyOptions")) FName AttributeKeyName);
	
	
	UFUNCTION(BlueprintCallable, Category="Event")
	void SendEvent(FUGAEventName EventName, EUGAFlushEventType FlushType = EUGAFlushEventType::None);
	
	UFUNCTION(BlueprintCallable, Category="Event")
	void SendEventByName(UPARAM(meta=(GetOptions="UnrealGoogleAnalytics.UGAGoogleAnalyticsLibrary.GetEventNameOptions")) FName EventName, EUGAFlushEventType FlushType = EUGAFlushEventType::None);
	
	UFUNCTION(BlueprintCallable, Category="Event")
	void SendEventWithAttribute(FUGAEventName EventName, FUGAAttribute Parameter, EUGAFlushEventType FlushType = EUGAFlushEventType::None);
	
	UFUNCTION(BlueprintCallable, Category="Event")
	void SendEventWithAttributes(FUGAEventName EventName, const TArray<FUGAAttribute>& Parameters, EUGAFlushEventType FlushType = EUGAFlushEventType::None);
	
	UFUNCTION(BlueprintCallable, Category="Event")
	void SendEventFromNameWithAttribute(UPARAM(meta=(GetOptions="UnrealGoogleAnalytics.UGAGoogleAnalyticsLibrary.GetEventNameOptions")) FName EventName, FUGAAttribute Parameter, EUGAFlushEventType FlushType = EUGAFlushEventType::None);
	
	UFUNCTION(BlueprintCallable, Category="Event")
	void SendEventFromNameWithAttributes(UPARAM(meta=(GetOptions="UnrealGoogleAnalytics.UGAGoogleAnalyticsLibrary.GetEventNameOptions")) FName EventName, const TArray<FUGAAttribute>& Parameters, EUGAFlushEventType FlushType = EUGAFlushEventType::None);
	
	void SendEvent(const FUGAEvent& Event, EUGAFlushEventType FlushType);
	
	
	UFUNCTION(BlueprintCallable, Category="Event")
	void FlushAllEvents();
	
protected:
	void FlushEvent(const FUGAEvent& Event);
	
	FString GetURL() const;
	
	void InitRequest(IHttpRequest& Request);
	
	void FillRequest(IHttpRequest& Request, const TArray<FUGAEvent>& Events);
	
	void AppendAttribute(BMJson::JsonObject& Params, const FUGAAttribute& Attribute) const;
	
	void SendRequest(IHttpRequest& Request);
	
	void OnRequestProcessCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bProcessedSuccessfully);
	
	bool CanSendRequests() const;
};
