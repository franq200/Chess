#pragma once
#include <iostream>

struct Resolution
{
	int height = 0;
	int width = 0;
};

class IRectangleShape;
class IEvent;

namespace sf
{
class RenderWindow;
}

class IWindow
{
public:
	virtual ~IWindow() = default;
	virtual bool PollEvent(IEvent& event) = 0;
	virtual void Close() = 0;
	virtual void Clear() = 0;
	virtual void Display() = 0;
	virtual void Draw(const IRectangleShape& drawable) = 0;
	virtual bool IsOpen() const = 0;
	virtual void Create(Resolution res, const std::string& title) = 0;
	virtual const sf::RenderWindow* GetSfmlWindow() const = 0;
};
