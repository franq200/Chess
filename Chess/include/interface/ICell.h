#pragma once
#include <memory>
#include "Helper.h"

class IWindow;
class IFigure;

class ICell
{
public:
	virtual ~ICell() = default;
	virtual void Draw(std::unique_ptr<IWindow>& window) = 0;
	virtual void SetFillColor(Color color) = 0;
	virtual void SetPosition(Pos pos) = 0;
	virtual void SetSize(Size size) = 0;
	virtual void AddFigure(std::shared_ptr<IFigure> figure) = 0;
};
