#pragma once
#include "Helper.h"

class IPlayer
{
public:
	~IPlayer() = default;
	virtual void TryChangeCurrentFigure(Pos mousePos) = 0;
private:
};

