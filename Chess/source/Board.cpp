#include "Board.h"
#include "Window.h"
#include "interface/ICell.h"

Board::Board(std::unique_ptr<ICell> cell)
{
	for (int x = 0; x < m_board.size(); x++)
	{
		for (int y = 0; y < m_board[x].size(); y++)
		{
			m_board[x][y] = std::move(cell);
		}
	}
}

void Board::Draw(std::unique_ptr<Window> window)
{
	for (int x = 0; x < m_board.size(); x++)
	{
		for (int y = 0; y < m_board[x].size(); y++)
		{
			m_board[x][y]->Draw(std::move(window));
		}
	}
}
