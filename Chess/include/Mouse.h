#pragma once
#include "interface\IMouse.h"
#include "SFML/Graphics.hpp"

class Mouse : public IMouse
{
public:
	__declspec(dllexport) bool IsButtonPressed(Button button) const override;
	__declspec(dllexport) Pos GetPosition() override;
private:
	sf::Mouse m_mouse;
};

