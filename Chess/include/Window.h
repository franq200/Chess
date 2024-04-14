#pragma once
#include "interface/IWindow.h"
#include <SFML/Graphics.hpp>

class Window : public IWindow
{
public:
	Window() = default;
	void Create(Resolution res, const std::string& title) override;
	bool PollEvent(IEvent& event) override;
	void Close() override;
	void Clear() override;
	void Display() override;
	void Draw(const IRectangleShape& drawable) override;
	bool IsOpen() const override;
private:
	sf::RenderWindow m_window;
};

