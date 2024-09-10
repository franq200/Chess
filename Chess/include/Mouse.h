#pragma once
#include "interface\IMouse.h"
#include <SFML/Graphics.hpp>

class Mouse : public IMouse
{
public:
	__declspec(dllexport) bool IsButtonPressed(Button button) const override;
	__declspec(dllexport) Pos GetCellPosition(const IWindowPtr& window) override;
	__declspec(dllexport) Pos GetPixelPosition(const IWindowPtr& window) override;
	__declspec(dllexport) bool IsMouseInWindow(const IWindowPtr& window) const override;
private:
	sf::Mouse m_mouse;
};

