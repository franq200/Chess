#include "Mouse.h"

bool Mouse::IsButtonPressed(Button button) const
{
	return m_mouse.isButtonPressed(static_cast<sf::Mouse::Button>(button));
}

Pos Mouse::GetPosition()
{
	sf::Vector2i mousePos = m_mouse.getPosition();
	return Pos(mousePos.x, mousePos.y);
}
