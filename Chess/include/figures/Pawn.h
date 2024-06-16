#pragma once
#include <memory>
#include "Figure.h"

class Pawn : public Figure
{
public:
	Pawn() = default;
	Pawn(const ITexture& texture, Pos pos, Size size, FigureColor color) :Figure(texture, pos, size, color) {}
	bool IsMovePossible(Pos moveCell) override;
private:
};

