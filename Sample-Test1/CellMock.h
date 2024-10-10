#pragma once
#include <gmock/gmock.h>
#include "interface/ICell.h"
#include "interface/IWindow.h"

class CellMock : public ICell
{
public:
    MOCK_METHOD(void, SetFillColor, (Color color), (override));
    MOCK_METHOD(void, SetPosition, (Pos pos), (override));
    MOCK_METHOD(void, SetSize, (Size size), (override));
    MOCK_METHOD(void, SetFigure, (IFigurePtr figure), (override));
    MOCK_METHOD(void, RemoveFigure, (), (override));
    MOCK_METHOD(IFigurePtr, GetFigure, (), (const, override));
    MOCK_METHOD(bool, IsOccupiedByPlayer, (const IPlayerPtr& currentColor), (const, override));
    MOCK_METHOD(void, Highlight, (), (override));
    MOCK_METHOD(void, HighlightAsTaking, (), (override));
    MOCK_METHOD(void, RemoveHighlight, (), (override));
    MOCK_METHOD(void, DrawCells, (IWindowPtr& window), (override));
    MOCK_METHOD(void, DrawFigures, (IWindowPtr& window), (override));
    MOCK_METHOD(void, DrawHighlights, (IWindowPtr& window), (override));
};

