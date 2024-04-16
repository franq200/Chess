#pragma once
#include <memory>
#include "Window.h"

class IBoard
{
public:
	~IBoard() = default;
	virtual void Draw(std::unique_ptr<Window> window) = 0;
};

