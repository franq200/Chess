#pragma once
#include <memory>
#include "Figure.h"

using Positions = std::vector<Pos>;

class Bishop : public Figure
{
public:
	Bishop() = default;
	Bishop(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size) {}
	bool IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) override;
};