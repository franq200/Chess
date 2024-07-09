#include "figures/Knight.h"
#include "interface/IRectangleShape.h"

Knight::Knight(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size)
{
    m_directions = {
           Pos(2, 1),
           Pos(1, 2),
           Pos(-1, 2),
           Pos(-2, 1),
           Pos(-2, -1),
           Pos(-1, -2),
           Pos(1, -2),
           Pos(2, -1)
    };
}

bool Knight::IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const
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