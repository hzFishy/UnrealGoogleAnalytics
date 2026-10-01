// By hzFishy - 2026 - Do whatever you want with it.

#pragma once

#include "UGAFlushEventType.generated.h"


UENUM(BlueprintType, DisplayName="Google Analytic Flush Type")
enum class EUGAFlushEventType : uint8
{
	/** Do not flush */
	None,
	/** Only flush this event */
	FlushSingle,
	/** Flush this event and all other cached events */
	FlushAll,
};
