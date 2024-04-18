#pragma once
#include <gmock/gmock.h>
#include "interface/ICell.h"
#include "interface/IWindow.h"

class CellMock : public ICell
{
public:
	MOCK_METHOD(void, Draw,(std::unique_ptr<IWindow> window), (override));
};

