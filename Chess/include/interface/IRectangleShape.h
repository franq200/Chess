#pragma once
#include <SFML/Graphics.hpp>
#include "Helper.h"

class IRectangleShape : public sf::Drawable
{
public:
	~IRectangleShape() = default;
	virtual Pos GetPosition() const = 0;
};

