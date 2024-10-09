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
	__declspec(dllexport) void SetFillColor(Color color) override;
	__declspec(dllexport) void SetPosition(Pos pos) override;
	__declspec(dllexport) void SetSize(Size size) override;
	__declspec(dllexport) void SetFigure(IFigurePtr figure) override;
	__declspec(dllexport) void RemoveFigure() override;
	__declspec(dllexport) IFigurePtr GetFigure() const override;
	__declspec(dllexport) bool IsOccupiedByPlayer(const IPlayerPtr& currentPlayer) const override;
	__declspec(dllexport) void Highlight() override;
	__declspec(dllexport) void HighlightAsTaking() override;
	__declspec(dllexport) void RemoveHighlight() override;
	__declspec(dllexport) void DrawCells(IWindowPtr& window) override;
	__declspec(dllexport) void DrawFigures(IWindowPtr& window) override;
	__declspec(dllexport) void DrawHighlights(IWindowPtr& window) override;
private:
	void InitHighlights();
	std::unique_ptr<IRectangleShape> m_cell;
	std::unique_ptr<IRectangleShape> m_highlight;
	std::unique_ptr<IRectangleShape> m_takingHighlight;
	IFigurePtr m_figure = nullptr;
	int m_pos = 0;
};
