#include "Board.h"
#include "interface/IWindow.h"
#include "interface/ICell.h"
#include "Helper.h"

Board::Board(std::array<std::unique_ptr<ICell>, 64> cells)
{
	CreateBoard(cells);
	CreateFigures();
}

void Board::Draw(std::unique_ptr<IWindow> window)
{
	for (int x = 0; x < m_board.size(); x++)
	{
		for (int y = 0; y < m_board[x].size(); y++)
		{
			m_board[x][y]->Draw(std::move(window));
		}
	}
}

void Board::CreateFigures()
{
}

void Board::CreateBoard(std::array<std::unique_ptr<ICell>, 64>& cells)
{
	for (int x = 0; x < 8; x++)
	{
		std::vector<std::unique_ptr<ICell>> row;
		for (int y = 0; y < 8; y++)
		{
			row.push_back(std::move(cells[GetCellIndex(Pos(x, y))]));
		}
		m_board.push_back(std::move(row));
	}
}
