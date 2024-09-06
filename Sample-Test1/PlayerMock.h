#pragma once
#include "interface/IPlayer.h"
#include "gmock/gmock.h"

class PlayerMock : public IPlayer
{
public:
	MOCK_METHOD(void, AddFigures, (FiguresVector& figures, std::shared_ptr<IFigure> figure), (override));
	MOCK_METHOD(void, TryChangeCurrentFigure, (Pos mousePos), (override));
	MOCK_METHOD(bool, HasFigure, (const std::shared_ptr<IFigure>& figure), (const, override));
	MOCK_METHOD(const FiguresVector&, GetFigures, (), (const, override));
	MOCK_METHOD(bool, IsAnyMovePossible, (const FiguresVector& opponentPlayerFigures), (const, override));
	MOCK_METHOD(void, RemoveFigure, (Pos mouseCell), (override));
};

