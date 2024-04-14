#pragma once
#include <SFML/Graphics.hpp>
#include "interface/IGame.h"
#include <memory>
#include <array>

class ITexture;
class IBoard;

class Game : public IGame
{
public:
	Game(std::array<std::unique_ptr<ITexture>, 12> texture, std::unique_ptr<IBoard> board);
	void Update() override;
private:
	void Draw();
	void Events();
	void LoadTextures(std::array<std::unique_ptr<ITexture>, 12>&);
	sf::RenderWindow m_window;
	std::unique_ptr<IBoard> m_board;
};

