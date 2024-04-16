#pragma once
#include <memory>

class IFigure;

class Bishop
{
public:
private:
	std::unique_ptr<IFigure> m_figure;
};