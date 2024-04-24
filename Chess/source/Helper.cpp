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

	std::unique_ptr<ITexture> boardGrey;
	std::unique_ptr<ITexture> boardRed;

	std::array<std::unique_ptr<ITexture>, 14> CreateTextures()
	{
		std::array<std::unique_ptr<ITexture>, 14> textures;
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

Color::Color(uint8_t r, uint8_t g, uint8_t b) :
	red(r), green(g), blue(b)
{
}

namespace size
{
	int cellSizeX = 50;
	int cellSizeY = 50;
}

Size::Size(int newX, int newY):
	x(newX), y(newY)
{
}
