#include "Mouse.h"
#include "interface/IWindow.h"
#include "Helper.h"

bool Mouse::IsButtonPressed(Button button) const
{
	return m_mouse.isButtonPressed(static_cast<sf::Mouse::Button>(button));
}

Pos Mouse::GetCellPosition(const IWindowPtr& window)
{
	sf::Vector2i mousePos = m_mouse.getPosition(*window->GetSfmlWindow());
	return functions::GetCellPosFromPixelPos(Pos(mousePos.x, mousePos.y));
}

Pos Mouse::GetPixelPosition(const IWindowPtr& window)
{
	sf::Vector2i mousePos = m_mouse.getPosition(*window->GetSfmlWindow());
	return Pos(mousePos.x, mousePos.y);
}

bool Mouse::IsMouseInWindow(const IWindowPtr& window) const
{
	sf::Vector2i mousePos = m_mouse.getPosition(*window->GetSfmlWindow());
	bool isInXRange = mousePos.x >= 0 && mousePos.x <= size::windowSizeXPix;
	bool isInYRange = mousePos.y >= 0 && mousePos.y <= size::windowSizeYPix;
	return isInXRange && isInYRange;
}
