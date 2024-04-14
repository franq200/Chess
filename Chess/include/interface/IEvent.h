#pragma once
#include <SFML/Graphics.hpp>

class IEvent: public sf::Event
{
public:
	~IEvent() = default;
};

