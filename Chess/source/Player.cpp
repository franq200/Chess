#include "Player.h"
#include "interface/IFigure.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

void Player::AddFigures(FiguresVector& figures, IFigurePtr king)
{
	m_figures = figures;
	m_king = king;
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

bool Player::HasFigure(const IFigurePtr& figure) const
{
	return std::find(m_figures.begin(), m_figures.end(), figure) != m_figures.end();
}

const FiguresVector& Player::GetFigures() const
{
	return m_figures;
}

bool Player::IsAnyMovePossible(const FiguresVector& opponentPlayerFigures) const
{
	std::vector<Pos> opponentTakingMoves = GetOpponentTakingMoves(opponentPlayerFigures, m_figures);
	if (IsKingUnderAttack(opponentTakingMoves))
	{
		if (CanKingEscape(opponentPlayerFigures))
		{
			return true;
		}

		//for (auto& figure : m_figures)
		//{
		//	std::vector<Pos> possibleMoves = figure->CalculatePossibleMoves(m_figures, opponentPlayerFigures);
		//	for (auto& move : possibleMoves)
		//	{
		//		std::vector<Pos> opponentTakingMoves = GetOpponentTakingMoves(opponentPlayerFigures);
		//		if (IsKingUnderAttack(opponentTakingMoves))
		//		{
		//
		//		}
		//	}
		//}
		return false;
	}
	for (auto& figure : m_figures)
	{
		if (!figure->CalculatePossibleMoves(m_figures, opponentPlayerFigures).empty())
		{
			return true;
		}
	}
	return false;
}

void Player::RemoveFigure(Pos mouseCell)
{
	std::erase_if(m_figures, [mouseCell](auto figure) {return figure->GetPosition() == mouseCell; });
}

bool Player::IsKingUnderAttack(const std::vector<Pos>& opponentTakingMoves) const
{
	return std::find(opponentTakingMoves.begin(), opponentTakingMoves.end(), m_king->GetPosition()) != opponentTakingMoves.end();
}

bool Player::CanKingEscape(const FiguresVector& opponentPlayerFigures) const
{
	//std::vector<Pos> kingPossibleMoves = m_king->CalculatePossibleMoves(m_figures, opponentPlayerFigures);
	//for (auto& move : kingPossibleMoves)
	//{
	//	FiguresVector opponentTakingMoves;
	//	if (std::find(opponentTakingMoves.begin(), opponentTakingMoves.end(), move) == opponentTakingMoves.end())
	//	{
	//		return true;
	//	}
	//}
	return false;
}

std::vector<Pos> Player::GetOpponentTakingMoves(const FiguresVector& opponentPlayerFigures, const FiguresVector& currentPlayerFigures) const
{
	std::vector<Pos> takingMoves;
	for (auto& opponentFigure : opponentPlayerFigures)
	{
		std::vector<Pos> possibleMoves = opponentFigure->CalculatePossibleMoves(opponentPlayerFigures, currentPlayerFigures);
		for (auto& move : possibleMoves)
		{
			if (opponentFigure->IsFigureTaking(move, currentPlayerFigures))
			{
				takingMoves.push_back(move);
			}
		}
	}
	return takingMoves;
}

std::pair<FiguresVector, IFigurePtr> Player::CloneFigures() const
{
	FiguresVector clonedFigures;
	IFigurePtr clonedKing;
	for (const auto& figure : m_figures)
	{
		if (figure == m_king)
		{
			clonedKing = figure->Clone();
			clonedFigures.emplace_back(clonedKing);
		}
		else
		{
			clonedFigures.emplace_back(figure->Clone());
		}
	}
	return std::pair<FiguresVector, IFigurePtr>(clonedFigures, clonedKing);
}
