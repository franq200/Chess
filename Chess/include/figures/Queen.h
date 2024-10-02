#pragma once
#include <memory>
#include "Figure.h"

class Queen : public Figure
{
public:
    Queen() = default;
    Queen(const ITexture& texture, Pos pos, Size size);
    __declspec(dllexport) std::shared_ptr<IFigure> Clone() const override;
protected:
    bool IsMoveAllowedForThisFigure(const Pos& destinationCell) const override;
};

