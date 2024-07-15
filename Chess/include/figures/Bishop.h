#pragma once
#include <memory>
#include "Figure.h"

using Positions = std::vector<Pos>;

class Bishop : public Figure
{
public:
	Bishop() = default;
	Bishop(const ITexture& texture, Pos pos, Size size);
protected:
	bool IsMoveAllowedForThisFigure(uint8_t yDifference, uint8_t xDifference) const;
};