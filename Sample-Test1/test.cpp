#include "gtest/gtest.h"
#include "TextureMock.h"
#include "WindowMock.h"
#include "BoardMock.h"
#include "Game.h"

std::array<std::unique_ptr<ITexture>, 14> CreateTextures()
{
	std::array<std::unique_ptr<ITexture>, 14> textures;
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i] = std::make_unique<TextureMock>();
	}
	return textures;
}


TEST(GameTest, AreTexturesBeingLoaded)
{
	//Game game(CreateTextures(), std::make_unique<BoardMock>(), std::make_unique<WindowMock>());
}