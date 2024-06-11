#include "figures/Pawn.h"
#include "interface/IRectangleShape.h"

bool Pawn::IsMovePossible(Pos moveCell)
{
    Pos pos = GetCellPosFromPixelPos(m_figure->GetPosition());
    int yDifference = moveCell.y - pos.y;
    int xDifference = moveCell.x - pos.x;
    return yDifference == -1 && xDifference == 0;
}
