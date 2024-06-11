#include "figures/King.h"
#include "interface/IRectangleShape.h"
#include "Helper.h"

bool King::IsMovePossible(Pos moveCell)
{
    Pos pos = GetCellPosFromPixelPos(m_figure->GetPosition());
    uint8_t yDifference = std::abs(moveCell.y - pos.y);
    uint8_t xDifference = std::abs(moveCell.x - pos.x);
    return xDifference + yDifference == 1;
}
