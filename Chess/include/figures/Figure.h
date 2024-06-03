#pragma once
#include "interface/IFigure.h"
#include "interface/IRectangleShape.h"
#include <memory>

class ITexture;
//class IRectangleShape;

class Figure : public IFigure
{
public:
	__declspec(dllexport) Figure() = default;
	virtual ~Figure() override = default;
	__declspec(dllexport) Figure(const ITexture& texture, Pos pos = { 0, 0 }, Size size = { 0, 0 });
	__declspec(dllexport) bool IsInRange(Pos mousePos) override;
	__declspec(dllexport) void SetOutlineThickness(int thickness) override;
	__declspec(dllexport) void SetOutlineColor(Color color) override;
protected:
	std::unique_ptr<IRectangleShape> m_figure;
};

