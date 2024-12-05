#include "IMoveExecutor.h"
#include "Board.h"

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

void NormalMoveExecutor::Execute(Board& board)
{
	if (board.IsItTakingMove(m_destinationPos))
	{
		board.RemoveFigure(mouseCell, opponent);
	}
	board.GetCurrentFigure()->OnMove();
	m_board[mouseCell.x][mouseCell.y]->SetFigure(board.GetCurrentFigure());
	m_board[m_selectedFigureCell.value().x][m_selectedFigureCell.value().y]->RemoveFigure();
	m_selectedFigureCell.reset();

	RemoveHighlights();
}

TakingMoveExecutor::TakingMoveExecutor(Pos destinationPos):
	NormalMoveExecutor(destinationPos)
{
}

void TakingMoveExecutor::Execute(Board& board)
{
	if (IsItTakingMove(mouseCell))
	{
		RemoveFigure(mouseCell, opponent);
	}
	GetCurrentFigure()->OnMove();
	m_board[mouseCell.x][mouseCell.y]->SetFigure(GetCurrentFigure());
	m_board[m_selectedFigureCell.value().x][m_selectedFigureCell.value().y]->RemoveFigure();
	m_selectedFigureCell.reset();

	RemoveHighlights();
}

CastleMoveExecutor::CastleMoveExecutor(Pos destinationPos):
	IMoveExecutor(destinationPos)
{
}

void CastleMoveExecutor::Execute(Board& board)
{
	if (IsItTakingMove(mouseCell))
	{
		RemoveFigure(mouseCell, opponent);
	}
	GetCurrentFigure()->OnMove();
	m_board[mouseCell.x][mouseCell.y]->SetFigure(GetCurrentFigure());
	m_board[m_selectedFigureCell.value().x][m_selectedFigureCell.value().y]->RemoveFigure();
	m_selectedFigureCell.reset();

	RemoveHighlights();
}
