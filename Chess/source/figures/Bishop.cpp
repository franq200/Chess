#include <algorithm>
#include "figures/Bishop.h"
#include "interface/IRectangleShape.h"

Bishop::Bishop(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size)
{
    m_directions = {Pos(1, 1),Pos(1, -1),Pos(-1, 1),Pos(-1, -1)};
}

bool Bishop::IsMoveAllowedForThisFigure(uint8_t xDifference, uint8_t yDifference) const
{
    return xDifference == yDifference && xDifference != 0;
}
