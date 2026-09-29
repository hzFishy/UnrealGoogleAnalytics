// By hzFishy - 2026 - Do whatever you want with it.


#include "Core/UGAGoogleAnalyticsSubsystem.h"
#include "HttpModule.h"
#include "Core/UGACore.h"
#include "Core/UGACoreSettings.h"
#include "Interfaces/IHttpResponse.h"
#include "ThirdParty/BMJson.h"

	
	/*----------------------------------------------------------------------------
		Defaults
	----------------------------------------------------------------------------*/
UUGAGoogleAnalyticsSubsystem::UUGAGoogleAnalyticsSubsystem():
	DefaultEngagementTime(-1),
	EventFlushIntervalTime(),
	ElapsedTimeSinceLastEventFlush()
{}

void UUGAGoogleAnalyticsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// cache settings
	CoreSettings = GetDefault<UUGACoreSettings>();
	
	DefaultEngagementTime = CoreSettings->DefaultEngagementTime;
	EventFlushIntervalTime = CoreSettings->EventFlushIntervalTime;
	
	GlobalEventParameters.Reserve(5);
	
	if (CoreSettings->bAutoSetClientId)
	{
		// cache client id (for now its simply the device name)
		SetClient(FPlatformProcess::UserName());
	}
	
	if (CoreSettings->bAutoStartSession)
	{
		StartSession();
	}
	
	FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &ThisClass::Tick));
}

void UUGAGoogleAnalyticsSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
	EndSession();
}

bool UUGAGoogleAnalyticsSubsystem::Tick(float DeltaTime)
{
	ElapsedTimeSinceLastEventFlush += DeltaTime;
	
	if (ElapsedTimeSinceLastEventFlush >= EventFlushIntervalTime)
	{
		FlushAllEvents();
		
		ElapsedTimeSinceLastEventFlush = 0;
	}
	
	return true;
}

	
	/*----------------------------------------------------------------------------
		Core
	----------------------------------------------------------------------------*/
void UUGAGoogleAnalyticsSubsystem::SetClient(FString NewClientId)
{
	ClientId = NewClientId;
}

void UUGAGoogleAnalyticsSubsystem::SetEventFlushIntervalTime(float NewEventFlushIntervalTime)
{
	EventFlushIntervalTime = NewEventFlushIntervalTime;
}

void UUGAGoogleAnalyticsSubsystem::StartSession(bool bForceNew)
{
	if (ClientId.IsEmpty()) { return; }
	
	if (SessionId.IsEmpty() || bForceNew)
	{
		SessionId = FGuid::NewGuid().ToString();
	}
}

void UUGAGoogleAnalyticsSubsystem::EndSession()
{
	SessionId.Empty();
}

FString UUGAGoogleAnalyticsSubsystem::GetSessionId() const
{
	return SessionId;
}


void UUGAGoogleAnalyticsSubsystem::AddGlobalEventParameter(FUGAAttribute Attribute)
{
	GlobalEventParameters.Emplace(Attribute);
}

void UUGAGoogleAnalyticsSubsystem::RemoveGlobalEventParameter(FUGAAttributeKey AttributeKey)
{
	for (int32 Index = 0; Index < GlobalEventParameters.Num(); ++Index)
	{
		if (GlobalEventParameters[Index].Key == AttributeKey)
		{
			GlobalEventParameters.RemoveAt(Index);
			return;;
		}
	}
}

void UUGAGoogleAnalyticsSubsystem::RemoveGlobalEventParameterByName(FName AttributeKeyName)
{
	RemoveGlobalEventParameter(FUGAAttributeKey(AttributeKeyName));
}


void UUGAGoogleAnalyticsSubsystem::SendEvent(FUGAEventName EventName, EUGAFlushEventType FlushType)
{
	SendEvent(FUGAEvent(EventName), FlushType);
}

void UUGAGoogleAnalyticsSubsystem::SendEventByName(FName EventName, EUGAFlushEventType FlushType)
{
	SendEvent(FUGAEventName(EventName), FlushType);
}

void UUGAGoogleAnalyticsSubsystem::SendEventWithAttribute(FUGAEventName EventName, FUGAAttribute Parameter, EUGAFlushEventType FlushType)
{
	SendEvent(FUGAEvent(EventName, Parameter), FlushType);
}

void UUGAGoogleAnalyticsSubsystem::SendEventWithAttributes(FUGAEventName EventName, const TArray<FUGAAttribute>& Parameters, EUGAFlushEventType FlushType)
{
	SendEvent(FUGAEvent(EventName, Parameters), FlushType);
}

void UUGAGoogleAnalyticsSubsystem::SendEventFromNameWithAttribute(FName EventName, FUGAAttribute Parameter, EUGAFlushEventType FlushType)
{
	SendEvent(FUGAEvent(FUGAEventName(EventName), Parameter), FlushType);
}

void UUGAGoogleAnalyticsSubsystem::SendEventFromNameWithAttributes(FName EventName, const TArray<FUGAAttribute>& Parameters, EUGAFlushEventType FlushType)
{
	SendEvent(FUGAEvent(FUGAEventName(EventName), Parameters), FlushType);
}

void UUGAGoogleAnalyticsSubsystem::SendEvent(const FUGAEvent& Event, EUGAFlushEventType FlushType)
{
	switch (FlushType) 
	{
	case EUGAFlushEventType::None:
		{
			CachedEvents.Emplace(Event);
			break;
		}
	case EUGAFlushEventType::FlushSingle:
		{
			FlushEvent(Event);
			break;
		}
	case EUGAFlushEventType::FlushAll:
		{
			CachedEvents.Emplace(Event);
			FlushAllEvents();
			break;
		}
	}
}

