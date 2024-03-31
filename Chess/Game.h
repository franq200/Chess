#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	void Update();
private:
	void Draw();
	void Events();
	void LoadTextures();
	sf::RenderWindow m_window;
};

