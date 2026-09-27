// By hzFishy - 2026 - Do whatever you want with it.


#include "Core/UGASubsystem.h"

#include "Core/UGACoreSettings.h"

	
	/*----------------------------------------------------------------------------
		Defaults
	----------------------------------------------------------------------------*/
UUGASubsystem::UUGASubsystem()
{}

void UUGASubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	// cache settings
	CoreSettings = GetDefault<UUGACoreSettings>();
	
	DefaultEngagementTime = CoreSettings->DefaultEngagementTime;
	
	GlobalEventParameters.Reserve(5);
	
	if (CoreSettings->bAutoSetClientId)
	{
		SetClient();
	}
	
	if (CoreSettings->bAutoStartSession)
	{
		StartSession();
	}
	
	AddGlobalEventParameter(FUGAAttribute(UGA::NAME_AttributeKey_EngagementTime, DefaultEngagementTime));
}

void UUGASubsystem::Deinitialize()
{
	Super::Deinitialize();
}

	
	/*----------------------------------------------------------------------------
		Core
	----------------------------------------------------------------------------*/
void UUGASubsystem::SetClient()
{
	// cache client id (for now its simply the device name)
	CliendId = FPlatformProcess::UserName();
	
	AddGlobalEventParameter(FUGAAttribute(UGA::NAME_AttributeKey_SessionId, CliendId));
}

void UUGASubsystem::StartSession()
{
	SessionId = FGuid::NewGuid().ToString();
}

void UUGASubsystem::EndSession()
{
	SessionId.Empty();
}

void UUGASubsystem::AddGlobalEventParameter(FUGAAttribute Attribute)
{
	GlobalEventParameters.Emplace(Attribute);
}

void UUGASubsystem::RemoveGlobalEventParameter(FUGAAttributeKey AttributeKey)
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

void UUGASubsystem::SendEvent(FUGAEventName EventName)
{
	SendEvent(FUGAEvent(EventName));
}

void UUGASubsystem::SendEventWithAttribute(FUGAEventName EventName, FUGAAttribute Parameter)
{
	SendEvent(FUGAEvent(EventName, Parameter));
}

void UUGASubsystem::SendEventWithAttributes(FUGAEventName EventName, const TArray<FUGAAttribute>& Parameters)
{
	SendEvent(FUGAEvent(EventName, Parameters));
}

void UUGASubsystem::SendEvent(const FUGAEvent& Event)
{
	CachedEvents.Emplace(Event);
}

void UUGASubsystem::FlushEvents()
{
	// TODO:
}
