#include <algorithm>
#include "figures/Bishop.h"
#include "interface/IRectangleShape.h"

Bishop::Bishop(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size)
{
    m_directions = {Pos(1, 1),Pos(1, -1),Pos(-1, 1),Pos(-1, -1)};
}

std::shared_ptr<IFigure> Bishop::Clone()
{
    return std::make_shared<Bishop>(*this);
}

bool Bishop::IsMoveAllowedForThisFigure(Pos destinationCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const
{
    Pos pos = GetPosition();
    uint8_t yDifference = std::abs(destinationCell.y - pos.y);
    uint8_t xDifference = std::abs(destinationCell.x - pos.x);
    return xDifference == yDifference && xDifference != 0;
}
