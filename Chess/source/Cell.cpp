#include "Cell.h"
#include "interface/IRectangleShape.h"
#include "interface/IWindow.h"

void Cell::Draw(std::unique_ptr<IWindow> window)
{
	window->Draw(*m_cell);
}
