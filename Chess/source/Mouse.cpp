#include "Mouse.h"
#include "interface/IWindow.h"
#include "Helper.h"

Mouse::Mouse()
{
	m_buttonsState[Button::Left] = { false, false };
	m_buttonsState[Button::Right] = { false, false };
}

bool Mouse::IsButtonPressed(Button button) const
{
	return m_buttonsState.at(button).current;
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

bool Mouse::WasButtonPressed(Button button) const
{
	return m_buttonsState.at(button).previous;
}

void Mouse::Update(UpdateType type)
{
	if (type == UpdateType::previous)
	{
		m_buttonsState.at(Button::Right).previous = m_buttonsState.at(Button::Right).current;
		m_buttonsState.at(Button::Left).previous = m_buttonsState.at(Button::Left).current;
	}
	else
	{
		m_buttonsState.at(Button::Right).current = m_mouse.isButtonPressed(static_cast<sf::Mouse::Button>(Button::Right));
		m_buttonsState.at(Button::Left).current = m_mouse.isButtonPressed(static_cast<sf::Mouse::Button>(Button::Left));
	}
}
