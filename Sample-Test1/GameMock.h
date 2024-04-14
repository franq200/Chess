#pragma once
#include <gmock/gmock.h>
#include "interface/IGame.h"

class GameMock : public IGame
{
public:
	MOCK_METHOD(void, Update,(), (override));
};

