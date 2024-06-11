#include "figures/Rook.h"
#include "interface/IRectangleShape.h"

bool Rook::IsMovePossible(Pos moveCell)
{
    Pos pos = GetCellPosFromPixelPos(m_figure->GetPosition());
    uint8_t yDifference = std::abs(moveCell.y - pos.y);
    uint8_t xDifference = std::abs(moveCell.x - pos.x);
    return xDifference == 0 ^ yDifference == 0;
}
