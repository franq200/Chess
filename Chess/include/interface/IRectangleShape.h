#pragma once
#include <SFML/Graphics.hpp>
#include "Helper.h"
#include <memory>

class ITexture;

class IRectangleShape : public sf::Drawable
{
public:
	~IRectangleShape() = default;
	virtual void SetOutlineThickness(int thickness) = 0;
	virtual void SetOutlineColor(Color color) = 0;
	virtual Pos GetPosition() const = 0;
	virtual void SetTexture(std::unique_ptr<ITexture> texture) = 0;
	virtual void SetPosition(Pos pos) = 0;
	virtual void SetSize(Size size) = 0;
};

