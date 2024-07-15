#include "figures/King.h"
#include "interface/IRectangleShape.h"
#include "Helper.h"

King::King(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size)
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

bool King::IsMoveAllowedForThisFigure(uint8_t xDifference, uint8_t yDifference) const
{
    return xDifference + yDifference == 1 || (xDifference == 1 && yDifference == 1);
}
