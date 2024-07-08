#pragma once
#include <memory>
#include "Figure.h"

class Rook: public Figure
{
public:
	Rook() = default;
	Rook(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size) {}
	bool IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures) override;
private:
};