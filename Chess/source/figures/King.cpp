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

std::shared_ptr<IFigure> King::Clone() const
{
    return std::make_shared<King>(*this);
}

bool King::IsMoveAllowedForThisFigure(const Pos& destinationCell) const
{
    Pos pos = GetPosition();
    uint8_t yDifference = std::abs(destinationCell.y - pos.y);
    uint8_t xDifference = std::abs(destinationCell.x - pos.x);
    return xDifference + yDifference == 1 || (xDifference == 1 && yDifference == 1);
}
