#include "Board.h"
#include "interface/IWindow.h"
#include "interface/ICell.h"
#include "Helper.h"
#include "figures/Rook.h"
#include "figures/Queen.h"
#include "figures/Pawn.h"
#include "figures/Knight.h"
#include "figures/King.h"
#include "figures/Bishop.h"
#include "interface/ICell.h"

Board::Board(std::array<std::unique_ptr<ICell>, 64> cells, const TextureContainer& textures)
{
	CreateBoard(cells);
	CreateFigures(textures);
}

void Board::CreateFigures(const TextureContainer& textures)
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

void Board::CreateWhite(const TextureContainer& textures)
{
	for (int i = 0; i < 8; i++)
	{
		m_figures[FigureColor::white][i] = std::move(std::make_unique<Pawn>());
	}
	m_figures[FigureColor::white][8] = std::move(std::make_unique<Rook>());
	m_figures[FigureColor::white][9] = std::move(std::make_unique<Knight>());
	m_figures[FigureColor::white][10] = std::move(std::make_unique<Bishop>());
	m_figures[FigureColor::white][11] = std::move(std::make_unique<Queen>());
	m_figures[FigureColor::white][12] = std::move(std::make_unique<King>());
	m_figures[FigureColor::white][13] = std::move(std::make_unique<Bishop>());
	m_figures[FigureColor::white][14] = std::move(std::make_unique<Knight>());
	m_figures[FigureColor::white][15] = std::move(std::make_unique<Rook>());
}

void Board::CreateBlack(const TextureContainer& textures)
{
	//m_figures[FigureColor::white][0] = std::make_unique<Rook>();
	//m_figures[FigureColor::white][1] = std::make_unique<Knight>();
	//m_figures[FigureColor::white][2] = std::make_unique<Bishop>();
	//m_figures[FigureColor::white][3] = std::make_unique<Queen>();
	//m_figures[FigureColor::white][4] = std::make_unique<King>();
	//m_figures[FigureColor::white][5] = std::make_unique<Bishop>();
	//m_figures[FigureColor::white][6] = std::make_unique<Knight>();
	//m_figures[FigureColor::white][7] = std::make_unique<Rook>();
	//for (int i = 8; i < 16; i++)
	//{
	//	m_figures[FigureColor::white][i] = std::make_unique<Pawn>();
	//}
}
