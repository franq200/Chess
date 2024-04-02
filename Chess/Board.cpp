#include "Board.h"

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
