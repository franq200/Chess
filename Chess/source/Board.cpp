#include "Board.h"
#include "interface/IPlayer.h"
#include "interface/IWindow.h"
#include "figures/Rook.h"
#include "figures/Queen.h"
#include "figures/Pawn.h"
#include "figures/Knight.h"
#include "figures/King.h"
#include "figures/Bishop.h"
#include "interface/ICell.h"
#include "interface/ITexture.h"
#include "interface/IRectangleShape.h"
#include "IMoveExecutor.h"

namespace
{
	std::vector<Pos> GetOpponentTakingMoves(const FiguresVector& opponentPlayerFigures, const FiguresVector& currentPlayerFigures)
	{
		std::vector<Pos> takingMoves;
		for (auto& opponentFigure : opponentPlayerFigures)
		{
			std::vector<MoveExecutorPtr> possibleMoves = opponentFigure->CalculatePossibleMoves(opponentPlayerFigures, currentPlayerFigures);
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

Board::Board(std::array<ICellPtr, 64> cells, TexturesMap& textures)
{
	CreateBoard(cells);
}

void Board::Draw(IWindowPtr& window)
{
	DrawCells(window);
	DrawFiguresAndHighlights(window);
}

bool Board::IsShortCastlePossible(const Positions& opponentTakingMoves) const
{
	//if king not under attack
	//if rook pos.y == king pos.y and rook pos.x == 0

	if (std::find_if(opponentTakingMoves.begin(), opponentTakingMoves.end(), [this](auto takingMove) {return takingMove == m_whiteKing->GetPosition() || takingMove == m_blackKing->GetPosition(); }) != opponentTakingMoves.end())
	{
		return false;
	}

}

bool Board::IsLongCastlePossible(const Positions& opponentTakingMoves) const
{
	return false;
}

std::vector<Pos> Board::GetTakingMoves(const IFigurePtr& currentFigure, const Figures& opponentFigures, const MoveExecutors& possibleMoves) const
{
	std::vector<Pos> takingMoves;
	for (auto& move : possibleMoves)
	{
		if (currentFigure->IsFigureTaking(move->GetDestinationPos(), opponentFigures))
		{
			takingMoves.push_back(move->GetDestinationPos());
		}
	}
	return takingMoves;
}

void Board::HighlightMoves(const MoveExecutors& possibleMoves)
{
	for (auto& move : possibleMoves)
	{
		auto moveDestinationPos = move->GetDestinationPos();
		if (!m_takingMoves.empty() && std::find_if(m_takingMoves.begin(), m_takingMoves.end(), [moveDestinationPos](auto takingMove) {return takingMove.x == moveDestinationPos.x;}) == m_takingMoves.end())
		{
			m_board.at(moveDestinationPos.x).at(moveDestinationPos.y)->HighlightAsTaking();
		}
		else
		{
			m_board.at(moveDestinationPos.x).at(moveDestinationPos.y)->Highlight();
		}
	}
}

bool Board::IsCellOccupied(Pos mouseCell, const IPlayerPtr& currentPlayer) const
{
	return m_board.at(mouseCell.x).at(mouseCell.y)->IsOccupiedByPlayer(currentPlayer);
}

void Board::SetCurrentFigure(Pos mouseCell, PlayerColor currentPlayer)
{
	RemoveHighlights();
	m_selectedFigureCell = mouseCell;
	auto currentFigure = GetCurrentFigure();
	UpdatePossibleMoves(currentPlayer);
}

bool Board::IsMovePossible(Pos mouseCell) const
{
	if (IsCurrentFigureSet())
	{
		const IFigurePtr currentFigure = GetCurrentFigure();
		return currentFigure->IsInPossibleMoves(mouseCell);
	}
	return false;
}

void Board::UpdatePossibleMoves(PlayerColor currentPlayer)
{
	m_takingMoves.clear();
	const IFigurePtr currentFigure = GetCurrentFigure();
	auto [currentPlayerFigures, opponentFigures] = GetPlayersFigures(currentPlayer);
	auto opponentTakingMoves = GetOpponentTakingMoves(currentPlayerFigures, opponentFigures);
	MoveExecutors possibleMoves = currentFigure->CalculatePossibleMoves(currentPlayerFigures, opponentFigures);
	m_takingMoves = GetTakingMoves(currentFigure, opponentFigures, possibleMoves);
	HighlightMoves(possibleMoves);
}

bool Board::IsCurrentFigureSet() const
{
	return m_selectedFigureCell.has_value();
}

void Board::MoveCurrentFiguresToNewCell(Pos mouseCell, IPlayerPtr& opponent)
{
	const IFigurePtr currentFigure = GetCurrentFigure();
	currentFigure->OnMove(*this, opponent, mouseCell);
}

void Board::CreateFigures(TexturesMap& textures, IPlayerPtr& white, IPlayerPtr& black)
{
	CreateWhite(textures);
	CreateBlack(textures);
	white->AddFigures(m_figures[PlayerColor::white], m_whiteKing);
	black->AddFigures(m_figures[PlayerColor::black], m_blackKing);
}

void Board::Animate(const Pos& mousePos)
{
	if (IsCurrentFigureSet())
	{
		auto currentFigure = GetCurrentFigure();
		auto currentFigurePos = currentFigure->GetPixelTempPosition();
		if (m_mousePosInFigure.has_value())
		{
			int newXPos = currentFigurePos.x + (mousePos.x - (currentFigurePos.x + m_mousePosInFigure.value().x));
			int newYPos = currentFigurePos.y + (mousePos.y - (currentFigurePos.y + m_mousePosInFigure.value().y));
			currentFigure->SetShapePos(Pos(newXPos, newYPos));
		}
		else if (!m_mousePosInFigure.has_value())
		{
			m_mousePosInFigure = Pos(mousePos.x - currentFigurePos.x, mousePos.y - currentFigurePos.y);
		}
	}
}

void Board::EndAnimation(const Pos& mouseCell)
{
	const bool moveNotExectuted = IsCurrentFigureSet();
	if (moveNotExectuted)
	{
		auto currentFigure = GetCurrentFigure();
		currentFigure->RestorePositionBeforeAnimation();
	}
	m_mousePosInFigure = std::nullopt;
	m_isAnimating = false;
}

bool Board::IsAnimating() const
{
	return m_isAnimating;
}

void Board::StartAnimation()
{
	m_isAnimating = true;
}

void Board::RemoveFigure(Pos mouseCell, IPlayerPtr& opponent)
{
	for (auto& [color, figures] : m_figures)
	{
		std::erase_if(figures, [mouseCell](auto figure) {return figure->GetPosition() == mouseCell; });
	}
	opponent->RemoveFigure(mouseCell);
}

bool Board::IsItTakingMove(const Pos& move) const
{
	if (!m_takingMoves.empty())
	{
		return std::find(m_takingMoves.begin(), m_takingMoves.end(), move) != m_takingMoves.end();
	}
	return false;
}

void Board::DrawCells(IWindowPtr& window)
{
	for (int x = 0; x < m_board.size(); x++)
	{
		for (int y = 0; y < m_board[x].size(); y++)
		{
			m_board[x][y]->DrawCells(window);
		}
	}
}

void Board::DrawFiguresAndHighlights(IWindowPtr& window)
{
	for (int x = 0; x < m_board.size(); x++)
	{
		for (int y = 0; y < m_board[x].size(); y++)
		{
			m_board[x][y]->DrawFigures(window);
			m_board[x][y]->DrawHighlights(window);
		}
	}
	if (m_selectedFigureCell.has_value())
	{
		m_board[m_selectedFigureCell.value().x][m_selectedFigureCell.value().y]->DrawFigures(window);
	}
}

std::pair<Figures, Figures> Board::GetPlayersFigures(PlayerColor currentPlayer) const
{
	Figures currentPlayerFigures = m_figures.at(currentPlayer);
	Figures opponentFigures;
	if (currentPlayer == PlayerColor::white)
	{
		opponentFigures = m_figures.at(PlayerColor::black);
	}
	else
	{
		opponentFigures = m_figures.at(PlayerColor::white);
	}
	return std::pair<Figures, Figures>(currentPlayerFigures, opponentFigures);
}

void Board::CreateBoard(std::array<ICellPtr, 64>& cells)
{
	for (int x = 0; x < 8; x++)
	{
		std::vector<ICellPtr> row;
		for (int y = 0; y < 8; y++)
		{
			uint8_t cellIndex = functions::GetCellIndex(Pos(x, y));
			if ((x + y) % 2 == 0)
			{
				cells[cellIndex]->SetFillColor(Color(0, 200, 0));
			}
			else
			{
				cells[cellIndex]->SetFillColor(Color(0, 0, 200));
			}
			cells[cellIndex]->SetPosition(Pos(static_cast<uint16_t>(x * size::cellSizeXPix), static_cast<uint16_t>(y * size::cellSizeYPix)));
			cells[cellIndex]->SetSize(Size(static_cast<uint8_t>(size::cellSizeXPix), static_cast<uint8_t>(size::cellSizeYPix)));
			row.push_back(std::move(cells[cellIndex]));
		}
		m_board.push_back(std::move(row));
	}
}

namespace
{
	struct WhiteStartingIndex
	{
		Pos rook1 = Pos(0, 7);
		Pos knight1 = Pos(1, 7);
		Pos bishop1 = Pos(2, 7);
		Pos queen = Pos(3, 7);
		Pos king = Pos(4, 7);
		Pos bishop2 = Pos(5, 7);
		Pos knight2 = Pos(6, 7);
		Pos rook2 = Pos(7, 7);
	};

	struct BlackStartingIndex
	{
		Pos rook1 = Pos(0, 0);
		Pos knight1 = Pos(1, 0);
		Pos bishop1 = Pos(2, 0);
		Pos queen = Pos(3, 0);
		Pos king = Pos(4, 0);
		Pos bishop2 = Pos(5, 0);
		Pos knight2 = Pos(6, 0);
		Pos rook2 = Pos(7, 0);
	};
}

void Board::CreateWhite(TexturesMap& textures)
{
	Size size = Size(static_cast<uint16_t>(size::cellSizeXPix), static_cast<uint16_t>(size::cellSizeYPix));
	WhiteStartingIndex startingIndex;

	const int pawnStartRow = 6;

	for (int i = 0; i < size::boardCellsX; i++)
	{
		const auto& figure = m_figures[PlayerColor::white].emplace_back(std::make_shared<Pawn>(*textures["whitePawn"], Pos(i, pawnStartRow), size));
		m_board[i][pawnStartRow]->SetFigure(figure);
	}
	const auto& whiteRook1 = m_figures[PlayerColor::white].emplace_back(std::make_shared<Rook>(*textures["whiteRook"], startingIndex.rook1, size));
	m_board[startingIndex.rook1.x][startingIndex.rook1.y]->SetFigure(whiteRook1);

	const auto& whiteKnight1 = m_figures[PlayerColor::white].emplace_back(std::make_shared<Knight>(*textures["whiteKnight"], startingIndex.knight1, size));
	m_board[startingIndex.knight1.x][startingIndex.knight1.y]->SetFigure(whiteKnight1);

	const auto& whiteBishop1 = m_figures[PlayerColor::white].emplace_back(std::make_shared<Bishop>(*textures["whiteBishop"], startingIndex.bishop1, size));
	m_board[startingIndex.bishop1.x][startingIndex.bishop1.y]->SetFigure(whiteBishop1);

	const auto& whiteQueen = m_figures[PlayerColor::white].emplace_back(std::make_shared<Queen>(*textures["whiteQueen"], startingIndex.queen, size));
	m_board[startingIndex.queen.x][startingIndex.queen.y]->SetFigure(whiteQueen);

	const auto& whiteKing = m_figures[PlayerColor::white].emplace_back(std::make_shared<King>(*textures["whiteKing"], startingIndex.king, size));
	m_board[startingIndex.king.x][startingIndex.king.y]->SetFigure(whiteKing);
	m_whiteKing = whiteKing;

	const auto& whiteBishop2 = m_figures[PlayerColor::white].emplace_back(std::make_shared<Bishop>(*textures["whiteBishop"], startingIndex.bishop2, size));
	m_board[startingIndex.bishop2.x][startingIndex.bishop2.y]->SetFigure(whiteBishop2);

	const auto& whiteKnight2 = m_figures[PlayerColor::white].emplace_back(std::make_shared<Knight>(*textures["whiteKnight"], startingIndex.knight2, size));
	m_board[startingIndex.knight2.x][startingIndex.knight2.y]->SetFigure(whiteKnight2);

	const auto& whiteRook2 = m_figures[PlayerColor::white].emplace_back(std::make_shared<Rook>(*textures["whiteRook"], startingIndex.rook2, size));
	m_board[startingIndex.rook2.x][startingIndex.rook2.y]->SetFigure(whiteRook2);
}

void Board::CreateBlack(TexturesMap& textures)
{
	BlackStartingIndex startingIndex;
	Size size = Size(static_cast<uint16_t>(size::cellSizeXPix), static_cast<uint16_t>(size::cellSizeYPix));

	const int pawnStartRow = 1;

	const auto& blackRook1 = m_figures[PlayerColor::black].emplace_back(std::make_shared<Rook>(*textures["blackRook"], startingIndex.rook1, size));
	m_board[startingIndex.rook1.x][startingIndex.rook1.y]->SetFigure(blackRook1);

	const auto& blackKnight1 = m_figures[PlayerColor::black].emplace_back(std::make_shared<Knight>(*textures["blackKnight"], startingIndex.knight1, size));
	m_board[startingIndex.knight1.x][startingIndex.knight1.y]->SetFigure(blackKnight1);

	const auto& blackBishop1 = m_figures[PlayerColor::black].emplace_back(std::make_shared<Bishop>(*textures["blackBishop"], startingIndex.bishop1, size));
	m_board[startingIndex.bishop1.x][startingIndex.bishop1.y]->SetFigure(blackBishop1);

	const auto& blackQueen = m_figures[PlayerColor::black].emplace_back(std::make_shared<Queen>(*textures["blackQueen"], startingIndex.queen, size));
	m_board[startingIndex.queen.x][startingIndex.queen.y]->SetFigure(blackQueen);

	const auto& blackKing = m_figures[PlayerColor::black].emplace_back(std::make_shared<King>(*textures["blackKing"], startingIndex.king, size));
	m_board[startingIndex.king.x][startingIndex.king.y]->SetFigure(blackKing);
	m_blackKing = blackKing;

	const auto& blackBishop2 = m_figures[PlayerColor::black].emplace_back(std::make_shared<Bishop>(*textures["blackBishop"], startingIndex.bishop2, size));
	m_board[startingIndex.bishop2.x][startingIndex.bishop2.y]->SetFigure(blackBishop2);

	const auto& blackKnight2 = m_figures[PlayerColor::black].emplace_back(std::make_shared<Knight>(*textures["blackKnight"], startingIndex.knight2, size));
	m_board[startingIndex.knight2.x][startingIndex.knight2.y]->SetFigure(blackKnight2);

	const auto& blackRook2 = m_figures[PlayerColor::black].emplace_back(std::make_shared<Rook>(*textures["blackRook"], startingIndex.rook2, size));
	m_board[startingIndex.rook2.x][startingIndex.rook2.y]->SetFigure(blackRook2);
	for (int i = 0; i < size::boardCellsX; i++)
	{
		const auto& blackPawn = m_figures[PlayerColor::black].emplace_back(std::make_shared<Pawn>(*textures["blackPawn"], Pos(i, pawnStartRow), size));
		m_board[i][pawnStartRow]->SetFigure(blackPawn);
	}
}

void Board::RemoveHighlights()
{
	for (int x = 0; x < m_board.size(); x++)
	{
		for (int y = 0; y < m_board[x].size(); y++)
		{
			m_board[x][y]->RemoveHighlight();
		}
	}
}

IFigurePtr Board::GetCurrentFigure() const
{
	if (IsCurrentFigureSet())
	{
		const int x = m_selectedFigureCell.value().x;
		const int y = m_selectedFigureCell.value().y;
		return m_board.at(x).at(y)->GetFigure();
	}
	return nullptr;
}
