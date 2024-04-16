#include "Player.h"
#include "interface/IFigure.h"
#include <SFML/Graphics.hpp>

void Player::TryChangeCurrentFigure(Pos mousePos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (auto el : m_figures)
		{
			if (el->IsInRange(mousePos))
			{
				m_currentFigure = el;
			}
		}
	}
}
