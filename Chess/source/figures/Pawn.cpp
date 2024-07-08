#include "figures/Pawn.h"
#include "interface/IRectangleShape.h"

/*
bool Pawn::IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures)
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
*/

bool Pawn::IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) {
    if (m_dir == MoveDirection::unknown) {
        SetDirectionBasedOnStartingPos();
    }
    Pos pos = GetCellPosFromPixelPos(m_figure->GetPosition());
    int yDifference = moveCell.y - pos.y;
    int xDifference = moveCell.x - pos.x;

    // Check if moving to a cell occupied by the current player's figure
    for (auto playerFigure : currentPlayerFigures) {
        Pos playerFigurePos = playerFigure->GetPosition();
        if (playerFigurePos.x == moveCell.x && playerFigurePos.y == moveCell.y) {
            return false;
        }
    }

    // Check for normal move (one or two squares forward)
    if ((yDifference == static_cast<int8_t>(m_dir)) && xDifference == 0) {
        // Check if the move cell is occupied by any figure
        for (auto figure : opponentPlayerFigures) {
            Pos figurePos = figure->GetPosition();
            if (figurePos.x == moveCell.x && figurePos.y == moveCell.y) {
                return false;
            }
        }
        return true;
    }
    if ((pos.y == m_startingHeight && yDifference == 2 * static_cast<int8_t>(m_dir)) && xDifference == 0) {
        // Check if the intermediate cell and the move cell are occupied by any figure
        Pos intermediatePos = { pos.x, static_cast<uint16_t>(pos.y + static_cast<int8_t>(m_dir)) };
        for (auto figure : currentPlayerFigures) {
            Pos figurePos = figure->GetPosition();
            if ((figurePos.x == moveCell.x && figurePos.y == moveCell.y) ||
                (figurePos.x == intermediatePos.x && figurePos.y == intermediatePos.y)) {
                return false;
            }
        }
        for (auto figure : opponentPlayerFigures) {
            Pos figurePos = figure->GetPosition();
            if ((figurePos.x == moveCell.x && figurePos.y == moveCell.y) ||
                (figurePos.x == intermediatePos.x && figurePos.y == intermediatePos.y)) {
                return false;
            }
        }
        return true;
    }

    // Check for capture
    if ((yDifference == static_cast<int8_t>(m_dir)) && (xDifference == 1 || xDifference == -1)) {
        for (auto figure : opponentPlayerFigures) {
            Pos figurePos = figure->GetPosition();
            if (figurePos.x == moveCell.x && figurePos.y == moveCell.y) {
                return true;
            }
        }
    }

    return false;
}

void Pawn::SetDirectionBasedOnStartingPos() {
    if (GetPosition().y == 6) {
        m_dir = MoveDirection::up;
        m_startingHeight = 6;
    }
    else {
        m_dir = MoveDirection::down;
        m_startingHeight = 1;
    }
}

bool Pawn::IsPromotion(Pos moveCell) {
    if ((m_dir == MoveDirection::up && moveCell.y == 0) ||
        (m_dir == MoveDirection::down && moveCell.y == 7)) {
        return true;
    }
    return false;
}