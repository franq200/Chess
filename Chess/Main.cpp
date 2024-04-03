#include "Game.h"
#include "Texture.h"
#include "Board.h"

int main()
{
	Game chess(std::move(std::make_unique<Texture>()), std::move(std::make_unique<Board>()));
	chess.Update();
	return 0;
}