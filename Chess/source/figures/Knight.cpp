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

bool Knight::IsMoveAllowedForThisFigure(uint8_t xDifference, uint8_t yDifference) const
{
    return xDifference + yDifference == 3 && xDifference != 0 && yDifference != 0;
}

std::vector<Pos> Knight::GetMovePath(Pos destinationCell, Pos currentPos) const
{
    return { destinationCell };
}
