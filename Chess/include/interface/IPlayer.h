#pragma once
#include "Helper.h"

class IPlayer
{
public:
	virtual ~IPlayer() = default;
	virtual void TryChangeCurrentFigure(Pos mousePos) = 0;
private:
};

