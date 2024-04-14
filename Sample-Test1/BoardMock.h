#pragma once
#include <gmock/gmock.h>
#include "interface/IBoard.h"

class BoardMock : public IBoard
{
public:
	MOCK_METHOD(void, Draw, (std::unique_ptr<Window> window), (override));
};

