#pragma once
#include <memory>

class Window;

class ICell
{
public:
	~ICell() = default;
	virtual void Draw(std::unique_ptr<Window> window) = 0;
};

