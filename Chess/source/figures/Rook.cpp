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

std::shared_ptr<IFigure> Rook::Clone()
{
    return std::make_shared<Rook>(*this);
}

bool Rook::IsRook() const
{
    return true;
}

bool Rook::IsMoveAllowedForThisFigure(Pos destinationCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const
{
    Pos pos = GetPosition();
    uint8_t yDifference = std::abs(destinationCell.y - pos.y);
    uint8_t xDifference = std::abs(destinationCell.x - pos.x);
    return (xDifference == 0) ^ (yDifference == 0);
}
