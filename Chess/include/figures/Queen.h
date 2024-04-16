#pragma once
#include <memory>

class IFigure;

class Queen
{
public:
private:
	std::unique_ptr<IFigure> m_figure;
};

