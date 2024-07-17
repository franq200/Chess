#include "Cell.h"
#include "interface/IPlayer.h"
#include "interface/IRectangleShape.h"
#include "interface/IWindow.h"
#include "RectangleShape.h"
#include "interface/IFigure.h"

Cell::Cell()
{
	static int pos = 0;
	m_pos = pos++;
	m_cell = std::make_unique<RectangleShape>();
	m_highlight = std::make_unique<RectangleShape>();
	m_highlight->SetFillColor(Color(220, 220, 220));
}

void Cell::Draw(std::unique_ptr<IWindow>& window)
{
	window->Draw(*m_cell);
	if (m_figure != nullptr)
	{
		m_figure->Draw(window);
	}
	window->Draw(*m_highlight);
}

void Cell::SetFillColor(Color color)
{
	m_cell->SetFillColor(color);
}

void Cell::SetPosition(Pos pos)
{
	m_cell->SetPosition(pos);
	m_highlight->SetPosition(Pos(pos.x + size::cellSizeXPix / 3, pos.y + size::cellSizeYPix / 3));
}

void Cell::SetSize(Size size)
{
	m_cell->SetSize(size);
}

void Cell::SetFigure(std::shared_ptr<IFigure> figure)
{
	m_figure = figure;
	m_figure->SetPosition(m_cell->GetPosition());
}

void Cell::RemoveFigure()
{
	m_figure.reset();
}

std::shared_ptr<IFigure> Cell::GetFigure() const
{
	return m_figure;
}

bool Cell::IsOccupiedByPlayer(const std::unique_ptr<IPlayer>& currentPlayer) const
{
	return currentPlayer->HasFigure(m_figure);
}

void Cell::Highlight()
{
	m_highlight->SetSize(Size(size::cellSizeXPix / 3, size::cellSizeYPix / 3));
}

void Cell::RemoveHighlight()
{
	m_highlight->SetSize(Size(0, 0));
}
