#include "Board.h"
#include "interface/IWindow.h"
#include "Cell.h"

Board::Board()
{
	CreateBoard();
	CreateFigures();
}

void Board::Draw(std::unique_ptr<IWindow> window)
{
	for (int x = 0; x < m_board.size(); x++)
	{
		for (int y = 0; y < m_board[x].size(); y++)
		{
			m_board[x][y].Draw(std::move(window));
		}
	}
}

void Board::CreateFigures()
{
}

void Board::CreateBoard()
{
	for (int x = 0; x < 8; x++)
	{
		std::vector<Cell> row;
		for (int y = 0; y < 8; y++)
		{
			row.push_back(Cell());
		}
		m_board.push_back(row);
	}
}
