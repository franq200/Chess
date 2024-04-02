#include "Cell.h"

void Cell::Draw(std::unique_ptr<IWindow> window)
{
	window->Draw(m_cell);
}
