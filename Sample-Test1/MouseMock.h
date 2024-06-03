#pragma once
#include "interface/IMouse.h"
#include "gmock/gmock.h"

class MouseMock : public IMouse
{
	MOCK_METHOD(Pos, GetPosition, (), (override));
	MOCK_METHOD(bool, IsButtonPressed, (Button), (const, override));
};
