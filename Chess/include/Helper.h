#pragma once
#include <array>
#include <memory>

class ITexture;

namespace textures
{
	extern std::unique_ptr<ITexture> blackPawn;
	extern std::unique_ptr<ITexture> blackQueen;
	extern std::unique_ptr<ITexture> blackKing;
	extern std::unique_ptr<ITexture> blackKnight;
	extern std::unique_ptr<ITexture> blackRook;
	extern std::unique_ptr<ITexture> blackBishop;

	extern std::unique_ptr<ITexture> whitePawn;
	extern std::unique_ptr<ITexture> whiteQueen;
	extern std::unique_ptr<ITexture> whiteKing;
	extern std::unique_ptr<ITexture> whiteKnight;
	extern std::unique_ptr<ITexture> whiteRook;
	extern std::unique_ptr<ITexture> whiteBishop;

	std::array<std::unique_ptr<ITexture>, 12> CreateTextures();
}

struct Pos
{
	Pos() = default;
	Pos(int newX, int newY);
	int x = 0;
	int y = 0;
};

namespace size
{
	extern int cellSizeX;
	extern int cellSizeY;
}