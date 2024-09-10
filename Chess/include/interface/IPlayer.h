#pragma once
#include <memory>
#include <vector>
#include "Helper.h"

class IFigure;
using IFigurePtr = std::shared_ptr<IFigure>;
using FiguresVector = std::vector<IFigurePtr>;

class IPlayer
{
public:
	virtual ~IPlayer() = default;
	virtual void AddFigures(FiguresVector& figures, IFigurePtr) = 0;
	virtual void TryChangeCurrentFigure(Pos mousePos) = 0;
	virtual bool HasFigure(const IFigurePtr& figure) const = 0;
	virtual const FiguresVector& GetFigures() const = 0;
	virtual bool IsAnyMovePossible(const FiguresVector& opponentPlayerFigures) const = 0;
	virtual void RemoveFigure(Pos mouseCell) = 0;
private:
};

