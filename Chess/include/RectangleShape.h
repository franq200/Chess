#pragma once
#include <SFML/Graphics.hpp>
#include "interface/IRectangleShape.h"

class RectangleShape : public IRectangleShape
{
public:
	Pos GetPosition() const override;
	void SetOutlineThickness(int thickness) override;
	void SetOutlineColor(Color color) override;
	void SetTexture(const ITexture& texture) override;
	void SetPosition(Pos pos) override;
	void SetSize(Size size) override;
private:
	sf::RectangleShape m_shape;
};

