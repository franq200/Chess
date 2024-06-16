#include "Game.h"
#include "Board.h"
#include "Cell.h"
#include "Helper.h"
#include "Texture.h"
#include "Mouse.h"
#include "Window.h"
#include "Player.h"

int main()
{
	TextureContainer textures = textures::CreateTextures();
	std::pair<std::unique_ptr<IPlayer>, std::unique_ptr<IPlayer>> players;
	players.first = std::make_unique<Player>();
	players.second = std::make_unique<Player>();
	Game chess(textures, std::make_unique<Board>(CreateCells(), textures), std::make_unique<Window>(), std::make_unique<Mouse>(), players);
	chess.Update();
	return 0;
}