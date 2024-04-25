//#include "interface/IRectangleShape.h"
#include "Game.h"
#include "Board.h"
#include "Cell.h"
#include "Helper.h"
#include "Texture.h"
#include "Window.h"

int main()
{
	Game chess(textures::CreateTextures(), std::make_unique<Board>(std::make_unique<Cell>()), std::make_unique<Window>());
	chess.Update();
	return 0;
}