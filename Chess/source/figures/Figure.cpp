#include "figures/Figure.h"
#include "interface/IRectangleShape.h"
#include "interface/ITexture.h"
#include "Helper.h"
#include "RectangleShape.h"
#include "interface/IWindow.h"

Figure::Figure(const ITexture& texture, Pos pos, Size size, PlayerColor color)
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

PlayerColor Figure::GetFigureColor() const
{
    return m_color;
}
