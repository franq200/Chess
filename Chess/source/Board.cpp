#include "Board.h"
#include "interface/IWindow.h"
#include "interface/ICell.h"
#include "figures/Rook.h"
#include "figures/Queen.h"
#include "figures/Pawn.h"
#include "figures/Knight.h"
#include "figures/King.h"
#include "figures/Bishop.h"
#include "interface/ICell.h"
#include "interface/ITexture.h"
#include "interface/IRectangleShape.h"

Board::Board(std::array<std::unique_ptr<ICell>, 64> cells, TextureContainer& textures)
{
	CreateBoard(cells);
	//CreateFigures(textures);
}

void Board::CreateFigures(TextureContainer& textures)
{
	CreateWhite(textures);
	CreateBlack(textures);
}

void Board::Draw(std::unique_ptr<IWindow>& window)
{
	for (int x = 0; x < m_board.size(); x++)
	{
		for (int y = 0; y < m_board[x].size(); y++)
		{
			m_board[x][y]->Draw(window);
		}
	}
}

bool Board::IsCellOccupied(Pos mouseCell, FigureColors currentColor) const
{
	return m_board[mouseCell.x][mouseCell.y]->IsOccupied(static_cast<CellFigureColor>(currentColor));
}

void Board::SetCurrentFigure(Pos mouseCell)
{
	m_selectedFigureCell = mouseCell;
}

bool Board::IsCurrentFigureSet() const
{
	return m_selectedFigureCell.x != std::numeric_limits<uint16_t>::max();
}

bool Board::IsMovePossible(Pos mouseCell) const
{
	return m_board[m_selectedFigureCell.x][m_selectedFigureCell.y]->IsMovePossible(mouseCell);
}

void Board::MoveCurrentFiguresToNewCell(Pos mouseCell)
{
	m_board[mouseCell.x][mouseCell.y]->SetFigure(m_board[m_selectedFigureCell.x][m_selectedFigureCell.y]->GetFigure());
	m_board[m_selectedFigureCell.x][m_selectedFigureCell.y]->RemoveFigure();
	m_selectedFigureCell = Pos(std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::max());
}

