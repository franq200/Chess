#include "RectangleShape.h"

const Pos& RectangleShape::GetPosition() const
{
	sf::Vector2f pos = m_shape.getPosition();
	return Pos(static_cast<int>(pos.x), static_cast<int>(pos.y));
}
