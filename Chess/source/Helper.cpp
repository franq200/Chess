#include "Helper.h"
#include "Texture.h"

namespace textures
{
	std::unique_ptr<ITexture> blackPawn;
	std::unique_ptr<ITexture> blackQueen;
	std::unique_ptr<ITexture> blackKing;
	std::unique_ptr<ITexture> blackKnight;
	std::unique_ptr<ITexture> blackRook;
	std::unique_ptr<ITexture> blackBishop;

	std::unique_ptr<ITexture> whitePawn;
	std::unique_ptr<ITexture> whiteQueen;
	std::unique_ptr<ITexture> whiteKing;
	std::unique_ptr<ITexture> whiteKnight;
	std::unique_ptr<ITexture> whiteRook;
	std::unique_ptr<ITexture> whiteBishop;

	std::array<std::unique_ptr<ITexture>, 12> CreateTextures()
	{
		std::array<std::unique_ptr<ITexture>, 12> textures;
		for (int i = 0; i < textures.size(); i++)
		{
			textures[i] = std::make_unique<Texture>();
		}
		return textures;
	}
}

Pos::Pos(int newX, int newY):
	x(newX), y(newY)
{
}



namespace size
{
	int cellSizeX = 50;
	int cellSizeY = 50;
}