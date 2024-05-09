#pragma once
#include <array>
#include <memory>

class ITexture;
class ICell;

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

	extern std::unique_ptr<ITexture> boardGrey;
	extern std::unique_ptr<ITexture> boardRed;

	__declspec(dllexport) std::array<std::unique_ptr<ITexture>, 14> CreateTextures();
}

struct Pos
{
	Pos() = default;
	Pos(int newX, int newY);
	int x = 0;
	int y = 0;
};

struct Color
{
	Color() = default;
	Color(uint8_t r, uint8_t g, uint8_t b);
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;
};

struct Size
{
	Size() = default;
	Size(int newX, int newY);
	int x = 0;
	int y = 0;
};

namespace size
{
	extern int cellSizeX;
	extern int cellSizeY;
}

__declspec(dllexport) int GetCellIndex(Pos index2Int);

__declspec(dllexport) std::array<std::unique_ptr<ICell>, 64> CreateCells();