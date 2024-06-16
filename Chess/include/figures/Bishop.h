#pragma once
#include <memory>
#include "Figure.h"

class Bishop : public Figure
{
public:
	Bishop() = default;
	Bishop(const ITexture& texture, Pos pos, Size size, FigureColor color) :Figure(texture, pos, size, color) {}
	bool IsMovePossible(Pos moveCell) override;
private:
};