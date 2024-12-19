#include "figures/Pawn.h"
#include "interface/IRectangleShape.h"

Pawn::Pawn(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size)
{
    if (m_dir == MoveDirection::unknown) {
        SetDirectionBasedOnStartingPos();
    }
}


MoveExecutorPtr Pawn::GenerateExecutor(Pos moveCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const
{
    Pos pos = GetPosition();
    int yDifference = moveCell.y - pos.y;
    int xDifference = moveCell.x - pos.x;

    if (IsCollisionWithCurrentPlayer({ moveCell }, currentPlayerFigures)) {
        return nullptr;
    }

    if (yDifference == static_cast<int8_t>(m_dir) && xDifference == 0) {
        for (auto figure : opponentPlayerFigures) {
            Pos figurePos = figure->GetPosition();
            if (figurePos.x == moveCell.x && figurePos.y == moveCell.y) {
                return nullptr;
            }
        }
        return std::make_unique<NormalMoveExecutor>(moveCell);
    }

    if (pos.y == m_startingHeight && yDifference == 2 * static_cast<int8_t>(m_dir) && xDifference == 0) {
        if (IsCollisionWithAnyPlayer({ moveCell }, currentPlayerFigures, opponentPlayerFigures)) {
            return nullptr;
        }
        return std::make_unique<NormalMoveExecutor>(moveCell);
    }

    if (yDifference == static_cast<int8_t>(m_dir) && std::abs(xDifference) == 1) {
        if (IsFigureTaking(moveCell, opponentPlayerFigures)) {
            return std::make_unique<TakingMoveExecutor>(moveCell);
        }
    }

    return nullptr;
}

std::shared_ptr<IFigure> Pawn::Clone()
{
    return std::make_shared<Pawn>(*this);
}

bool Pawn::IsPawn() const
{
    return true;
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

bool Pawn::IsMoveAllowedForThisFigure(Pos destinationCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const
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