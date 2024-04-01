#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class ITexture;

class Game
{
public:
	Game(std::unique_ptr<ITexture> texture);
	void Update();
private:
	void Draw();
	void Events();
	void LoadTextures();
	sf::RenderWindow m_window;
	std::unique_ptr<ITexture> m_texture;
};

