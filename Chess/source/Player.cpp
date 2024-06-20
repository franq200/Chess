#include "Player.h"
#include "interface/IFigure.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

void Player::AddFigures(std::vector<std::shared_ptr<IFigure>>& figures)
{
	m_figures = figures;
}

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

bool Player::HasFigure(const std::shared_ptr<IFigure>& figure) const
{
	return std::find(m_figures.begin(), m_figures.end(), figure) != m_figures.end();
}

void Player::UpdateCurrentFigure()
{
	m_currentFigure->SetOutlineThickness(2);
}
