#pragma once
#include <memory>

class IWindow;

class IBoard
{
public:
	virtual ~IBoard() = default;
	virtual void Draw(std::unique_ptr<IWindow> window) = 0;
};

