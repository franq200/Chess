#include "gtest/gtest.h"
#include "TextureMock.h"
#include "WindowMock.h"
#include "BoardMock.h"
#include "PlayerMock.h"
#include "FigureMock.h"
#include "CellMock.h"
#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Helper.h"
#include "MouseMock.h"

namespace
{
	std::array<ICellPtr, 64> CreateCells()
	{
		std::array<ICellPtr, 64> cells;
		for (int i = 0; i < cells.size(); i++)
		{
			cells[i] = std::make_unique<testing::NiceMock<CellMock>>();
		}
		return cells;
	}

	FiguresVector CreateFigures()
	{
		FiguresVector figures;
		for (int i = 0; i < 16; i++)
		{
			figures.push_back(std::make_shared<testing::NiceMock<FigureMock>>());
		}
		return figures;
	}

	TexturesMap CreateTextures()
	{
		TexturesMap textures;
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
}

class BasicChessTests : public testing::Test
{
protected:
	std::unique_ptr<testing::NiceMock<BoardMock>> boardMock{ std::make_unique<testing::NiceMock<BoardMock>>() };
	std::unique_ptr<testing::NiceMock<WindowMock>> windowMock{ std::make_unique<testing::NiceMock<WindowMock>>() };
	std::unique_ptr<testing::NiceMock<MouseMock>> mouseMock{ std::make_unique<testing::NiceMock<MouseMock>>() };
	std::unique_ptr<testing::NiceMock<PlayerMock>> white = std::make_unique<testing::NiceMock<PlayerMock>>();
	std::unique_ptr<testing::NiceMock<PlayerMock>> black = std::make_unique<testing::NiceMock<PlayerMock>>();
	TexturesMap texturesMock = CreateTextures();
};

class GameTest : public BasicChessTests
{
protected:
	Game createSut()
	{
		Game game(texturesMock, std::move(boardMock), std::move(windowMock), std::move(mouseMock), std::move(white), std::move(black));
		return game;
	}

	void ExpectWhitePlayerFigures(const FiguresVector& figures)
	{
		EXPECT_CALL(*white, GetFigures()).Times(testing::AtLeast(1)).WillRepeatedly(testing::ReturnRefOfCopy(figures));
	}

	void ExpectBlackPlayerFigures(const FiguresVector& figures)
	{
		EXPECT_CALL(*black, GetFigures()).Times(testing::AtLeast(1)).WillRepeatedly(testing::ReturnRefOfCopy(figures));
	}

	void ExpectTexturesLoaded()
	{
		for (auto& [key, texture] : texturesMock)
		{
			EXPECT_CALL(dynamic_cast<TextureMock&>(*texture), LoadFromFile(testing::_)).Times(1).WillOnce(testing::Return(true));
		}
	}

	void ExpectSomeTexturesToFail(int amountOfTexturesToFail)
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
};

TEST_F(GameTest, AreTexturesBeingLoaded)
{
	ExpectTexturesLoaded();
	Game game = createSut();
}

TEST_F(GameTest, DoesTexturesDetectIfOneTextureFailsToLoadAndThrowException)
{
	ExpectSomeTexturesToFail(1);
	EXPECT_THROW(Game game = createSut(), std::exception);
}

TEST_F(GameTest, DoesTexturesDetectIfFiveTextureFailsToLoadAndThrowException)
{
	ExpectSomeTexturesToFail(5);
	EXPECT_THROW(Game game = createSut(), std::exception);
}

TEST_F(GameTest, WindowClearAndDisplayFunctionsShouldBeCalledAsLongAsFunctionIsOpenReturnTrue)
{
	ExpectTexturesLoaded();
	ExpectBlackPlayerFigures(CreateFigures());
	EXPECT_CALL(*windowMock, IsOpen()).Times(4).WillOnce(testing::Return(true)).WillOnce(testing::Return(true)).WillOnce(testing::Return(true)).WillOnce(testing::Return(false));
	EXPECT_CALL(*mouseMock, IsMouseInWindow(testing::_)).Times(4).WillOnce(testing::Return(true)).WillOnce(testing::Return(true)).WillOnce(testing::Return(true)).WillOnce(testing::Return(true));
	EXPECT_CALL(*windowMock, Clear()).Times(3);
	EXPECT_CALL(*boardMock, Draw(testing::_)).Times(3);
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

class GetCellIndexParameterizedTestFixtureCorrectNumbers : public ::testing::TestWithParam<Parameters> {};

TEST_P(GetCellIndexParameterizedTestFixtureCorrectNumbers, GetCellIndexTestCorrectNumbers)
{
	Parameters parameters = GetParam();
	EXPECT_EQ(functions::GetCellIndex(parameters.index), parameters.result);
}

INSTANTIATE_TEST_SUITE_P(GetCellIndexTestCorrectNumbers, GetCellIndexParameterizedTestFixtureCorrectNumbers, ::testing::Values(
	Parameters{ {7, 1}, 15 },
	Parameters{ {1, 4}, 33 },
	Parameters{ {3, 7}, 59 },
	Parameters{ {7, 7}, 63 },
	Parameters{ {0, 0}, 0 },
	Parameters{ {1, 1}, 9 },
	Parameters{ {5, 5}, 45 }
));


class GetCellIndexParameterizedTestFixtureWrongNumbers : public ::testing::TestWithParam<Parameters> {};

TEST_P(GetCellIndexParameterizedTestFixtureWrongNumbers, GetCellIndexTestWrongNumbers)
{
	Parameters parameters = GetParam();
	EXPECT_THROW(functions::GetCellIndex(parameters.index), std::exception);
}

INSTANTIATE_TEST_SUITE_P(GetCellIndexTestWrongNumbers, GetCellIndexParameterizedTestFixtureWrongNumbers, ::testing::Values(
	Parameters{ {8, 4}, 34 },
	Parameters{ {3, 8}, 1 },
	Parameters{ {9, 9}, 16 }
));


class BoardTest : public BasicChessTests
{
protected:
	Board CreateSut()
	{
		Board board(std::move(cellsMock), texturesMock);
		return board;
	}
	std::array <ICellPtr, 64> cellsMock = CreateCells();
};

TEST_F(BoardTest, jjjj)
{
	Pos expectedPos = Pos(0, 0);
	testing::NiceMock<CellMock>* expectedMock = dynamic_cast<testing::NiceMock<CellMock>*>(cellsMock[functions::GetCellIndex(expectedPos)].get());
	EXPECT_TRUE( expectedMock != nullptr);
    EXPECT_CALL(*expectedMock, IsOccupiedByPlayer(testing::_)).WillOnce(testing::Return(true));
//	EXPECT_CALL(*cellsMock[functions::GetCellIndex(expectedPos)], IsOccupiedByPlayer(testing::_)).WillOnce(testing::Return(true));
	Board board = CreateSut();

	board.IsCellOccupied(Pos(0, 0), std::move(white));
}

class PlayerTest : public BasicChessTests
{
protected:
	Player CreateSut()
	{
		Player player;
		return player;
	}
};