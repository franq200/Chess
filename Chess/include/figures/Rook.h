#pragma once
#include <memory>
#include "Figure.h"

class Rook: public Figure
{
public:
	Rook() = default;
	Rook(const ITexture& texture, Pos pos, Size size);
protected:
	bool IsMoveAllowedForThisFigure(uint8_t yDifference, uint8_t xDifference) const;
};