#pragma once
#include "Helper.h"

class IWindow;

class IFigure
{
public:
	virtual ~IFigure() = default;
	virtual bool IsInRange(Pos mousePos) = 0;
	virtual void SetOutlineThickness(int thickness) = 0;
	virtual void SetOutlineColor(Color color) = 0;
	virtual void Draw(std::unique_ptr<IWindow>& window) = 0;
};

