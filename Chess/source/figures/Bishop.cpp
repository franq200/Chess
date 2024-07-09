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

std::vector<Pos> Bishop::GetEveryPossibleMoves(FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const
{
    std::vector<Pos> possibleMoves;
    Pos currentPos = GetCellPosFromPixelPos(m_figure->GetPosition());

    const int boardSize = 8;
    const int directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    for (const auto& direction : directions) {
        for (int i = 1; i < boardSize; ++i) {
            Pos newPos = { currentPos.x + direction[0] * i, currentPos.y + direction[1] * i };
            if (newPos.x >= 0 && newPos.x < boardSize && newPos.y >= 0 && newPos.y < boardSize) {
                if (IsMovePossible(newPos, currentPlayerFigures, opponentPlayerFigures)) {
                    possibleMoves.push_back(newPos);
                }
            }
            else {
                break;  // Move is out of board bounds
            }
        }
    }
    return possibleMoves;
}
