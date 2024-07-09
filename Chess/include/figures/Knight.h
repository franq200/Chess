#pragma once
#include <memory>
#include "Figure.h"

class Knight : public Figure
{
public:
	Knight() = default;
	Knight(const ITexture& texture, Pos pos, Size size) :Figure(texture, pos, size) {}
	__declspec(dllexport) bool IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) override;
	__declspec(dllexport) std::vector<Pos> GetEveryPossibleMoves(FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const override;
private:
};