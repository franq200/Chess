#pragma once
#include "interface/IPlayer.h"
#include "gmock/gmock.h"

class PlayerMock : public IPlayer
{
	MOCK_METHOD(void, AddFigures, (FiguresVector& figures), (override));
	MOCK_METHOD(void, TryChangeCurrentFigure, (Pos mousePos), (override));
	MOCK_METHOD(bool, HasFigure, (const std::shared_ptr<IFigure>& figure), (const override));
	MOCK_METHOD(const FiguresVector&, GetFigures, (), (const override));
	MOCK_METHOD(bool, IsAnyMovePossible, (FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures), (const override));
};

