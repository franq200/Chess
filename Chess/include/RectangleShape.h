#pragma once
#include <SFML/Graphics.hpp>
#include "interface/IRectangleShape.h"

class RectangleShape : public IRectangleShape
{
public:
	__declspec(dllexport) Pos GetPosition() const override;
	__declspec(dllexport) void SetOutlineThickness(int thickness) override;
	__declspec(dllexport) void SetOutlineColor(Color color) override;
	__declspec(dllexport) void SetTexture(const ITexture& texture) override;
	__declspec(dllexport) void SetPixelPosition(Pos pos) override;
	__declspec(dllexport) void SetSize(Size size) override;
	__declspec(dllexport) void SetFillColor(Color color) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	__declspec(dllexport) Pos GetPixelTempPosition() const override;
	__declspec(dllexport) Pos GetCellTempPosition() const override;
private:
	sf::RectangleShape m_shape;
};

