#pragma once
#include <memory>
#include <vector>
#include "Helper.h"
#include "Figure.h"

class Knight : public Figure
{
public:
	Knight() = default;
	Knight(const ITexture& texture, Pos pos, Size size);
protected:
	bool IsMoveAllowedForThisFigure(uint8_t yDifference, uint8_t xDifference) const;
	std::vector<Pos> GetMovePath(Pos destinationCell, Pos currentPos) const;
};