#include "Cell.h"
#include "interface/IRectangleShape.h"
#include "interface/IWindow.h"

Cell::Cell(Pos pos)
{
	m_cell->SetPosition(pos);
}

void Cell::Draw(std::unique_ptr<IWindow> window)
{
	window->Draw(*m_cell);
}
