#include "figures/King.h"
#include "interface/IRectangleShape.h"
#include "Helper.h"

bool King::IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures)
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
    return xDifference + yDifference == 1 || (xDifference == 1 && yDifference == 1);
}

std::vector<Pos> King::GetEveryPossibleMoves(FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const
{
    return std::vector<Pos>();
}
