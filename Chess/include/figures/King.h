#pragma once
#include <memory>

class IFigure;

class King
{
public:
private:
	std::unique_ptr<IFigure> m_figure;
};

