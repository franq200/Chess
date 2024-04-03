#pragma once
#include <SFML/Graphics.hpp>

class IWindow
{
public:
	~IWindow() = default;
	virtual bool PollEvent(sf::Event& event) = 0;
	virtual void Close() = 0;
	virtual void Clear() = 0;
	virtual void Display() = 0;
	virtual void Draw(const sf::Drawable& drawable) = 0;
	virtual bool IsOpen() const = 0;
	virtual void Create(sf::VideoMode mode, const std::string& title, sf::Uint32 style = sf::Style::Default) = 0;
};
