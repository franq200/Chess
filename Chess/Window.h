#pragma once
#include "IWindow.h"
#include <SFML/Graphics.hpp>

class Window : public IWindow
{
public:
	Window() = default;
	void Create(sf::VideoMode mode, const std::string& title, sf::Uint32 style = sf::Style::Default);
	bool PollEvent(sf::Event& event) override;
	void Close() override;
	void Clear() override;
	void Display() override;
	void Draw(const sf::Drawable& drawable) override;
	bool IsOpen() const override;
private:
	sf::RenderWindow m_window;
};

