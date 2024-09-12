#pragma once
#include "interface/IMouse.h"
#include "gmock/gmock.h"

class IWindow;

class MouseMock : public IMouse
{
public:
	MOCK_METHOD(bool, IsButtonPressed, (Button button), (const, override));
	MOCK_METHOD(Pos, GetCellPosition, (const std::unique_ptr<IWindow>& window), (override));
	MOCK_METHOD(Pos, GetPixelPosition, (const std::unique_ptr<IWindow>& window), (override));
	MOCK_METHOD(bool, IsMouseInWindow, (const std::unique_ptr<IWindow>& window), (const, override));
};
