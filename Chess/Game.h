#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "IGame.h"

class ITexture;
class IBoard;

class Game : public IGame
{
public:
	Game(std::unique_ptr<ITexture> texture, std::unique_ptr<IBoard> board);
	void Update() override;
private:
	void Draw();
	void Events();
	void LoadTextures();
	sf::RenderWindow m_window;
	std::unique_ptr<ITexture> m_texture;
	std::unique_ptr<IBoard> m_board;
};

