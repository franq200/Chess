#pragma once
#include <vector>
#include "Helper.h"

class IWindow;

class IFigure
{
public:
	using FiguresVector = std::vector<std::shared_ptr<IFigure>>;
	virtual ~IFigure() = default;
	virtual bool IsInRange(Pos mousePos) = 0;
	virtual void SetOutlineThickness(int thickness) = 0;
	virtual void SetOutlineColor(Color color) = 0;
	virtual void Draw(std::unique_ptr<IWindow>& window) = 0;
	virtual void SetPosition(Pos pos) = 0;
	virtual Pos GetPosition() const = 0;
	virtual bool IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const = 0;
	virtual std::vector<Pos> GetEveryPossibleMoves(FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const = 0;
};

