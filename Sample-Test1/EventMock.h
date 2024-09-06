#pragma once
#include <gmock/gmock.h>
#include "interface/IEvent.h"

class EventMock : public IEvent
{
public:
	MOCK_METHOD(bool, IsEventClosed, (), (override));
};
