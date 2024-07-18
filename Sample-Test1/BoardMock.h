#pragma once
#include <gmock/gmock.h>
#include "interface/IBoard.h"
#include "interface/IWindow.h"


class BoardMock : public IBoard
{
public:
	MOCK_METHOD(void ,Draw, (std::unique_ptr<IWindow>& window, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures), (override));
	MOCK_METHOD(bool ,IsCellOccupied, (Pos mouseCell, const std::unique_ptr<IPlayer>& currentPlayer), (const override));
	MOCK_METHOD(void ,SetCurrentFigure, (Pos mouseCell), (override));
	MOCK_METHOD(bool ,IsMovePossible, (Pos mouseCell, PlayerColor currentPlayer), (const override));
	MOCK_METHOD(void ,MoveCurrentFiguresToNewCell, (Pos mouseCell), (override));
	MOCK_METHOD(void ,CreateFigures, (TextureContainer& textures, std::unique_ptr<IPlayer>& white, std::unique_ptr<IPlayer>& black), (override));
};

