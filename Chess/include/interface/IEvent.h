#pragma once
#include <SFML/Graphics.hpp>

class IEvent: public sf::Event
{
public:
	virtual ~IEvent() = default;
};

