#pragma once
#include "interface/IWindow.h"
#include <SFML/Graphics.hpp>

class Window : public IWindow
{
public:
	__declspec(dllexport) Window() = default;
	__declspec(dllexport) void Create(Resolution res, const std::string& title) override;
	__declspec(dllexport) bool PollEvent(IEvent& event) override;
	__declspec(dllexport) void Close() override;
	__declspec(dllexport) void Clear() override;
	__declspec(dllexport) void Display() override;
	__declspec(dllexport) void Draw(const IRectangleShape& drawable) override;
	__declspec(dllexport) bool IsOpen() const override;
private:
	sf::RenderWindow m_window;
};

