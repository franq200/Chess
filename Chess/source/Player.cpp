#include "Player.h"
#include "interface/IFigure.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

void Player::AddFigures(FiguresVector& figures)
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

const FiguresVector& Player::GetFigures() const
{
	return m_figures;
}

bool Player::IsAnyMovePossible(FiguresVector opponentPlayerFigures) const
{
	std::vector<Pos> opponentTakingMoves = GetOpponentTakingMoves(opponentPlayerFigures);
	std::shared_ptr<IFigure> king = GetKing();
	if (std::find(opponentTakingMoves.begin(), opponentTakingMoves.end(), king->GetPosition()) != opponentTakingMoves.end())
	{
		std::vector<Pos> kingPossibleMoves = king->SetPossibleMoves(m_figures, opponentPlayerFigures);
		for (auto move : kingPossibleMoves)
		{
			if (std::find(opponentTakingMoves.begin(), opponentTakingMoves.end(), move) == opponentTakingMoves.end())
			{
				return true;
			}
		}

		for (auto figure : m_figures)
		{
			std::vector<Pos> possibleMoves = figure->SetPossibleMoves(m_figures, opponentPlayerFigures);
			for (auto move : possibleMoves)
			{
				// warto by zrobiæ coœ takiego ¿e do SetPossibleMoves przekazuje tylko pozycje i wtedy by mo¿na zmieniæ pozycje jednej figury i jeszcze trzeba zrobiæ tak ¿eby by³a funkcja getPossibleTakingMoves()
			}
		}
		//else if ()//if not is any figure move enough
		//{
		//	return true;
		//}
		return false;
	}
	for (auto figure : m_figures)
	{
		if (!figure->SetPossibleMoves(m_figures, opponentPlayerFigures).empty())
		{
			return true;
		}
	}
	return false;
}

std::vector<Pos> Player::GetOpponentTakingMoves(FiguresVector opponentPlayerFigures) const
{
	std::vector<Pos> takingMoves;
	return takingMoves;
}

std::shared_ptr<IFigure> Player::GetKing() const
{
	for (auto figure : m_figures)
	{
		if (figure->IsKing())
		{
			return figure;
		}
	}
	return std::shared_ptr<IFigure>();
}

void Player::UpdateCurrentFigure()
{
	m_currentFigure->SetOutlineThickness(2);
}
