#pragma once
#include <cstdint>
#include "Helper.h"

class IMouse
{
public:
	enum class Button : uint8_t
	{
		Left = 0,
		Right
	};
	virtual bool IsButtonPressed(Button button) const = 0;
	virtual Pos GetPosition() = 0;
};

