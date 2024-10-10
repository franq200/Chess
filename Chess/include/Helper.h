#pragma once
#include <map>
#include <memory>
#include <string>
#include <array>

class ITexture;
using ITexturePtr = std::unique_ptr<ITexture>;
class ICell;
using ICellPtr = std::unique_ptr<ICell>;
using FigureName = std::string;
using TexturesMap = std::map<FigureName, ITexturePtr>;

namespace textures
{
	extern ITexturePtr blackPawn;
	extern ITexturePtr blackQueen;
	extern ITexturePtr blackKing;
	extern ITexturePtr blackKnight;
	extern ITexturePtr blackRook;
	extern ITexturePtr blackBishop;

	extern ITexturePtr whitePawn;
	extern ITexturePtr whiteQueen;
	extern ITexturePtr whiteKing;
	extern ITexturePtr whiteKnight;
	extern ITexturePtr whiteRook;
	extern ITexturePtr whiteBishop;

	extern ITexturePtr boardGrey;
	extern ITexturePtr boardRed;

	__declspec(dllexport) TexturesMap CreateTextures();
}

struct Pos
{
	Pos() = default;
	__declspec(dllexport) Pos(int16_t newX, int16_t newY);
	__declspec(dllexport) bool operator == (const Pos& pos) const;
	int16_t x = 0;
	int16_t y = 0;
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

namespace functions
{
	__declspec(dllexport) Pos GetPixelPosFromCellPos(Pos pos);
	__declspec(dllexport) Pos GetCellPosFromPixelPos(Pos pos);

	__declspec(dllexport) int GetCellIndex(Pos posIndex);

	__declspec(dllexport) std::array<ICellPtr, 64> CreateCells();
}