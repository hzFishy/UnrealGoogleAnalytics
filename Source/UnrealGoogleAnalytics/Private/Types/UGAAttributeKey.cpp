// By hzFishy - 2026 - Do whatever you want with it.


#include "Types/UGAAttributeKey.h"


FUGAAttributeKey::FUGAAttributeKey()
{}

FUGAAttributeKey::FUGAAttributeKey(FName InKeyName):
	KeyName(InKeyName)
{}

bool FUGAAttributeKey::operator==(const FUGAAttributeKey& OtherKey) const
{
	return KeyName == OtherKey.KeyName;
}
