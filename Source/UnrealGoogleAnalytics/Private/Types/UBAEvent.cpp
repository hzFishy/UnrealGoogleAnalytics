// By hzFishy - 2026 - Do whatever you want with it.


#include "Types/UBAEvent.h"


FUGAEvent::FUGAEvent()
{}

FUGAEvent::FUGAEvent(FUGAEventName InName):
	Name(InName)
{}

FUGAEvent::FUGAEvent(FUGAEventName InName, const FUGAAttribute& Attribute):
	Name(InName), Attributes({Attribute})
{}

FUGAEvent::FUGAEvent(FUGAEventName InName, const TArray<FUGAAttribute>& Attributes):
	Name(InName), Attributes(Attributes)
{}
