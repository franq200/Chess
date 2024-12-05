#pragma once
#include "Helper.h"

class Board;

class IMoveExecutor
{
public:
	IMoveExecutor(Pos destinationPos);
	virtual void Execute(Board& board) = 0;
	Pos GetDestinationPos();
	IMoveExecutor& operator=(const IMoveExecutor& other);
protected:
	Pos m_destinationPos;
};

class NormalMoveExecutor : public IMoveExecutor
{
public:
	NormalMoveExecutor(Pos destinationPos);
	__declspec(dllexport) void Execute(Board& board) override;
};

class TakingMoveExecutor : public NormalMoveExecutor
{
public:
	TakingMoveExecutor(Pos destinationPos);
	__declspec(dllexport) void Execute(Board& board) override;
};

class CastleMoveExecutor : public IMoveExecutor
{
public:
	CastleMoveExecutor(Pos destinationPos);
	__declspec(dllexport) void Execute(Board& board) override;
};