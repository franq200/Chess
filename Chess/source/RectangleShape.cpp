#include "RectangleShape.h"
#include "interface/ITexture.h"

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

void RectangleShape::SetTexture(const ITexture& texture)
{
	m_shape.setTexture(texture.GetTexture());
}

void RectangleShape::SetPosition(Pos pos)
{
	m_shape.setPosition({ static_cast<float>(pos.x), static_cast<float>(pos.y) });
}

void RectangleShape::SetSize(Size size)
{
	m_shape.setSize({ static_cast<float>(size.x), static_cast<float>(size.y) });
}

void RectangleShape::SetFillColor(Color color)
{
	m_shape.setFillColor(sf::Color{ color.red, color.green, color.blue });
}

void RectangleShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_shape, states);
}
