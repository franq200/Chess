#pragma once
#include <memory>
#include "IWindow.h"

class ICell
{
public:
	~ICell() = default;
	virtual void Draw(std::unique_ptr<IWindow> window) = 0;
};

