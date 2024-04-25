#pragma once
#include <memory>

class IWindow;

class ICell
{
public:
	virtual ~ICell() = default;
	virtual void Draw(std::unique_ptr<IWindow> window) = 0;
};
