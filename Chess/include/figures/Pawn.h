#pragma once
#include <memory>

class IFigure;

class Pawn
{
public:
private:
	std::unique_ptr<IFigure> m_figure;
};

