#include "figures/Figure.h"
#include "interface/IRectangleShape.h"
#include "interface/ITexture.h"
#include "Helper.h"
#include "RectangleShape.h"
#include "interface/IWindow.h"

Figure::Figure(const ITexture& texture, Pos pos, Size size)
{
    m_figure = std::make_unique<RectangleShape>();
    m_figure->SetOutlineColor(Color(50, 50, 150));
    m_figure->SetTexture(texture);
    m_figure->SetPosition(GetPixelPosFromCellPos(pos));
    m_figure->SetSize(size);
}

bool Figure::IsInRange(Pos mousePos)
{
    Pos pos = m_figure->GetPosition();
    bool isInXRange = mousePos.x - pos.x <= size::cellSizeXPix && mousePos.x - pos.x >= 0;
    bool isInYRange = mousePos.y - pos.y <= size::cellSizeYPix && mousePos.y - pos.y >= 0;
    return isInXRange && isInYRange;
}

void Figure::SetOutlineThickness(int thickness)
{
    m_figure->SetOutlineThickness(thickness);
}

void Figure::SetOutlineColor(Color color)
{
    m_figure->SetOutlineColor(color);
}

void Figure::Draw(IWindowPtr& window)
{
    window->Draw(*m_figure);
}

void Figure::SetPosition(Pos pos)
{
    m_figure->SetPosition(pos);
}

Pos Figure::GetPosition() const
{
    return GetCellPosFromPixelPos(m_figure->GetPosition());
}

Pos Figure::GetPixelPosition() const
{
    return m_figure->GetPosition();
}

