#pragma once
#include "interface/IFigure.h"
#include <memory>

class IRectangleShape;

class Figure : public IFigure
{
public:
	bool IsInRange(Pos mousePos) override;
protected:
	std::unique_ptr<IRectangleShape> m_figure;
};

