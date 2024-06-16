#include "Cell.h"
#include "interface/IRectangleShape.h"
#include "interface/IWindow.h"
#include "RectangleShape.h"
#include "interface/IFigure.h"

Cell::Cell()
{
	static int pos = 0;
	m_pos = pos++;
	m_cell = std::make_unique<RectangleShape>();
}

void Cell::Draw(std::unique_ptr<IWindow>& window)
{
	window->Draw(*m_cell);
	if (m_figure != nullptr)
	{
		m_figure->Draw(window);
	}
}

void Cell::SetFillColor(Color color)
{
	m_cell->SetFillColor(color);
}

void Cell::SetPosition(Pos pos)
{
	m_cell->SetPosition(pos);
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

bool Cell::IsOccupied(CellFigureColor currentColor)
{
	return m_figure!=nullptr && static_cast<uint8_t>(currentColor) == static_cast<uint8_t>(m_figure->GetFigureColor());
}

bool Cell::IsMovePossible(Pos moveCell)
{
	return m_figure->IsMovePossible(moveCell);
}
