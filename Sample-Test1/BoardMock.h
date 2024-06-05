#pragma once
#include <gmock/gmock.h>
#include "interface/IBoard.h"
#include "interface/IWindow.h"


class BoardMock : public IBoard
{
public:
	MOCK_METHOD(void, Draw, (std::unique_ptr<IWindow>& window), (override));
	MOCK_METHOD(bool, IsCellOccupied, (Pos mousePos), (const, override));
	MOCK_METHOD(void, SetCurrentFigure, (Pos mousePos), (override));
	MOCK_METHOD(bool, IsCurrentFigureSet, (), (const, override));
	MOCK_METHOD(bool, IsMovePossible, (Pos mousePos), (const, override));
	MOCK_METHOD(void, MoveCurrentFiguresToNewCell, (Pos mousePos), (override));
};

