#pragma once
#include <gmock/gmock.h>
#include "interface/IBoard.h"
#include "interface/IWindow.h"


class BoardMock : public IBoard
{
public:
	MOCK_METHOD(void, Draw, (std::unique_ptr<IWindow>& window), (override));
};

