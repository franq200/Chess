#include "figures/Rook.h"
#include "interface/IRectangleShape.h"

Rook::Rook(const ITexture& texture, Pos pos, Size size) : Figure(texture, pos, size)
{
    m_directions = {
           Pos(1, 0),
           Pos(0, 1),
           Pos(-1, 0),
           Pos(0, -1)
    };
}

bool Rook::IsMoveAllowedForThisFigure(const Pos& destinationCell) const
{
    Pos pos = GetPosition();
    uint8_t yDifference = std::abs(destinationCell.y - pos.y);
    uint8_t xDifference = std::abs(destinationCell.x - pos.x);
    return (xDifference == 0) ^ (yDifference == 0);
}
