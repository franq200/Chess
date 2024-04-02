#pragma once
#include "ICell.h"
#include <SFML/Graphics.hpp>

class Cell : public ICell
{
public:
	void Draw(std::unique_ptr<IWindow> window) override;
private:
	sf::RectangleShape m_cell;
};

