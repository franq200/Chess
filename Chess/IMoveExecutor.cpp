#include "IMoveExecutor.h"

IMoveExecutor::IMoveExecutor(Pos destinationPos) :
	m_destinationPos(destinationPos)
{
}

Pos IMoveExecutor::GetDestinationPos()
{
	return m_destinationPos;
}

NormalMoveExecutor::NormalMoveExecutor(Pos destinationPos):
	IMoveExecutor(destinationPos)
{
}

void NormalMoveExecutor::Execute()
{

}

TakingMoveExecutor::TakingMoveExecutor(Pos destinationPos):
	NormalMoveExecutor(destinationPos)
{
}

void TakingMoveExecutor::Execute()
{

}

CastleMoveExecutor::CastleMoveExecutor(Pos destinationPos):
	IMoveExecutor(destinationPos)
{
}

void CastleMoveExecutor::Execute()
{

}
