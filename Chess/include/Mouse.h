#pragma once
#include "interface\IMouse.h"
#include <SFML/Graphics.hpp>
#include <map>

class Mouse : public IMouse
{
public:
	__declspec(dllexport) Mouse();
	__declspec(dllexport) bool IsButtonPressed(Button button) const override;
	__declspec(dllexport) Pos GetCellPosition(const IWindowPtr& window) override;
	__declspec(dllexport) Pos GetPixelPosition(const IWindowPtr& window) override;
	__declspec(dllexport) bool IsMouseInWindow(const IWindowPtr& window) const override;
	__declspec(dllexport) bool WasButtonPressed(Button button) const override;
	__declspec(dllexport) void Update(UpdateType type) override;
private:
	sf::Mouse m_mouse;
	std::map<Button, State> m_buttonsState;
};

