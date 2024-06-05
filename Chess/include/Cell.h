#pragma once
#include <memory>
#include "Helper.h"
#include "interface/ICell.h"

class IRectangleShape;
class Window;

class Cell : public ICell
{
public:
	__declspec(dllexport) Cell();
	__declspec(dllexport) void Draw(std::unique_ptr<IWindow>& window) override;
	__declspec(dllexport) void SetFillColor(Color color) override;
	__declspec(dllexport) void SetPosition(Pos pos) override;
	__declspec(dllexport) void SetSize(Size size) override;
	__declspec(dllexport) void AddFigure(std::shared_ptr<IFigure> figure) override;
private:
	 std::unique_ptr<IRectangleShape> m_cell;
	 std::shared_ptr<IFigure> m_figure = nullptr;
	 int m_pos = 0;
};

