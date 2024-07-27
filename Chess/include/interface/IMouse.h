#pragma once
#include <cstdint>
#include "Helper.h"

class IWindow;

class IMouse
{
public:
	enum class Button : uint8_t
	{
		Left = 0,
		Right
	};
	virtual bool IsButtonPressed(Button button) const = 0;
	virtual Pos GetCellPosition(const std::unique_ptr<IWindow>& window) = 0;
	virtual Pos GetPixelPosition(const std::unique_ptr<IWindow>& window) = 0;
	virtual bool IsMouseInWindow(const std::unique_ptr<IWindow>& window) const = 0;
};

