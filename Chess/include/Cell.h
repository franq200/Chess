#pragma once
#include <memory>
#include "Helper.h"
#include "interface/ICell.h"
#include "interface/IRectangleShape.h"

class Window;

class Cell : public ICell
{
public:
	__declspec(dllexport) Cell();
	__declspec(dllexport) void Draw(std::unique_ptr<IWindow>& window) override;
	__declspec(dllexport) void SetFillColor(Color color) override;
	__declspec(dllexport) void SetPosition(Pos pos) override;
	__declspec(dllexport)void SetSize(Size size) override;
private:
	 std::unique_ptr<IRectangleShape> m_cell;
	 int m_pos = 0;
};

