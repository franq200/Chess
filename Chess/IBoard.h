#pragma once
#include "IWindow.h"
#include <memory>

class IBoard
{
public:
	~IBoard() = default;
	virtual void Draw(std::unique_ptr<IWindow> window) = 0;
};

