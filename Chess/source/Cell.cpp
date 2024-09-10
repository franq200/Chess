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
	InitHighlights();
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

void Cell::SetFigure(IFigurePtr figure)
{
	m_figure = figure;
	m_figure->SetPosition(m_cell->GetPosition());
}

void Cell::RemoveFigure()
{
	m_figure.reset();
}

IFigurePtr Cell::GetFigure() const
{
	return m_figure;
}

bool Cell::IsOccupiedByPlayer(const IPlayerPtr& currentPlayer) const
{
	return currentPlayer->HasFigure(m_figure);
}

void Cell::Highlight()
{
	m_highlight->SetSize(Size(size::cellSizeXPix / 3, size::cellSizeYPix / 3));
}

void Cell::HighlightAsTaking()
{
	m_takingHighlight->SetSize(Size(size::cellSizeXPix / 2, size::cellSizeYPix / 2));
}

void Cell::RemoveHighlight()
{
	m_highlight->SetSize(Size(0, 0));
	m_takingHighlight->SetSize(Size(0, 0));
}

void Cell::DrawCells(IWindowPtr& window)
{
	window->Draw(*m_cell);
	window->Draw(*m_highlight);
	window->Draw(*m_takingHighlight);
}

void Cell::DrawFigures(IWindowPtr& window)
{
	if (m_figure != nullptr)
	{
		m_figure->Draw(window);
	}
}

void Cell::InitHighlights()
{
	m_highlight = std::make_unique<RectangleShape>();
	m_highlight->SetFillColor(Color(220, 220, 220));
	m_takingHighlight = std::make_unique<RectangleShape>();
	m_takingHighlight->SetFillColor(Color(240, 190, 190));
}
