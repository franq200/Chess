#pragma once
#include <memory>
#include "Helper.h"

class IPlayer;
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
	virtual void SetFigure(std::shared_ptr<IFigure> figure) = 0;
	virtual void RemoveFigure() = 0;
	virtual std::shared_ptr<IFigure> GetFigure() const = 0;
	virtual bool IsOccupiedByPlayer(const std::unique_ptr<IPlayer>& currentColor) const = 0;
	virtual bool IsMovePossible(Pos moveCell) = 0;
};