void Board::CreateBoard(std::array<std::unique_ptr<ICell>, 64>& cells)
{
	for (int x = 0; x < 8; x++)
	{
		std::vector<std::unique_ptr<ICell>> row;
		for (int y = 0; y < 8; y++)
		{
			uint8_t cellIndex = GetCellIndex(Pos(x, y));
			if ((x + y )% 2 == 0)
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

void Board::CreateWhite(TextureContainer& textures)
{
	Size size = Size(static_cast<uint16_t>(size::cellSizeXPix), static_cast<uint16_t>(size::cellSizeYPix));
	WhiteStartingIndex startingIndex;

	FigureColor color = FigureColor::white;
	const int pawnStartRow = 6;
	
	for (int i = 0; i < size::boardCellsX; i++)
	{
		const auto& figure = m_figures[FigureColors::white].emplace_back(std::make_shared<Pawn>(*textures["whitePawn"], Pos(i, pawnStartRow), size, color));
		m_board[i][pawnStartRow]->SetFigure(figure);
	}
	const auto& whiteRook1 = m_figures[FigureColors::white].emplace_back(std::make_shared<Rook>(*textures["whiteRook"], startingIndex.rook1, size, color));
	m_board[startingIndex.rook1.x][startingIndex.rook1.y]->SetFigure(whiteRook1);
	
	const auto& whiteKnight1 = m_figures[FigureColors::white].emplace_back(std::make_shared<Knight>(*textures["whiteKnight"], startingIndex.knight1, size, color));
	m_board[startingIndex.knight1.x][startingIndex.knight1.y]->SetFigure(whiteKnight1);
	
	const auto& whiteBishop1 = m_figures[FigureColors::white].emplace_back(std::make_shared<Bishop>(*textures["whiteBishop"], startingIndex.bishop1, size, color));
	m_board[startingIndex.bishop1.x][startingIndex.bishop1.y]->SetFigure(whiteBishop1);
	
	const auto& whiteQueen = m_figures[FigureColors::white].emplace_back(std::make_shared<Queen>(*textures["whiteQueen"], startingIndex.queen, size, color));
	m_board[startingIndex.queen.x][startingIndex.queen.y]->SetFigure(whiteQueen);
	
	const auto& whiteKing = m_figures[FigureColors::white].emplace_back(std::make_shared<King>(*textures["whiteKing"], startingIndex.king, size, color));
	m_board[startingIndex.king.x][startingIndex.king.y]->SetFigure(whiteKing);
	
	const auto& whiteBishop2 = m_figures[FigureColors::white].emplace_back(std::make_shared<Bishop>(*textures["whiteBishop"], startingIndex.bishop2, size, color));
	m_board[startingIndex.bishop2.x][startingIndex.bishop2.y]->SetFigure(whiteBishop2);
	
	const auto& whiteKnight2 = m_figures[FigureColors::white].emplace_back(std::make_shared<Knight>(*textures["whiteKnight"], startingIndex.knight2, size, color));
	m_board[startingIndex.knight2.x][startingIndex.knight2.y]->SetFigure(whiteKnight2);
	
	const auto& whiteRook2 = m_figures[FigureColors::white].emplace_back(std::make_shared<Rook>(*textures["whiteRook"], startingIndex.rook2, size, color));
	m_board[startingIndex.rook2.x][startingIndex.rook2.y]->SetFigure(whiteRook2);
}

void Board::CreateBlack(TextureContainer& textures)
{
	BlackStartingIndex startingIndex;
	Size size = Size(static_cast<uint16_t>(size::cellSizeXPix), static_cast<uint16_t>(size::cellSizeYPix));
	
	FigureColor color = FigureColor::black;
	const int pawnStartRow = 1;
	
	const auto& blackRook1 = m_figures[FigureColors::black].emplace_back(std::make_shared<Rook>(*textures["blackRook"], startingIndex.rook1, size, color));
	m_board[startingIndex.rook1.x][startingIndex.rook1.y]->SetFigure(blackRook1);
	
	const auto& blackKnight1 = m_figures[FigureColors::black].emplace_back(std::make_shared<Knight>(*textures["blackKnight"], startingIndex.knight1, size, color));
	m_board[startingIndex.knight1.x][startingIndex.knight1.y]->SetFigure(blackKnight1);
	
	const auto& blackBishop1 = m_figures[FigureColors::black].emplace_back(std::make_shared<Bishop>(*textures["blackBishop"], startingIndex.bishop1, size, color));
	m_board[startingIndex.bishop1.x][startingIndex.bishop1.y]->SetFigure(blackBishop1);
	
	const auto& blackQueen = m_figures[FigureColors::black].emplace_back(std::make_shared<Queen>(*textures["blackQueen"], startingIndex.queen, size, color));
	m_board[startingIndex.queen.x][startingIndex.queen.y]->SetFigure(blackQueen);
	
	const auto& blackKing = m_figures[FigureColors::black].emplace_back(std::make_shared<King>(*textures["blackKing"], startingIndex.king, size, color));
	m_board[startingIndex.king.x][startingIndex.king.y]->SetFigure(blackKing);
	
	const auto& blackBishop2 = m_figures[FigureColors::black].emplace_back(std::make_shared<Bishop>(*textures["blackBishop"], startingIndex.bishop2, size, color));
	m_board[startingIndex.bishop2.x][startingIndex.bishop2.y]->SetFigure(blackBishop2);
	
	const auto& blackKnight2 = m_figures[FigureColors::black].emplace_back(std::make_shared<Knight>(*textures["blackKnight"], startingIndex.knight2, size, color));
	m_board[startingIndex.knight2.x][startingIndex.knight2.y]->SetFigure(blackKnight2);
	
	const auto& blackRook2 = m_figures[FigureColors::black].emplace_back(std::make_shared<Rook>(*textures["blackRook"], startingIndex.rook2, size, color));
	m_board[startingIndex.rook2.x][startingIndex.rook2.y]->SetFigure(blackRook2);
	for (int i = 0; i < size::boardCellsX; i++)
	{
		const auto& blackPawn = m_figures[FigureColors::black].emplace_back(std::make_shared<Pawn>(*textures["blackPawn"], Pos(i, pawnStartRow), size, color));
		m_board[i][pawnStartRow]->SetFigure(blackPawn);
	}
}
