#pragma once
#include <memory>
#include <vector>
#include "Helper.h"

class IFigure;
using FiguresVector = std::vector<std::shared_ptr<IFigure>>;

class IPlayer
{
public:
	virtual ~IPlayer() = default;
	virtual void AddFigures(FiguresVector& figures, std::shared_ptr<IFigure>) = 0;
	virtual void TryChangeCurrentFigure(Pos mousePos) = 0;
	virtual bool HasFigure(const std::shared_ptr<IFigure>& figure) const = 0;
	virtual const FiguresVector& GetFigures() const = 0;
	virtual bool IsAnyMovePossible(const FiguresVector& opponentPlayerFigures) const = 0;
	virtual void RemoveFigure(Pos mouseCell) = 0;
private:
};

