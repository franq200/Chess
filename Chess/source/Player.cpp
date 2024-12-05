#include "Player.h"
#include "interface/IFigure.h"
#include "../IMoveExecutor.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

namespace
{
	FiguresVector CloneOpponentFigures(const FiguresVector& opponentPlayerFigures)
	{
		FiguresVector clonedFigures;
		for (const auto& figure : opponentPlayerFigures)
		{
			clonedFigures.emplace_back(figure->Clone());
		}
		return clonedFigures;
	}

	std::vector<Pos> GetOpponentTakingMoves(const FiguresVector& opponentPlayerFigures, const FiguresVector& currentPlayerFigures)
	{
		std::vector<Pos> takingMoves;
		for (auto& opponentFigure : opponentPlayerFigures)
		{
			std::vector<std::unique_ptr<IMoveExecutor>> possibleMoves = opponentFigure->CalculatePossibleMoves(opponentPlayerFigures, currentPlayerFigures);
			for (auto& move : possibleMoves)
			{
				if (opponentFigure->IsFigureTaking(move->GetDestinationPos(), currentPlayerFigures))
				{
					takingMoves.push_back(move->GetDestinationPos());
				}
			}
		}
		return takingMoves;
	}
}

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

		for (auto& figure : m_figures)
		{
			std::vector<std::unique_ptr<IMoveExecutor>> possibleMoves = figure->CalculatePossibleMoves(m_figures, opponentPlayerFigures);
			for (auto& move : possibleMoves)
			{
				auto [clonedFiguresVector, kingCopy] = CloneFigures();
				auto clonedOpponentFigures = CloneOpponentFigures(opponentPlayerFigures);
				auto figureCopy = std::find(clonedFiguresVector.begin(), clonedFiguresVector.end(), figure);
				if (figureCopy == clonedFiguresVector.end())
				{
					throw(std::exception("bad figures copy"));
				}
				(*figureCopy)->SetPixelPosition(functions::GetPixelPosFromCellPos(move->GetDestinationPos()));
				std::erase_if(clonedOpponentFigures, [&](auto& figure) {return figure->GetPosition() == move->GetDestinationPos(); });

				std::vector<Pos> opponentTakingMoves = GetOpponentTakingMoves(clonedOpponentFigures, clonedFiguresVector);
				if (std::find(opponentTakingMoves.begin(), opponentTakingMoves.end(), kingCopy->GetPosition()) == opponentTakingMoves.end())
				{
					return true;
				}
			}
		}
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
	std::vector<std::unique_ptr<IMoveExecutor>> kingPossibleMoves = m_king->CalculatePossibleMoves(m_figures, opponentPlayerFigures);
	for (std::unique_ptr<IMoveExecutor>& move : kingPossibleMoves)
	{
		auto [clonedFiguresVector, kingCopy] = CloneFigures();
		auto clonedOpponentFigures = CloneOpponentFigures(opponentPlayerFigures);
		kingCopy->SetPixelPosition(functions::GetPixelPosFromCellPos(move->GetDestinationPos()));
		std::erase_if(clonedOpponentFigures, [&](auto& figure) {return figure->GetPosition() == move->GetDestinationPos(); });

		std::vector<Pos> opponentTakingMoves = GetOpponentTakingMoves(clonedOpponentFigures, clonedFiguresVector);
		if (std::find(opponentTakingMoves.begin(), opponentTakingMoves.end(), move) == opponentTakingMoves.end())
		{
			return true;
		}
	}
	return false;
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
