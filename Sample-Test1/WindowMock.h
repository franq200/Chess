
/*
#pragma once
#include <gmock/gmock.h>
#include "../Chess/IWindow.h"

class WindowMock : public IWindow
{
public:
	MOCK_METHOD(bool, PollEvent,(sf::Event& event), (override));
	MOCK_METHOD(void, Close,(), (override));
	MOCK_METHOD(void, Clear,(), (override));
	MOCK_METHOD(void, Display,(), (override));
	MOCK_METHOD(void, Draw,(const sf::Drawable& drawable), (override));
	MOCK_METHOD(bool, IsOpen,(), (override));
	MOCK_METHOD(void, Create,(sf::VideoMode mode, const std::string& title, sf::Uint32 style = sf::Style::Default), (override));
};
*/
