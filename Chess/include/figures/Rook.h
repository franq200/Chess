#pragma once
#include <memory>

class IFigure;

class Rook
{
public:
private:
	std::unique_ptr<IFigure> m_figure;
};