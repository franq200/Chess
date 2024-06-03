#include "gtest/gtest.h"
#include "TextureMock.h"
#include "WindowMock.h"
#include "BoardMock.h"
#include "Game.h"
#include "Helper.h"
#include "MouseMock.h"


TextureContainer CreateTextures()
{
	TextureContainer textures;
	textures["blackPawn"] = std::make_unique<TextureMock>();
	textures["blackQueen"] = std::make_unique<TextureMock>();
	textures["blackKing"] = std::make_unique<TextureMock>();
	textures["blackKnight"] = std::make_unique<TextureMock>();
	textures["blackRook"] = std::make_unique<TextureMock>();
	textures["blackBishop"] = std::make_unique<TextureMock>();
	textures["whitePawn"] = std::make_unique<TextureMock>();
	textures["whiteQueen"] = std::make_unique<TextureMock>();
	textures["whiteKing"] = std::make_unique<TextureMock>();
	textures["whiteKnight"] = std::make_unique<TextureMock>();
	textures["whiteRook"] = std::make_unique<TextureMock>();
	textures["whiteBishop"] = std::make_unique<TextureMock>();
	textures["boardGrey"] = std::make_unique<TextureMock>();
	textures["boardRed"] = std::make_unique<TextureMock>();
	return textures;
}

class BasicChessTests : public testing::Test
{
protected:
	std::unique_ptr<testing::NiceMock<BoardMock>> boardMock{ std::make_unique<testing::NiceMock<BoardMock>>() };
	std::unique_ptr<testing::NiceMock<WindowMock>> windowMock{ std::make_unique<testing::NiceMock<WindowMock>>() };
	std::unique_ptr<testing::NiceMock<MouseMock>> mouseMock{ std::make_unique<testing::NiceMock<MouseMock>>() };
	TextureContainer texturesMock = CreateTextures();
};

class GameTest : public BasicChessTests
{
protected:
	Game createSut()
	{
		Game game(texturesMock, std::move(boardMock), std::move(windowMock), std::move(mouseMock));
		return game;
		//return { std::move(texturesMock), std::move(boardMock), std::move(windowMock) };
	}
};

void ExpectTexturesLoaded(TextureContainer& texturesMock)
{
	for (auto& [key, texture] : texturesMock)
	{
		EXPECT_CALL(dynamic_cast<TextureMock&>(*texture), LoadFromFile(testing::_)).Times(1).WillOnce(testing::Return(true));
	}
}

void ExpectSomeTexturesToFail(TextureContainer& texturesMock, int amountOfTexturesToFail)
{
	int i = 0;
	for (auto& [key, texture] : texturesMock)
	{
		if (i < amountOfTexturesToFail)
		{
			EXPECT_CALL(dynamic_cast<TextureMock&>(*texture), LoadFromFile(testing::_)).Times(1).WillOnce(testing::Return(false));
		}
		else
		{
			EXPECT_CALL(dynamic_cast<TextureMock&>(*texture), LoadFromFile(testing::_)).Times(1).WillOnce(testing::Return(true));
		}
		i++;
	}
}

TEST_F(GameTest, AreTexturesBeingLoaded)
{
	ExpectTexturesLoaded(texturesMock);
	Game game = createSut();
}

TEST_F(GameTest, DoesTexturesDetectIfOneTextureFailsToLoadAndThrowException)
{
	ExpectSomeTexturesToFail(texturesMock, 1);
	EXPECT_THROW(Game game = createSut(), std::exception);
}

TEST_F(GameTest, DoesTexturesDetectIfFiveTextureFailsToLoadAndThrowException)
{
	ExpectSomeTexturesToFail(texturesMock, 5);
	EXPECT_THROW(Game game = createSut(), std::exception);
}

TEST_F(GameTest, WindowClearAndDisplayFunctionsShouldBeCalledAsLongAsFunctionIsOpenReturnTrue)
{
	ExpectTexturesLoaded(texturesMock);
	EXPECT_CALL(*windowMock, IsOpen()).Times(4).WillOnce(testing::Return(true)).WillOnce(testing::Return(true)).WillOnce(testing::Return(true)).WillOnce(testing::Return(false));
	EXPECT_CALL(*windowMock, Clear()).Times(3);
	EXPECT_CALL(*windowMock, Display()).Times(3);
	EXPECT_CALL(*windowMock, PollEvent(testing::_)).Times(testing::AtLeast(1));
	Game game = createSut();
	game.Update();
}

struct GetCellIndexFixture : public ::testing::Test
{
};

struct Parameters
{
	Pos index;
	int result = 0;
};

class GetCellIndexParameterizedTestFixtureCorrectNumbers : public ::testing::TestWithParam<Parameters>{};

TEST_P(GetCellIndexParameterizedTestFixtureCorrectNumbers, GetCellIndexTestCorrectNumbers)
{
	Parameters parameters = GetParam();
	EXPECT_EQ(GetCellIndex(parameters.index), parameters.result);
}

INSTANTIATE_TEST_SUITE_P(GetCellIndexTestCorrectNumbers, GetCellIndexParameterizedTestFixtureCorrectNumbers, ::testing::Values(
	Parameters{ {7, 1}, 15},
	Parameters{ {1, 4}, 33},
	Parameters{ {3, 7}, 59},
	Parameters{ {7, 7}, 63},
	Parameters{ {0, 0}, 0},
	Parameters{ {1, 1}, 9},
	Parameters{ {5, 5}, 45}
));

class GetCellIndexParameterizedTestFixtureWrongNumbers : public ::testing::TestWithParam<Parameters> {};

TEST_P(GetCellIndexParameterizedTestFixtureWrongNumbers, GetCellIndexTestWrongNumbers)
{
	Parameters parameters = GetParam();
	EXPECT_THROW(GetCellIndex(parameters.index), std::exception);
}

INSTANTIATE_TEST_SUITE_P(GetCellIndexTestWrongNumbers, GetCellIndexParameterizedTestFixtureWrongNumbers, ::testing::Values(
	Parameters{ {8, 4}, 34 },
	Parameters{ {3, 8}, 1 },
	Parameters{ {9, 9}, 16 }
));