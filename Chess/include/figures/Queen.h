#pragma once
#include <memory>
#include "Figure.h"

class Queen : public Figure
{
public:
    Queen() = default;
    Queen(const ITexture& texture, Pos pos, Size size, PlayerColor color) :Figure(texture, pos, size, color) {}
    bool IsMovePossible(Pos moveCell) override;
private:
};

