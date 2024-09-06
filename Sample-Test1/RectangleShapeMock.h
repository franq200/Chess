#pragma once
#include <gmock/gmock.h>
#include "interface/IRectangleShape.h"

class RectangleShapeMock : public IRectangleShape
{
public:
	MOCK_METHOD(void, SetOutlineThickness, (int thickness), (override));
	MOCK_METHOD(void, SetOutlineColor, (Color color), (override));
	MOCK_METHOD(Pos, GetPosition, (), (const, override));
	MOCK_METHOD(void, SetTexture, (const ITexture& texture), (override));
	MOCK_METHOD(void, SetPosition, (Pos pos), (override));
	MOCK_METHOD(void, SetSize, (Size size), (override));
	MOCK_METHOD(void, SetFillColor, (Color color), (override));
	MOCK_METHOD(void, SetTempPos, (const Pos& tempPos), (override));
	MOCK_METHOD(void, SetCurrentPos, (), (override));
	MOCK_METHOD(Pos, GetPixelTempPosition, (), (const, override));
	MOCK_METHOD(Pos, GetCellTempPosition, (), (const, override));
	MOCK_METHOD(void, OnAnimation, (), (override));
};