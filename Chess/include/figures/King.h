#pragma once
#include <memory>
#include "Figure.h"

class King : public Figure
{
public:
	King() = default;
	King(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size) {}
	bool IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) override;
private:
};

