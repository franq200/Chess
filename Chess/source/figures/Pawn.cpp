#include "figures/Pawn.h"
#include "interface/IRectangleShape.h"

Pawn::Pawn(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size)
{
    if (m_dir == MoveDirection::unknown) {
        SetDirectionBasedOnStartingPos();
    }
}


bool Pawn::IsMoveAllowed(Pos moveCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const
{
    Pos pos = GetPosition();
    int yDifference = moveCell.y - pos.y;
    int xDifference = moveCell.x - pos.x;

    if (IsCollisionWithCurrentPlayer({ moveCell }, currentPlayerFigures)) {
        return false;
    }

    if (yDifference == static_cast<int8_t>(m_dir) && xDifference == 0) {
        for (auto figure : opponentPlayerFigures) {
            Pos figurePos = figure->GetPosition();
            if (figurePos.x == moveCell.x && figurePos.y == moveCell.y) {
                return false;
            }
        }
        return true;
    }

    if (pos.y == m_startingHeight && yDifference == 2 * static_cast<int8_t>(m_dir) && xDifference == 0) {
        if (IsCollisionWithAnyPlayer({ moveCell }, currentPlayerFigures, opponentPlayerFigures)) {
            return false;
        }
        return true;
    }

    if (yDifference == static_cast<int8_t>(m_dir) && std::abs(xDifference) == 1) {
        if (IsFigureTaking(moveCell, opponentPlayerFigures)) {
            return true;
        }
    }

    return false;
}

void Pawn::SetDirectionBasedOnStartingPos() {
    if (GetPosition().y == 6) {
        m_directions = {
            Pos(0, -1),
            Pos(0, 2 * -1),
            Pos(-1, -1),
            Pos(1, -1)
        };
        m_dir = MoveDirection::up;
        m_startingHeight = 6;
    }
    else {
        m_directions = {
           Pos(0, 1),
           Pos(0, 2 * 1),
           Pos(-1, 1),
           Pos(1, 1)
        };
        m_dir = MoveDirection::down;
        m_startingHeight = 1;
    }
}

bool Pawn::IsMoveAllowedForThisFigure(const Pos& destinationCell) const
{
    return false;
}

bool Pawn::IsPromotion(Pos moveCell) {
    if ((m_dir == MoveDirection::up && moveCell.y == 0) ||
        (m_dir == MoveDirection::down && moveCell.y == 7)) {
        return true;
    }
    return false;
}