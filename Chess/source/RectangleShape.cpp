#include "RectangleShape.h"

Pos RectangleShape::GetPosition() const
{
	sf::Vector2f pos = m_shape.getPosition();
	return Pos(static_cast<int>(pos.x), static_cast<int>(pos.y));
}

void RectangleShape::SetOutlineThickness(int thickness)
{
	m_shape.setOutlineThickness(static_cast<float>(thickness));
}

void RectangleShape::SetOutlineColor(Color color)
{
	m_shape.setOutlineColor(sf::Color{ color.red, color.green, color.blue });
}

void RectangleShape::SetTexture(std::unique_ptr<ITexture> texture)
{
	m_shape.setTexture(texture);
}

void RectangleShape::SetPosition(Pos pos)
{
	m_shape.setPosition({ pos.x, pos.y });
}

void RectangleShape::SetSize(Size size)
{
	m_shape.setPosition({ size.x, size.y });
}
