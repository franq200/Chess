#pragma once
#include <gmock/gmock.h>
#include "../Chess/IBoard.h"

class BoardMock : public IBoard
{
public:
	MOCK_METHOD(void, Draw, (std::unique_ptr<IWindow> window), (override));
};

