#pragma once
#include <memory>
#include "Figure.h"

class Queen : public Figure
{
public:
    Queen() = default;
    Queen(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size) {}
private:
};

