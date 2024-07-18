#pragma once
#include <memory>
#include "Figure.h"

class Rook: public Figure
{
public:
	Rook() = default;
	Rook(const ITexture& texture, Pos pos, Size size);
protected:
	bool IsMoveAllowedForThisFigure(const Pos& destinationCell) const override;
};