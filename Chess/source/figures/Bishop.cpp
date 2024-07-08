#include <algorithm>
#include "figures/Bishop.h"
#include "interface/IRectangleShape.h"

bool Bishop::IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures)
{
    Pos pos = GetCellPosFromPixelPos(m_figure->GetPosition());
    uint8_t yDifference = std::abs(moveCell.y - pos.y);
    uint8_t xDifference = std::abs(moveCell.x - pos.x);
    std::vector<Pos> positionsToPass;
    int8_t xDifferenceRaw = moveCell.x - pos.x;
    int8_t yDifferenceRaw = moveCell.y - pos.y;
    positionsToPass = HandleDiagonalMovement(xDifferenceRaw, yDifferenceRaw, pos, moveCell);
    for (auto playerFigure : currentPlayerFigures)
    {
        Pos playerFigurePos = playerFigure->GetPosition();
        if (std::find(positionsToPass.begin(), positionsToPass.end(), playerFigurePos) != positionsToPass.end())
        {
            return false;
        }
    }
    return xDifference == yDifference && xDifference != 0;
}