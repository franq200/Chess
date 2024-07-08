#include "figures/Pawn.h"
#include "interface/IRectangleShape.h"

bool Pawn::IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures)
{
    if (m_dir == MoveDirection::unknown)
    {
        SetDirectionBasedOnStartingPos();
    }
    Pos pos = GetCellPosFromPixelPos(m_figure->GetPosition());
    int yDifference = moveCell.y - pos.y;
    int xDifference = moveCell.x - pos.x;
    for (auto playerFigure : currentPlayerFigures)
    {
        Pos playerFigurePos = playerFigure->GetPosition();
        if (playerFigurePos.x == moveCell.x && playerFigurePos.y == moveCell.y)
        {
            return false;
        }
    }
    return ((yDifference == static_cast<int8_t>(m_dir)) || (pos.y == m_startingHeight && yDifference == 2*static_cast<int8_t>(m_dir))) && xDifference == 0;
}
void Pawn::SetDirectionBasedOnStartingPos()
{
    if (GetPosition().y == 6)
    {
        m_dir = MoveDirection::up;
        m_startingHeight = 6;
    }
    else
    {
        m_dir = MoveDirection::down;
        m_startingHeight = 1;
    }
}
