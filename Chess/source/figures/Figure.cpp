#include "figures/Figure.h"
#include "interface/ITexture.h"
#include "Helper.h"
#include "interface/IWindow.h"
#include "../IMoveExecutor.h"

Figure::Figure(const ITexture& texture, Pos pos, Size size)
{
    m_startingPos = pos;
    m_figureShape.SetOutlineColor(Color(50, 50, 150));
    m_figureShape.SetTexture(texture);
    SetPixelPosition(functions::GetPixelPosFromCellPos(pos));
    m_figureShape.SetSize(size);
}

bool Figure::IsInRange(Pos mousePos)
{
    Pos pos = m_figureShape.GetPosition();
    bool isInXRange = mousePos.x - pos.x <= size::cellSizeXPix && mousePos.x - pos.x >= 0;
    bool isInYRange = mousePos.y - pos.y <= size::cellSizeYPix && mousePos.y - pos.y >= 0;
    return isInXRange && isInYRange;
}

void Figure::SetOutlineThickness(int thickness)
{
    m_figureShape.SetOutlineThickness(thickness);
}

void Figure::SetOutlineColor(Color color)
{
    m_figureShape.SetOutlineColor(color);
}

void Figure::Draw(IWindowPtr& window)
{
    window->Draw(m_figureShape);
}

void Figure::SetPixelPosition(Pos pos)
{
    SetShapePos(pos);
    m_position = functions::GetCellPosFromPixelPos(m_figureShape.GetPosition());
}

Pos Figure::GetPosition() const
{
    return m_position;
}

std::unique_ptr<IMoveExecutor> Figure::GenerateExecutor(Pos destinationCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const
{
    if (IsMoveAllowedForThisFigure(destinationCell, currentPlayerFigures, opponentPlayerFigures))
    {
        if (IsCollisionWithAnyPlayer(destinationCell, currentPlayerFigures, opponentPlayerFigures))
        {
            return nullptr;
        }
        if (IsFigureTaking(destinationCell, opponentPlayerFigures))
        {
            return std::make_unique<TakingMoveExecutor>(destinationCell);
        }
        return std::make_unique<NormalMoveExecutor>(destinationCell);
    }
    return nullptr;
}

bool Figure::IsMoveAllowedForThisFigure(Pos destinationCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const
{
    return false;
}

std::vector<std::unique_ptr<IMoveExecutor>> Figure::CalculatePossibleMoves(const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures)
{
    std::vector<std::unique_ptr<IMoveExecutor>> possibleMoves;
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
                auto executor = GenerateExecutor(newPos, currentPlayerFigures, opponentPlayerFigures);
                if (executor != nullptr)
                {
                    possibleMoves.push_back(std::move(executor));
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

void Figure::SetShapePos(const Pos& shapePos)
{
    m_figureShape.SetPixelPosition(shapePos);
}

void Figure::RestorePositionBeforeAnimation()
{
    m_figureShape.SetPixelPosition(functions::GetPixelPosFromCellPos(m_position));
}

Pos Figure::GetPixelTempPosition() const
{
    return m_figureShape.GetPixelTempPosition();
}

bool Figure::IsInPossibleMoves(const Pos& destinationPos) const
{
    return std::find(m_possibleMoves.begin(), m_possibleMoves.end(), destinationPos) != m_possibleMoves.end();
}

Pos Figure::GetCellTempPosition() const
{
    return m_figureShape.GetCellTempPosition();
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

std::shared_ptr<IFigure> Figure::Clone() const
{
    return std::shared_ptr<IFigure>();
}

void Figure::OnMove()
{
    m_moveCounter++;
}

bool operator==(const std::shared_ptr<IFigure>& lhs, const std::shared_ptr<IFigure>& rhs)
{
    return lhs->m_startingPos == rhs->m_startingPos;//!
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