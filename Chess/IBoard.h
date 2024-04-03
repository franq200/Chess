#pragma once
#include <memory>
#include "IWindow.h"

class IBoard
{
public:
	~IBoard() = default;
	virtual void Draw(std::unique_ptr<IWindow> window) = 0;
};

