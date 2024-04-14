#pragma once
#include <memory>

class Window;

class IBoard
{
public:
	~IBoard() = default;
	virtual void Draw(std::unique_ptr<Window> window) = 0;
};

