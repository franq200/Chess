#pragma once
#include <memory>
#include "Figure.h"

class Rook: public Figure
{
public:
	Rook() = default;
	Rook(const ITexture& texture, Pos pos, Size size, FigureColor color) :Figure(texture, pos, size, color) {}
	bool IsMovePossible(Pos moveCell) override;
private:
};