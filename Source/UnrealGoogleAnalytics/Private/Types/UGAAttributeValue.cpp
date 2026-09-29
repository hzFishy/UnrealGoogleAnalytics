// By hzFishy - 2026 - Do whatever you want with it.


#include "Types/UGAAttributeValue.h"


FUGAAttributeValue::FUGAAttributeValue()
{}

FUGAAttributeValue::FUGAAttributeValue(bool InValue):
	Value(TInPlaceType<bool>(), InValue)
{}

FUGAAttributeValue::FUGAAttributeValue(int32 InValue):
	Value(TInPlaceType<int32>(), InValue)
{}

FUGAAttributeValue::FUGAAttributeValue(float InValue):
	Value(TInPlaceType<float>(), InValue)
{}

FUGAAttributeValue::FUGAAttributeValue(FString InValue):
	Value(TInPlaceType<FString>(), InValue)
{}

FUGAAttributeValue::FUGAAttributeValue(FName InValue):
	Value(TInPlaceType<FName>(), InValue)
{}


bool FUGAAttributeValue::GetAsBool() const
{
	return Value.Get<bool>();
}

bool FUGAAttributeValue::GetAsBool_Checked() const
{
	check(Value.IsType<bool>());
	return Value.Get<bool>();
}

const bool* FUGAAttributeValue::TryGetAsBool() const
{
	return Value.TryGet<bool>();
}


int32 FUGAAttributeValue::GetAsInt() const
{
	return Value.Get<int32>();
}

int32 FUGAAttributeValue::GetAsInt_Checked() const
{
	check(Value.IsType<int32>());
	return Value.Get<int32>();
}

const int32* FUGAAttributeValue::TryGetAsInt() const
{
	return Value.TryGet<int32>();
}

float FUGAAttributeValue::GetAsFloat() const
{
	return Value.Get<float>();
}

float FUGAAttributeValue::GetAsFloat_Checked() const
{
	check(Value.IsType<float>());
	return Value.Get<float>();
}

const float* FUGAAttributeValue::TryGetAsFloat() const
{
	return Value.TryGet<float>();
}


FString FUGAAttributeValue::GetAsString() const
{
	return Value.Get<FString>();
}

FString FUGAAttributeValue::GetAsString_Checked() const
{
	check(Value.IsType<FString>());
	return Value.Get<FString>();
}

const FString* FUGAAttributeValue::TryGetAsString() const
{
	return Value.TryGet<FString>();
}


FName FUGAAttributeValue::GetAsName() const
{
	return Value.Get<FName>();
}

FName FUGAAttributeValue::GetAsName_Checked() const
{
	check(Value.IsType<FName>());
	return Value.Get<FName>();
}

const FName* FUGAAttributeValue::TryGetAsName() const
{
	return Value.TryGet<FName>();
}

FString FUGAAttributeValue::ConvertToString() const
{
	if (Value.IsType<bool>())
	{
		return Value.Get<bool>() ? FString("true") : FString("false");
	}
	else if (Value.IsType<int32>())
	{
		return FString::FromInt(Value.Get<int32>());
	}
	else if (Value.IsType<float>())
	{
		return FString::Printf(TEXT("%f"), Value.Get<float>());
	}
	else if (Value.IsType<FString>())
	{
		return Value.Get<FString>();
	}
	else if (Value.IsType<FName>())
	{
		return Value.Get<FName>().ToString();
	}
	
	return FString("");
}
