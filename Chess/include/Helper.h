#pragma once
#include <map>
#include <memory>
#include <string>
#include <array>

class ITexture;
class ICell;
using FigureName = std::string;
using TextureContainer = std::map<FigureName, std::unique_ptr<ITexture>>;

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

	__declspec(dllexport) TextureContainer CreateTextures();
}

struct Pos
{
	Pos() = default;
	__declspec(dllexport) Pos(uint16_t newX, uint16_t newY);
	__declspec(dllexport) bool operator == (const Pos& pos) const;
	uint16_t x = 0;
	uint16_t y = 0;
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
	Size(uint16_t newX, uint16_t newY);
	uint16_t x = 0;
	uint16_t y = 0;
};

namespace size
{
	extern uint16_t boardCellsX;
	extern uint16_t boardCellsY;
	extern uint16_t windowSizeXPix;
	extern uint16_t windowSizeYPix;
	extern uint16_t cellSizeXPix;
	extern uint16_t cellSizeYPix;
}

__declspec(dllexport) Pos GetPixelPosFromCellPos(Pos pos);
__declspec(dllexport) Pos GetCellPosFromPixelPos(Pos pos);

__declspec(dllexport) int GetCellIndex(Pos posIndex);

__declspec(dllexport) std::array<std::unique_ptr<ICell>, 64> CreateCells();