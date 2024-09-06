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
	MOCK_METHOD(void, SetFigure, (std::shared_ptr<IFigure> figure), (override));
	MOCK_METHOD(void, RemoveFigure, (), (override));
	MOCK_METHOD(std::shared_ptr<IFigure>, GetFigure, (), (const, override));
	MOCK_METHOD(bool, IsOccupiedByPlayer, (const std::unique_ptr<IPlayer>& currentColor), (const, override));
	MOCK_METHOD(void, Highlight, (), (override));
	MOCK_METHOD(void, HighlightAsTaking, (), (override));
	MOCK_METHOD(void, RemoveHighlight, (), (override));
	MOCK_METHOD(void, DrawCells, (std::unique_ptr<IWindow>& window), (override));
	MOCK_METHOD(void, DrawFigures, (std::unique_ptr<IWindow>& window), (override));
};

