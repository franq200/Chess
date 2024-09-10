#pragma once
#include <cstdint>
#include "Helper.h"

class IWindow;
using IWindowPtr = std::unique_ptr<IWindow>;

class IMouse
{
public:
	enum class Button : uint8_t
	{
		Left = 0,
		Right
	};
	virtual bool IsButtonPressed(Button button) const = 0;
	virtual Pos GetCellPosition(const IWindowPtr& window) = 0;
	virtual Pos GetPixelPosition(const IWindowPtr& window) = 0;
	virtual bool IsMouseInWindow(const IWindowPtr& window) const = 0;
};

