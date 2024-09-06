#pragma once
#include <gmock/gmock.h>
#include "interface/IFigure.h"

class FigureMock : public IFigure
{
	MOCK_METHOD(bool, IsInRange, (Pos mousePos), (override));
	MOCK_METHOD(void, SetOutlineThickness, (int thickness), (override));
	MOCK_METHOD(void, SetOutlineColor, (Color color), (override));
	MOCK_METHOD(void, Draw, (std::unique_ptr<IWindow>& window), (override));
	MOCK_METHOD(void, SetPosition, (Pos pos), (override));
	MOCK_METHOD(Pos, GetPosition, (), (const, override));
	MOCK_METHOD(Pos, GetPixelPosition, (), (const, override));
	MOCK_METHOD(std::vector<Pos>, CalculatePossibleMoves, (const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures), (override));
	MOCK_METHOD(void, ChangeTempPos, (const Pos& tempPos), (override));
	MOCK_METHOD(void, SetCurrentPos, (), (override));
	MOCK_METHOD(Pos, GetPixelTempPosition, (), (const, override));
	MOCK_METHOD(bool, IsInPossibleMoves, (const Pos& destinationPos), (const, override));
	MOCK_METHOD(Pos, GetCellTempPosition, (), (const, override));
	MOCK_METHOD(void, OnAnimation, (), (override));
	MOCK_METHOD(bool, IsFigureTaking, (Pos destinationCell, const FiguresVector& opponentPlayerFigures), (const, override));
};

