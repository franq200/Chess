#pragma once
#include <gmock/gmock.h>
#include "interface/IFigure.h"

class FigureMock : public IFigure
{
public:
    MOCK_METHOD(bool, IsInRange, (Pos mousePos), (override));
    MOCK_METHOD(void, SetOutlineThickness, (int thickness), (override));
    MOCK_METHOD(void, SetOutlineColor, (Color color), (override));
    MOCK_METHOD(void, Draw, (IWindowPtr& window), (override));
    MOCK_METHOD(void, SetPixelPosition, (Pos pos), (override));
    MOCK_METHOD(Pos, GetPosition, (), (const, override));
    MOCK_METHOD(std::vector<Pos>, CalculatePossibleMoves, (const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures), (override));
    MOCK_METHOD(void, SetShapePos, (const Pos& tempPos), (override));
    MOCK_METHOD(void, RestorePositionBeforeAnimation, (), (override));
    MOCK_METHOD(Pos, GetPixelTempPosition, (), (const, override));
    MOCK_METHOD(bool, IsInPossibleMoves, (const Pos& destinationPos), (const, override));
    MOCK_METHOD(Pos, GetCellTempPosition, (), (const, override));
    MOCK_METHOD(bool, IsFigureTaking, (Pos destinationCell, const FiguresVector& opponentPlayerFigures), (const, override));
    MOCK_METHOD(std::shared_ptr<IFigure>, Clone, (), (const, override));
};

