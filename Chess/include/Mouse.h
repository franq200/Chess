#pragma once
#include "interface\IMouse.h"
#include <SFML/Graphics.hpp>

class Mouse : public IMouse
{
public:
	__declspec(dllexport) bool IsButtonPressed(Button button) const override;
	__declspec(dllexport) Pos GetCellPosition(const std::unique_ptr<IWindow>& window) override;
	__declspec(dllexport) Pos GetPixelPosition(const std::unique_ptr<IWindow>& window) override;
	__declspec(dllexport) bool IsMouseInWindow(const std::unique_ptr<IWindow>& window) const override;
private:
	sf::Mouse m_mouse;
};

