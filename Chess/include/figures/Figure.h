#pragma once
#include "interface/IFigure.h"
#include <memory>

class ITexture;
class IRectangleShape;

class Figure : public IFigure
{
public:
	Figure(std::unique_ptr<ITexture> texture, Pos pos = { 0, 0 }, Size size = { 0, 0 });
	bool IsInRange(Pos mousePos) override;
	void SetOutlineThickness(int thickness) override;
	void SetOutlineColor(Color color) override;
protected:
	std::unique_ptr<IRectangleShape> m_figure;
};

