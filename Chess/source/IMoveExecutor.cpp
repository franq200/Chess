#include "IMoveExecutor.h"
#include "Board.h"
#include "interface/IFigure.h"
#include "interface/ICell.h"

IMoveExecutor::IMoveExecutor(Pos destinationPos) :
	m_destinationPos(destinationPos)
{
}

Pos IMoveExecutor::GetDestinationPos()
{
	return m_destinationPos;
}

IMoveExecutor& IMoveExecutor::operator=(const IMoveExecutor& other)
{
	if (this == &other)
	{
		return *this;
	}
	m_destinationPos = other.m_destinationPos;
	return *this;
}

NormalMoveExecutor::NormalMoveExecutor(Pos destinationPos):
	IMoveExecutor(destinationPos)
{
}

void NormalMoveExecutor::Execute(Board& board, IPlayerPtr& opponent)
{
	board.m_board[m_destinationPos.x][m_destinationPos.y]->SetFigure(board.GetCurrentFigure());
	board.m_board[board.m_selectedFigureCell.value().x][board.m_selectedFigureCell.value().y]->RemoveFigure();
	board.m_selectedFigureCell.reset();
	board.RemoveHighlights();
}

TakingMoveExecutor::TakingMoveExecutor(Pos destinationPos):
	NormalMoveExecutor(destinationPos)
{
}

void TakingMoveExecutor::Execute(Board& board, IPlayerPtr& opponent)
{
	board.RemoveFigure(m_destinationPos, opponent);
	NormalMoveExecutor::Execute(board, opponent);
}

CastleMoveExecutor::CastleMoveExecutor(Pos destinationPos):
	IMoveExecutor(destinationPos)
{
}

void CastleMoveExecutor::Execute(Board& board, IPlayerPtr& opponent)
{
	
}
