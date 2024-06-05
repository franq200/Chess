#pragma once
#include <memory>
#include "Figure.h"

class Pawn : public Figure
{
public:
	Pawn() = default;
	Pawn(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size) {}
private:
};

