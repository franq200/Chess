#include "Helper.h"
#include "Texture.h"
#include "Cell.h"

namespace textures
{
	TexturesMap CreateTextures()
	{
		TexturesMap textures;
		textures["blackPawn"] = std::make_unique<Texture>();
		textures["blackQueen"] = std::make_unique<Texture>();
		textures["blackKing"] = std::make_unique<Texture>();
		textures["blackKnight"] = std::make_unique<Texture>();
		textures["blackRook"] = std::make_unique<Texture>();
		textures["blackBishop"] = std::make_unique<Texture>();

		textures["whitePawn"] = std::make_unique<Texture>();
		textures["whiteQueen"] = std::make_unique<Texture>();
		textures["whiteKing"] = std::make_unique<Texture>();
		textures["whiteKnight"] = std::make_unique<Texture>();
		textures["whiteRook"] = std::make_unique<Texture>();
		textures["whiteBishop"] = std::make_unique<Texture>();

		textures["boardGrey"] = std::make_unique<Texture>();
		textures["boardRed"] = std::make_unique<Texture>();
		return textures;
	}
}

Pos::Pos(int16_t newX, int16_t newY):
	x(newX), y(newY)
{
}

bool Pos::operator==(const Pos& pos) const
{
	return pos.x == x && pos.y == y;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) :
	red(r), green(g), blue(b)
{
}

namespace size
{
	uint16_t boardCellsX = 8;
	uint16_t boardCellsY = 8;
	uint16_t windowSizeXPix = 1000;
	uint16_t windowSizeYPix = 1000;
	uint16_t cellSizeXPix = windowSizeXPix/boardCellsX;
	uint16_t cellSizeYPix = windowSizeYPix/boardCellsY;
}

Size::Size(uint16_t newX, uint16_t newY):
	x(newX), y(newY)
{
}

Pos GetPixelPosFromCellPos(Pos pos)
{
	return Pos(pos.x * size::cellSizeXPix, pos.y * size::cellSizeYPix);
}

Pos GetCellPosFromPixelPos(Pos pos)
{
	return Pos(pos.x / size::cellSizeXPix, pos.y / size::cellSizeYPix);
}

int GetCellIndex(Pos posIndex)
{
	if (posIndex.x >= 8 || posIndex.y >= 8 || posIndex.x < 0 || posIndex.y < 0)
	{
		throw(std::exception("too big position index"));
	}
	return posIndex.x + posIndex.y * 8;
}

std::array<ICellPtr, 64> CreateCells()
{
	std::array<ICellPtr, 64> cells;
	for (int i = 0; i < cells.size(); i++)
	{
		cells[i] = std::make_unique<Cell>();
	}
	return cells;
}