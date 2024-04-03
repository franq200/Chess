#pragma once
#include <gmock/gmock.h>
#include "../Chess/ICell.h"

class CellMock : public ICell
{
public:
	MOCK_METHOD(void, Draw,(std::unique_ptr<IWindow> window), (override));
};

