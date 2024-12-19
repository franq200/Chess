#pragma once
#include <memory>
#include "Figure.h"
#include "../IMoveExecutor.h"

using Positions = std::vector<Pos>;

class Bishop : public Figure
{
public:
	Bishop() = default;
	Bishop(const ITexture& texture, Pos pos, Size size);
	__declspec(dllexport) std::shared_ptr<IFigure> Clone() override;
protected:
	bool IsMoveAllowedForThisFigure(Pos destinationCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const override;
};