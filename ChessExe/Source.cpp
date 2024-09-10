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
	TexturesMap textures = textures::CreateTextures();
	Game chess(textures, std::make_unique<Board>(CreateCells(), textures), std::make_unique<Window>(), std::make_unique<Mouse>(), std::make_unique<Player>(), std::make_unique<Player>());
	chess.Update();
	return 0;
}