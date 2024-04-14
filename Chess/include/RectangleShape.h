#pragma once
#include <SFML/Graphics.hpp>
#include "interface/IRectangleShape.h"

class RectangleShape : public IRectangleShape
{
public:
private:
	sf::RectangleShape m_shape;
};

