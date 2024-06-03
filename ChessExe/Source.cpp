#include "Game.h"
#include "Board.h"
#include "Cell.h"
#include "Helper.h"
#include "Texture.h"
#include "Mouse.h"
#include "Window.h"

int main()
{
	TextureContainer textures = textures::CreateTextures();
	Game chess(textures, std::make_unique<Board>(CreateCells(), textures), std::make_unique<Window>(), std::make_unique<Mouse>());
	chess.Update();
	return 0;
}