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
	virtual void AddFigures(FiguresVector& figures) = 0;
	virtual void TryChangeCurrentFigure(Pos mousePos) = 0;
	virtual bool HasFigure(const std::shared_ptr<IFigure>& figure) const = 0;
	virtual const FiguresVector& GetFigures() const = 0;
	virtual bool IsAnyMovePossible() const = 0;
private:
};

