#pragma once
#include <SFML/Graphics.hpp>
#include "interface/IRectangleShape.h"

class RectangleShape : public IRectangleShape
{
public:
	const Pos& GetPosition() const override;
private:
	sf::RectangleShape m_shape;
};

