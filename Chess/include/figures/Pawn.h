#pragma once
#include <memory>
#include "Figure.h"

enum class MoveDirection : int8_t
{
	up = -1,
	down = 1,
	unknown = 0
};

class Pawn : public Figure
{
public:
	Pawn() = default;
	Pawn(const ITexture& texture, Pos pos, Size size);
	__declspec(dllexport) bool IsMovePossible(Pos moveCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const override;
private:
	bool IsPromotion(Pos moveCell);
	void SetDirectionBasedOnStartingPos();
	MoveDirection m_dir = MoveDirection::unknown;
	uint8_t m_startingHeight = 0;
protected:
	bool IsMoveAllowedForThisFigure(uint8_t yDifference, uint8_t xDifference) const override;
};

