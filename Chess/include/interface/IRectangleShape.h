#pragma once
#include <SFML/Graphics.hpp>
#include "Helper.h"
#include <memory>

class ITexture;

class IRectangleShape : public sf::Drawable
{
public:
	virtual ~IRectangleShape() = default;
	virtual void SetOutlineThickness(int thickness) = 0;
	virtual void SetOutlineColor(Color color) = 0;
	virtual Pos GetPosition() const = 0;
	virtual void SetTexture(const ITexture& texture) = 0;
	virtual void SetPosition(Pos pos) = 0;
	virtual void SetSize(Size size) = 0;
	virtual void SetFillColor(Color color) = 0;
	virtual void SetTempPos(const Pos& tempPos) = 0;
	virtual void SetCurrentPos() = 0;
	virtual const Pos& GetPixelTempPosition() const = 0;
	virtual const Pos& GetCellTempPosition() const = 0;
};

