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

std::shared_ptr<IFigure> Queen::Clone() const
{
    return std::make_shared<Queen>(*this);
}

bool Queen::IsMoveAllowedForThisFigure(const Pos& destinationCell) const
{
    Pos pos = GetPosition();
    uint8_t yDifference = std::abs(destinationCell.y - pos.y);
    uint8_t xDifference = std::abs(destinationCell.x - pos.x);
    return (xDifference == yDifference && xDifference != 0) || ((xDifference == 0) ^ (yDifference == 0));
}
