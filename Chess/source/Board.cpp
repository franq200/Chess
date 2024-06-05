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
	m_figures[FigureColor::white].resize(16);
	m_figures[FigureColor::black].resize(16);
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

bool Board::IsCellOccupied(Pos mousePos) const
{
	return false;
}

void Board::SetCurrentFigure(Pos mousePos)
{
}

bool Board::IsCurrentFigureSet() const
{
	return false;
}

bool Board::IsMovePossible(Pos mousePos) const
{
	return false;
}

void Board::MoveCurrentFiguresToNewCell(Pos mousePos)
{
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

void Board::CreateWhite(TextureContainer& textures)
{
	Size size = Size(static_cast<uint16_t>(size::cellSizeXPix), static_cast<uint16_t>(size::cellSizeYPix));
	WhiteStartingIndex startingIndex = WhiteStartingIndex();
	for (int i = 0; i < 8; i++)
	{
		m_board[i][6]->AddFigure(m_figures[FigureColor::white][i] = std::make_unique<Pawn>(*textures["whitePawn"], Pos(i, 6), size));
	}
	m_board[startingIndex.rook1.x][startingIndex.rook1.y]->AddFigure(m_figures[FigureColor::white][8] = std::make_unique<Rook>(*textures["whiteRook"], startingIndex.rook1, size));
	m_board[startingIndex.knight1.x][startingIndex.knight1.y]->AddFigure(m_figures[FigureColor::white][9] = std::make_unique<Knight>(*textures["whiteKnight"], startingIndex.knight1, size));
	m_board[startingIndex.bishop1.x][startingIndex.bishop1.y]->AddFigure(m_figures[FigureColor::white][10] = std::make_unique<Bishop>(*textures["whiteBishop"], startingIndex.bishop1, size));
	m_board[startingIndex.queen.x][startingIndex.queen.y]->AddFigure(m_figures[FigureColor::white][11] = std::make_unique<Queen>(*textures["whiteQueen"], startingIndex.queen, size));
	m_board[startingIndex.king.x][startingIndex.king.y]->AddFigure(m_figures[FigureColor::white][12] = std::make_unique<King>(*textures["whiteKing"], startingIndex.king, size));
	m_board[startingIndex.bishop2.x][startingIndex.bishop2.y]->AddFigure(m_figures[FigureColor::white][13] = std::make_unique<Bishop>(*textures["whiteBishop"], startingIndex.bishop2, size));
	m_board[startingIndex.knight2.x][startingIndex.knight2.y]->AddFigure(m_figures[FigureColor::white][14] = std::make_unique<Knight>(*textures["whiteKnight"], startingIndex.knight2, size));
	m_board[startingIndex.rook2.x][startingIndex.rook2.y]->AddFigure(m_figures[FigureColor::white][15] = std::make_unique<Rook>(*textures["whiteRook"], startingIndex.rook2, size));
}

void Board::CreateBlack(TextureContainer& textures)
{
	BlackStartingIndex startingIndex = BlackStartingIndex();
	Size size = Size(static_cast<uint16_t>(size::cellSizeXPix), static_cast<uint16_t>(size::cellSizeYPix));
	m_board[startingIndex.rook1.x][startingIndex.rook1.y]->AddFigure(m_figures[FigureColor::black][0] = std::make_unique<Rook>(*textures["blackRook"], startingIndex.rook1, size));
	m_board[startingIndex.knight1.x][startingIndex.knight1.y]->AddFigure(m_figures[FigureColor::black][1] = std::make_unique<Knight>(*textures["blackKnight"], startingIndex.knight1, size));
	m_board[startingIndex.bishop1.x][startingIndex.bishop1.y]->AddFigure(m_figures[FigureColor::black][2] = std::make_unique<Bishop>(*textures["blackBishop"], startingIndex.bishop1, size));
	m_board[startingIndex.queen.x][startingIndex.queen.y]->AddFigure(m_figures[FigureColor::black][3] = std::make_unique<Queen>(*textures["blackQueen"], startingIndex.queen, size));
	m_board[startingIndex.king.x][startingIndex.king.y]->AddFigure(m_figures[FigureColor::black][4] = std::make_unique<King>(*textures["blackKing"], startingIndex.king, size));
	m_board[startingIndex.bishop2.x][startingIndex.bishop2.y]->AddFigure(m_figures[FigureColor::black][5] = std::make_unique<Bishop>(*textures["blackBishop"], startingIndex.bishop2, size));
	m_board[startingIndex.knight2.x][startingIndex.knight2.y]->AddFigure(m_figures[FigureColor::black][6] = std::make_unique<Knight>(*textures["blackKnight"], startingIndex.knight2, size));
	m_board[startingIndex.rook2.x][startingIndex.rook2.y]->AddFigure(m_figures[FigureColor::black][7] = std::make_unique<Rook>(*textures["blackRook"], startingIndex.rook2, size));
	for (int i = 7; i < 15; i++)
	{
		m_board[i-7][1]->AddFigure(m_figures[FigureColor::white][i] = std::make_unique<Pawn>(*textures["blackPawn"], Pos(i-7, 1), size));
	}
}
