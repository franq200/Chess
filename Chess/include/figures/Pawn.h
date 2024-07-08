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
	Pawn(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size) {}
	bool IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures) override;
private:
	void SetDirectionBasedOnStartingPos();
	MoveDirection m_dir = MoveDirection::unknown;
	uint8_t m_startingHeight = 0;
};

