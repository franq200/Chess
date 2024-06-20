#pragma once
#include <memory>
#include <vector>
#include "Helper.h"

class IFigure;

class IPlayer
{
public:
	virtual ~IPlayer() = default;
	virtual void AddFigures(std::vector<std::shared_ptr<IFigure>>& figures) = 0;
	virtual void TryChangeCurrentFigure(Pos mousePos) = 0;
	virtual bool HasFigure(const std::shared_ptr<IFigure>& figure) const = 0;
private:
};

