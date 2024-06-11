#pragma once
#include "interface/IMouse.h"
#include "gmock/gmock.h"

class IWindow;

class MouseMock : public IMouse
{
	MOCK_METHOD(Pos, GetPosition, (const std::unique_ptr<IWindow>& window), (override));
	MOCK_METHOD(bool, IsButtonPressed, (Button), (const, override));
};
