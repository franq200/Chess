#include <SFML/Graphics.hpp>
#include "ITexture.h"

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
}

