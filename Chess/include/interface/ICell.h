#pragma once
#include <memory>
#include <vector>
#include "Helper.h"

class IPlayer;
using IPlayerPtr = std::unique_ptr<IPlayer>;
class IWindow;
using IWindowPtr = std::unique_ptr<IWindow>;
class IFigure;
using IFigurePtr = std::shared_ptr<IFigure>;

using FiguresVector = std::vector<IFigurePtr>;

class ICell
{
public:
	virtual ~ICell() = default;
	virtual void SetFillColor(Color color) = 0;
	virtual void SetPosition(Pos pos) = 0;
	virtual void SetSize(Size size) = 0;
	virtual void SetFigure(IFigurePtr figure) = 0;
	virtual void RemoveFigure() = 0;
	virtual IFigurePtr GetFigure() const = 0;
	virtual bool IsOccupiedByPlayer(const IPlayerPtr& currentColor) const = 0;
	virtual void Highlight() = 0;
	virtual void HighlightAsTaking() = 0;
	virtual void RemoveHighlight() = 0;
	virtual void DrawCells(IWindowPtr& window) = 0;
	virtual void DrawFigures(IWindowPtr& window) = 0;
	virtual void DrawHighlights(IWindowPtr& window) = 0;
};
