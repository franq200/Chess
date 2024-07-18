#include <algorithm>
#include "figures/Bishop.h"
#include "interface/IRectangleShape.h"

Bishop::Bishop(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size)
{
    m_directions = {Pos(1, 1),Pos(1, -1),Pos(-1, 1),Pos(-1, -1)};
}

bool Bishop::IsMoveAllowedForThisFigure(const Pos& destinationCell) const
{
    Pos pos = GetPosition();
    uint8_t yDifference = std::abs(destinationCell.y - pos.y);
    uint8_t xDifference = std::abs(destinationCell.x - pos.x);
    return xDifference == yDifference && xDifference != 0;
}
