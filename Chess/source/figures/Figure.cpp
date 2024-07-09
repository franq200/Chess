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

void Figure::Draw(std::unique_ptr<IWindow>& window)
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

std::vector<Pos> Figure::GetEveryPossibleMoves(FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const
{
    std::vector<Pos> possibleMoves;
    Pos currentPos = GetCellPosFromPixelPos(m_figure->GetPosition());
    
    for (const auto& direction : m_directions) {
        for (int i = 1; i < 8; ++i) {
            Pos newPos = { currentPos.x + direction[0] * i, currentPos.y + direction[1] * i };
            if (newPos.x >= 0 && newPos.x < 8 && newPos.y >= 0 && newPos.y < 8) {
                if (IsMovePossible(newPos, currentPlayerFigures, opponentPlayerFigures)) {
                    possibleMoves.push_back(newPos);
                }
            }
            else {
                break;
            }
        }
    }
    
    return possibleMoves;
}

Positions Figure::GetTopPath(const Pos pos, const Pos moveCell) const
{
    Positions positions;
    for (int i = 1; pos.y - i >= moveCell.y; ++i)
    {
        positions.push_back(Pos(pos.x, pos.y - i));
    }
    return positions;
}

Positions Figure::GetDownPath(const Pos pos, const Pos moveCell) const
{
    Positions positions;
    for (int i = 1; i + pos.y <= moveCell.y; ++i)
    {
        positions.push_back(Pos(pos.x, pos.y + i));
    }
    return positions;
}

Positions Figure::GetLeftPath(const Pos pos, const Pos moveCell) const
{
    Positions positions;
    for (int i = 1; pos.x - i >= moveCell.x; ++i)
    {
        positions.push_back(Pos(pos.x - i, pos.y));
    }
    return positions;
}

Positions Figure::GetRightPath(const Pos pos, const Pos moveCell) const
{
    Positions positions;
    for (int i = 1; i + pos.x <= moveCell.x; ++i)
    {
        positions.push_back(Pos(pos.x + i, pos.y));
    }
    return positions;
}

Positions Figure::GetRightTopPath(const Pos pos, const Pos moveCell) const
{
    Positions positions;
    for (int i = 1; i + pos.x <= moveCell.x; ++i)
    {
        positions.push_back(Pos(pos.x + i, pos.y - i));
    }
    return positions;
}

Positions Figure::GetRightDownPath(const Pos pos, const Pos moveCell) const
{
    Positions positions;
    for (int i = 1; i + pos.x <= moveCell.x; ++i)
    {
        positions.push_back(Pos(pos.x + i, pos.y + i));
    }
    return positions;
}

Positions Figure::GetLeftTopPath(const Pos pos, const Pos moveCell) const
{
    Positions positions;
    for (int i = 1; pos.x - i >= moveCell.x; ++i)
    {
        positions.push_back(Pos(pos.x - i, pos.y - i));
    }
    return positions;
}

Positions Figure::GetLeftDownPath(const Pos pos, const Pos moveCell) const
{
    Positions positions;
    for (int i = 1; pos.x - i >= moveCell.x; ++i)
    {
        positions.push_back(Pos(pos.x - i, pos.y + i));
    }
    return positions;
}

std::vector<Pos> Figure::HandleDiagonalMovement(int xDifferenceRaw, int yDifferenceRaw, Pos pos, Pos moveCell) const
{
    if (xDifferenceRaw > 0 && yDifferenceRaw < 0)
    {
        return GetRightTopPath(pos, moveCell);
    }
    else if (xDifferenceRaw > 0 && yDifferenceRaw > 0)
    {
        return GetRightDownPath(pos, moveCell);
    }
    else if (xDifferenceRaw < 0 && yDifferenceRaw < 0)
    {
        return GetLeftTopPath(pos, moveCell);
    }
    else
    {
        return GetLeftDownPath(pos, moveCell);
    }
}

std::vector<Pos> Figure::HandleBasicMovement(int xDifferenceRaw, int yDifferenceRaw, Pos pos, Pos moveCell) const
{
    if (xDifferenceRaw == 0)
    {
        if (yDifferenceRaw < 0)
        {
            return GetTopPath(pos, moveCell);
        }
        else
        {
            return GetDownPath(pos, moveCell);
        }
    }
    else
    {
        if (xDifferenceRaw < 0)
        {
            return GetLeftPath(pos, moveCell);
        }
        else
        {
            return GetRightPath(pos, moveCell);
        }
    }
}