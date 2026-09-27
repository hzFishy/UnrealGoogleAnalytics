// By hzFishy - 2026 - Do whatever you want with it.


#include "Core/UGACoreSettings.h"


UUGACoreSettings::UUGACoreSettings(): 
	bAutoSetClientId(true), 
	bAutoStartSession(true),
	DefaultEngagementTime(100)
{
	AttributeKeys.Emplace(UGA::NAME_AttributeKey_ClientId);
	AttributeKeys.Emplace(UGA::NAME_AttributeKey_SessionId);
}
