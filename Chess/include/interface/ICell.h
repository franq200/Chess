#pragma once
#include <memory>
#include "Window.h"

class ICell
{
public:
	~ICell() = default;
	virtual void Draw(std::unique_ptr<Window> window) = 0;
};

//window to nie IWindow
// w IWindow s¹ jakieœ class ...;
