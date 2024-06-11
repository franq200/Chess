#pragma once
#include <memory>
#include "Figure.h"

class Knight : public Figure
{
public:
	Knight() = default;
	Knight(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size) {}
	bool IsMovePossible(Pos moveCell) override;
private:
};