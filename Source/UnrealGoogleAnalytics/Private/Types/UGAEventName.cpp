// By hzFishy - 2026 - Do whatever you want with it.


#include "Types/UGAEventName.h"


FUGAEventName::FUGAEventName()
{}

FUGAEventName::FUGAEventName(FName InEventName):
	EventName(InEventName)
{}

bool FUGAEventName::operator==(const FUGAEventName& Other) const
{
	return EventName == Other.EventName;
}