void UUGAGoogleAnalyticsSubsystem::FlushAllEvents()
{
	if (!CanSendRequests())
	{
		UE_LOG(LogGoogleAnalytics, Error, TEXT("Tried to flush events but cannot send HTTP requests, ClientId: %s, SessionId: %s"), *ClientId, *SessionId);
		return;
	}
	
	if (CachedEvents.IsEmpty()) { return; }
	
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	InitRequest(Request.Get());
	FillRequest(Request.Get(), CachedEvents);
	SendRequest(Request.Get());
	
	CachedEvents.Empty();
}

void UUGAGoogleAnalyticsSubsystem::FlushEvent(const FUGAEvent& Event)
{
	if (!CanSendRequests())
	{
		UE_LOG(LogGoogleAnalytics, Error, TEXT("Tried to flush event but cannot send HTTP requests, ClientId: %s, SessionId: %s"), *ClientId, *SessionId);
		return;
	}
	
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	InitRequest(Request.Get());
	FillRequest(Request.Get(), { Event });
	SendRequest(Request.Get());
}

FString UUGAGoogleAnalyticsSubsystem::GetURL() const
{
	return FString::Printf(
		TEXT("https://www.google-analytics.com/mp/collect?measurement_id=%s&api_secret=%s"), 
		*CoreSettings->MeasurementID,
		*CoreSettings->Secret
	);
}

void UUGAGoogleAnalyticsSubsystem::InitRequest(IHttpRequest& Request)
{
	Request.SetURL(GetURL());
	Request.SetVerb("POST");
	Request.SetHeader(TEXT("User-Agent"), TEXT("UETEST"));
	Request.SetHeader(TEXT("Content-Type"), TEXT("text/plain"));
}

void UUGAGoogleAnalyticsSubsystem::FillRequest(IHttpRequest& Request, const TArray<FUGAEvent>& Events)
{
	BMJson::Json BodyParser;
	{
		BodyParser[UGA::ClientId] = TCHAR_TO_UTF8(*ClientId);
		
		BMJson::JsonArray JsonEvents;
		{
			for (auto& Event : Events)
			{
				BMJson::JsonObject SingleEvent;
				{
					SingleEvent["name"] = TCHAR_TO_UTF8(*Event.Name.EventName.ToString());
					
					BMJson::JsonObject Params;
					Params[UGA::SessionId] = TCHAR_TO_UTF8(*SessionId);
					Params[UGA::EngagementTime] = DefaultEngagementTime;
					
					for (int32 i = 0; i < GlobalEventParameters.Num(); ++i)
					{
						AppendAttribute(Params, GlobalEventParameters[i]);
					}
					
					for (int32 i = 0; i < Event.Attributes.Num(); ++i)
					{
						AppendAttribute(Params, Event.Attributes[i]);
					}
					
					SingleEvent["params"] = std::move(Params);
				}
				JsonEvents.AddValue() = std::move(SingleEvent);
			}
		}
		
		BodyParser["events"] = std::move(JsonEvents);
	}
	
	const FString BodyAsString = BodyParser.Serialize(true).c_str();
	
	UE_LOG(LogGoogleAnalytics, VeryVerbose, TEXT("HTTP request body as string: \n%s"), *BodyAsString);
	
	Request.SetContentAsString(BodyAsString);
}

void UUGAGoogleAnalyticsSubsystem::AppendAttribute(BMJson::JsonObject& Params, const FUGAAttribute& Attribute) const
{
	if (auto* BoolValue = Attribute.Value.TryGetAsBool())
	{
		Params[*Attribute.Key] = *BoolValue;
	}
	else if (auto* IntValue = Attribute.Value.TryGetAsInt())
	{
		Params[*Attribute.Key] = *IntValue;
	}
	else if (auto* FloatValue = Attribute.Value.TryGetAsFloat())
	{
		Params[*Attribute.Key] = *FloatValue;
	}
	else if (auto* StringValue = Attribute.Value.TryGetAsString())
	{
		Params[*Attribute.Key] = TCHAR_TO_UTF8(*(*StringValue));
	}
	else if (auto* NameValue = Attribute.Value.TryGetAsName())
	{
		Params[*Attribute.Key] = TCHAR_TO_UTF8(*NameValue->ToString());
	}
}

void UUGAGoogleAnalyticsSubsystem::SendRequest(IHttpRequest& Request)
{
	Request.OnProcessRequestComplete().BindUObject(this, &ThisClass::OnRequestProcessCompleted);
	
	UE_LOG(LogGoogleAnalytics, Verbose, TEXT("Sending HTTP request"));
	Request.ProcessRequest();
}

void UUGAGoogleAnalyticsSubsystem::OnRequestProcessCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bProcessedSuccessfully)
{
	const FString ResponseString = Response->GetContentAsString();
	if (Response->GetStatus() == EHttpRequestStatus::Succeeded)
	{
		UE_LOG(LogGoogleAnalytics, Verbose, TEXT("HTTP request succeeded"));
	}
	else
	{
		UE_LOG(LogGoogleAnalytics, Error, TEXT("HTTP request didn't succeeded"));
	}
	UE_LOG(LogGoogleAnalytics, Verbose, TEXT("HTTP request response code: %i\n%s"), Response->GetResponseCode(), *Response->GetContentAsString());
}

bool UUGAGoogleAnalyticsSubsystem::CanSendRequests() const
{
	return !ClientId.IsEmpty() && !SessionId.IsEmpty();
}
