#include "figures/Queen.h"
#include "interface/IRectangleShape.h"

Queen::Queen(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size)
{
    m_directions = {
            Pos(1, 0),
            Pos(0, 1),
            Pos(-1, 0),
            Pos(0, -1),
            Pos(1, 1),
            Pos(1, -1),
            Pos(-1, 1),
            Pos(-1, -1)
    };
}

bool Queen::IsMoveAllowedForThisFigure(uint8_t xDifference, uint8_t yDifference) const
{
    return (xDifference == yDifference && xDifference != 0) || ((xDifference == 0) ^ (yDifference == 0));
}
