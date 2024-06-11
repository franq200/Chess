#pragma once
#include <gmock/gmock.h>
#include "interface/IWindow.h"

namespace sf
{
	class RenderWindow;
}

class WindowMock : public IWindow
{
public:
	MOCK_METHOD(bool, PollEvent,(IEvent& event), (override));
	MOCK_METHOD(void, Close,(), (override));
	MOCK_METHOD(void, Clear,(), (override));
	MOCK_METHOD(void, Display,(), (override));
	MOCK_METHOD(void, Draw,(const IRectangleShape& drawable), (override));
	MOCK_METHOD(bool, IsOpen,(), (const, override));
	MOCK_METHOD(void, Create,(Resolution mode, const std::string& title), (override));
	MOCK_METHOD(const sf::RenderWindow*, GetSfmlWindow, (), (const, override));
};

