#pragma once
#include <memory>
#include <vector>
#include "Helper.h"
#include "Figure.h"

class Knight : public Figure
{
public:
	Knight() = default;
	Knight(const ITexture& texture, Pos pos, Size size);
	__declspec(dllexport) std::shared_ptr<IFigure> Clone() const override;
protected:
	bool IsMoveAllowedForThisFigure(const Pos& destinationCell) const;
	std::vector<Pos> GetMovePath(Pos destinationCell, Pos currentPos) const;
};