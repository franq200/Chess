#pragma once
#include <gmock/gmock.h>
#include "../Chess/IGame.h"

class GameMock : public IGame
{
public:
	MOCK_METHOD(void, Update,(), (override));
};

