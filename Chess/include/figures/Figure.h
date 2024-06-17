#pragma once
#include "interface/IFigure.h"
#include <memory>

class IRectangleShape;
class ITexture;

class Figure : public IFigure
{
public:
	__declspec(dllexport) Figure() = default;
	virtual ~Figure() override = default;
	__declspec(dllexport) Figure(const ITexture& texture, Pos pos, Size size, PlayerColor color);
	__declspec(dllexport) bool IsInRange(Pos mousePos) override;
	__declspec(dllexport) void SetOutlineThickness(int thickness) override;
	__declspec(dllexport) void SetOutlineColor(Color color) override;
	__declspec(dllexport) void Draw(std::unique_ptr<IWindow>& window) override;
	__declspec(dllexport) void SetPosition(Pos pos) override;
	bool IsMovePossible(Pos moveCell) override = 0;
	__declspec(dllexport) PlayerColor GetFigureColor() const override;
protected:
	std::unique_ptr<IRectangleShape> m_figure;
	PlayerColor m_color;
};

