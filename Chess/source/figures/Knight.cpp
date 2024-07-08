#include "figures/Knight.h"
#include "interface/IRectangleShape.h"

bool Knight::IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures)
{
    Pos pos = GetCellPosFromPixelPos(m_figure->GetPosition());
    uint8_t yDifference = std::abs(moveCell.y - pos.y);
    uint8_t xDifference = std::abs(moveCell.x - pos.x);
    for (auto playerFigure : currentPlayerFigures)
    {
        Pos playerFigurePos = playerFigure->GetPosition();
        if (playerFigurePos.x == moveCell.x && playerFigurePos.y == moveCell.y)
        {
            return false;
        }
    }
    return xDifference + yDifference == 3 && xDifference != 0 && yDifference != 0;
}
