#pragma once
#include <memory>

class IWindow;

class ICell
{
public:
	~ICell() = default;
	virtual void Draw(std::unique_ptr<IWindow> window) = 0;
};

// w IWindow s¹ jakieœ class ...;
