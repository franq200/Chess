#pragma once
#include <memory>

class IFigure;

class Knight
{
public:
private:
	std::unique_ptr<IFigure> m_figure;
};