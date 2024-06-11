#pragma once
#include <gmock/gmock.h>
#include "interface/IBoard.h"
#include "interface/IWindow.h"


class BoardMock : public IBoard
{
public:
	MOCK_METHOD(void, Draw, (std::unique_ptr<IWindow>& window), (override));
	MOCK_METHOD(bool, IsCellOccupied, (Pos mouseCell), (const, override));
	MOCK_METHOD(void, SetCurrentFigure, (Pos mouseCell), (override));
	MOCK_METHOD(bool, IsCurrentFigureSet, (), (const, override));
	MOCK_METHOD(bool, IsMovePossible, (Pos mouseCell), (const, override));
	MOCK_METHOD(void, MoveCurrentFiguresToNewCell, (Pos mouseCell), (override));
	MOCK_METHOD(void, CreateFigures, (TextureContainer& textures), (override));
};

