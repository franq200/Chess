#include "figures/Knight.h"
#include "interface/IRectangleShape.h"

Knight::Knight(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size)
{
    m_directions = {
           Pos(2, 1),
           Pos(1, 2),
           Pos(-1, 2),
           Pos(-2, 1),
           Pos(-2, -1),
           Pos(-1, -2),
           Pos(1, -2),
           Pos(2, -1)
    };
}

bool Knight::IsMoveAllowedForThisFigure(const Pos& destinationCell) const
{
    Pos pos = GetPosition();
    uint8_t yDifference = std::abs(destinationCell.y - pos.y);
    uint8_t xDifference = std::abs(destinationCell.x - pos.x);
    return xDifference + yDifference == 3 && xDifference != 0 && yDifference != 0;
}

std::vector<Pos> Knight::GetMovePath(Pos destinationCell, Pos currentPos) const
{
    return { destinationCell };
}
