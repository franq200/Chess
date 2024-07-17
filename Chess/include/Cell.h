#pragma once
#include <memory>
#include "Helper.h"
#include "interface/ICell.h"

class IRectangleShape;
class IWindow;

class Cell : public ICell
{
public:
	__declspec(dllexport) Cell();
	__declspec(dllexport) void Draw(std::unique_ptr<IWindow>& window) override;
	__declspec(dllexport) void SetFillColor(Color color) override;
	__declspec(dllexport) void SetPosition(Pos pos) override;
	__declspec(dllexport) void SetSize(Size size) override;
	__declspec(dllexport) void SetFigure(std::shared_ptr<IFigure> figure) override;
	__declspec(dllexport) void RemoveFigure() override;
	__declspec(dllexport) std::shared_ptr<IFigure> GetFigure() const override;
	__declspec(dllexport) bool IsOccupiedByPlayer(const std::unique_ptr<IPlayer>& currentPlayer) const override;
	__declspec(dllexport) void Highlight() override;
	__declspec(dllexport) void RemoveHighlight() override;
private:
	 std::unique_ptr<IRectangleShape> m_cell;
	 std::unique_ptr<IRectangleShape> m_highlight;
	 std::shared_ptr<IFigure> m_figure = nullptr;
	 int m_pos = 0;
};

