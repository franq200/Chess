#include "Cell.h"
#include "interface/IRectangleShape.h"
#include "Window.h"

void Cell::Draw(std::unique_ptr<Window> window)
{
	window->Draw(*m_cell);
}
