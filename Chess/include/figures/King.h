#pragma once
#include <memory>
#include "Figure.h"

class King : public Figure
{
public:
	King() = default;
	King(const ITexture& texture, Pos pos, Size size, FigureColor color) :Figure(texture, pos, size, color) {}
	bool IsMovePossible(Pos moveCell) override;
private:
};