bool Figure::IsMoveAllowed(Pos destinationCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const
{
    if (IsMoveAllowedForThisFigure(destinationCell))
    {
        if (IsCollisionWithAnyPlayer(destinationCell, currentPlayerFigures, opponentPlayerFigures))
        {
            return false;
        }
        return true;
    }
    return false;
}

std::vector<Pos> Figure::CalculatePossibleMoves(const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures)
{
    std::vector<Pos> possibleMoves;
    Pos currentPos = GetPosition();
    
    for (const auto& direction : m_directions)
    {
        for (int i = 1; i < 8; ++i)
        {
            Pos newPos = {
                static_cast<int16_t>(currentPos.x + static_cast<int>(direction.x) * static_cast<int>(i)),
                static_cast<int16_t>(currentPos.y + static_cast<int>(direction.y) * static_cast<int>(i))
                };
            if (newPos.x >= 0 && newPos.x < 8 && newPos.y >= 0 && newPos.y < 8) 
            {
                if (IsMoveAllowed(newPos, currentPlayerFigures, opponentPlayerFigures)) 
                {
                    possibleMoves.push_back(newPos);
                }
            }
            else
            {
                break;
            }
        }
    }
    m_possibleMoves = possibleMoves;
    return possibleMoves;
}

void Figure::ChangeTempPos(const Pos& tempPos)
{
    m_figure->SetTempPos(tempPos);
}

void Figure::SetCurrentPos()
{
    m_figure->SetCurrentPos();
}

Pos Figure::GetPixelTempPosition() const
{
    return m_figure->GetPixelTempPosition();
}

bool Figure::IsInPossibleMoves(const Pos& destinationPos) const
{
    return std::find(m_possibleMoves.begin(), m_possibleMoves.end(), destinationPos) != m_possibleMoves.end();
}

Pos Figure::GetCellTempPosition() const
{
    return m_figure->GetCellTempPosition();
}

void Figure::OnAnimation()
{
    m_figure->OnAnimation();
}

std::vector<Pos> Figure::GetMovePath(Pos destinationCell, Pos currentPos) const
{
    int8_t xDifferenceRaw = destinationCell.x - currentPos.x;
    int8_t yDifferenceRaw = destinationCell.y - currentPos.y;
    if (xDifferenceRaw != 0 && yDifferenceRaw != 0)
    {
        return HandleDiagonalMovement(xDifferenceRaw, yDifferenceRaw, currentPos, destinationCell);
    }
    else
    {
        return HandleBasicMovement(xDifferenceRaw, yDifferenceRaw, currentPos, destinationCell);
    }
}

bool Figure::IsCollisionWithCurrentPlayer(const std::vector<Pos>& movePath, const FiguresVector& currentPlayerFigures) const
{
    for (auto playerFigure : currentPlayerFigures)
    {
        Pos playerFigurePos = playerFigure->GetPosition();
        if (std::find(movePath.begin(), movePath.end(), playerFigurePos) != movePath.end())
        {
            return true;
        }
    }
    return false;
}

bool Figure::IsCollisionWithOpponent(const std::vector<Pos>& movePath, const FiguresVector& opponentPlayerFigures) const
{
    IFigurePtr collisionFigure = nullptr;
    for (auto opponentFigure : opponentPlayerFigures)
    {
        Pos opponentFigurePos = opponentFigure->GetPosition();
        if (std::find(movePath.begin(), movePath.end(), opponentFigurePos) != movePath.end())
        {
            if (collisionFigure != nullptr)
            {
                return true;
            }
            collisionFigure = opponentFigure;
        }
    }
    const bool isCollision = !movePath.empty() && collisionFigure != nullptr && collisionFigure->GetPosition() != movePath.back();
    return isCollision;
}

bool Figure::IsCollisionWithAnyPlayer(Pos destinationCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const
{
    Positions movePath = GetMovePath(destinationCell, GetPosition());
    return IsCollisionWithCurrentPlayer(movePath, currentPlayerFigures) || IsCollisionWithOpponent(movePath, opponentPlayerFigures);
}

bool Figure::IsFigureTaking(Pos destinationCell, const FiguresVector& opponentPlayerFigures) const
{
    for (auto playerFigure : opponentPlayerFigures)
    {
        const Pos& opponentFigurePos = playerFigure->GetPosition();
        if (destinationCell == opponentFigurePos)
        {
            return true;
        }
    }
    return false;
}

Positions Figure::GetTopPath(const Pos pos, const Pos destinationCell) const
{
    Positions positions;
    for (int i = 1; pos.y - i >= destinationCell.y; ++i)
    {
        positions.push_back(Pos(pos.x, pos.y - i));
    }
    return positions;
}

Positions Figure::GetDownPath(const Pos pos, const Pos destinationCell) const
{
    Positions positions;
    for (int i = 1; i + pos.y <= destinationCell.y; ++i)
    {
        positions.push_back(Pos(pos.x, pos.y + i));
    }
    return positions;
}

Positions Figure::GetLeftPath(const Pos pos, const Pos destinationCell) const
{
    Positions positions;
    for (int i = 1; pos.x - i >= destinationCell.x; ++i)
    {
        positions.push_back(Pos(pos.x - i, pos.y));
    }
    return positions;
}

Positions Figure::GetRightPath(const Pos pos, const Pos destinationCell) const
{
    Positions positions;
    for (int i = 1; i + pos.x <= destinationCell.x; ++i)
    {
        positions.push_back(Pos(pos.x + i, pos.y));
    }
    return positions;
}

Positions Figure::GetRightTopPath(const Pos pos, const Pos destinationCell) const
{
    Positions positions;
    for (int i = 1; i + pos.x <= destinationCell.x; ++i)
    {
        positions.push_back(Pos(pos.x + i, pos.y - i));
    }
    return positions;
}

Positions Figure::GetRightDownPath(const Pos pos, const Pos destinationCell) const
{
    Positions positions;
    for (int i = 1; i + pos.x <= destinationCell.x; ++i)
    {
        positions.push_back(Pos(pos.x + i, pos.y + i));
    }
    return positions;
}

Positions Figure::GetLeftTopPath(const Pos pos, const Pos destinationCell) const
{
    Positions positions;
    for (int i = 1; pos.x - i >= destinationCell.x; ++i)
    {
        positions.push_back(Pos(pos.x - i, pos.y - i));
    }
    return positions;
}

Positions Figure::GetLeftDownPath(const Pos pos, const Pos destinationCell) const
{
    Positions positions;
    for (int i = 1; pos.x - i >= destinationCell.x; ++i)
    {
        positions.push_back(Pos(pos.x - i, pos.y + i));
    }
    return positions;
}

std::vector<Pos> Figure::HandleDiagonalMovement(int xDifferenceRaw, int yDifferenceRaw, Pos pos, Pos destinationCell) const
{
    if (xDifferenceRaw > 0 && yDifferenceRaw < 0)
    {
        return GetRightTopPath(pos, destinationCell);
    }
    else if (xDifferenceRaw > 0 && yDifferenceRaw > 0)
    {
        return GetRightDownPath(pos, destinationCell);
    }
    else if (xDifferenceRaw < 0 && yDifferenceRaw < 0)
    {
        return GetLeftTopPath(pos, destinationCell);
    }
    else if(xDifferenceRaw < 0 && yDifferenceRaw > 0)
    {
        return GetLeftDownPath(pos, destinationCell);
    }
    return{};
}

std::vector<Pos> Figure::HandleBasicMovement(int xDifferenceRaw, int yDifferenceRaw, Pos pos, Pos destinationCell) const
{
    if (xDifferenceRaw == 0)
    {
        if (yDifferenceRaw < 0)
        {
            return GetTopPath(pos, destinationCell);
        }
        else
        {
            return GetDownPath(pos, destinationCell);
        }
    }
    else
    {
        if (xDifferenceRaw < 0)
        {
            return GetLeftPath(pos, destinationCell);
        }
        else
        {
            return GetRightPath(pos, destinationCell);
        }
    }
}