#pragma once
#include <gmock/gmock.h>
#include "interface/ICell.h"

class CellMock : public ICell
{
public:
	MOCK_METHOD(void, Draw,(std::unique_ptr<Window> window), (override));
};

