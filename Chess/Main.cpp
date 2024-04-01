#include "Game.h"
#include "Texture.h"

int main()
{
	Game chess(std::move(std::make_unique<Texture>()));
	chess.Update();
	return 0;
}