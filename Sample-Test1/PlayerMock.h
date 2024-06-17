#pragma once
#include "interface/IPlayer.h"
#include "gmock/gmock.h"

class PlayerMock : public IPlayer
{
	MOCK_METHOD(void, TryChangeCurrentFigure, (Pos mousePos), (override));
};

