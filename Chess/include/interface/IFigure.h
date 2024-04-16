#pragma once
#include "Helper.h"

class IFigure
{
public:
	~IFigure() = default;
	virtual bool IsInRange(Pos mousePos) = 0;
};

