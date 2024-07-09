#pragma once
#include <memory>
#include "Figure.h"

class Rook: public Figure
{
public:
	Rook() = default;
	Rook(const ITexture& texture, Pos pos, Size size);
	__declspec(dllexport) bool IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) override;
	__declspec(dllexport) std::vector<Pos> GetEveryPossibleMoves(FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const override;
protected:
	bool IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const override;
};