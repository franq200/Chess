#pragma once
#include <vector>
#include <memory>
#include "interface/IBoard.h"
#include <array>
#include <map>
#include <string>
#include "Helper.h"

class ICell;
class IFigure;
class Window;

using Figures = std::vector < std::shared_ptr<IFigure>>;
using FiguresMap = std::map<FigureColors, Figures>;
using Cells = std::vector<std::vector<std::unique_ptr<ICell>>>;

class Board : public IBoard
{
public:
	__declspec(dllexport) Board() = default;
	__declspec(dllexport) Board(std::array < std::unique_ptr<ICell>, 64> cells, TextureContainer& textures);
	__declspec(dllexport) void Draw(std::unique_ptr<IWindow>& window) override;
	__declspec(dllexport) bool IsCellOccupied(Pos mouseCell, FigureColors currentColor) const override;
	__declspec(dllexport) void SetCurrentFigure(Pos mouseCell) override;
	__declspec(dllexport) bool IsCurrentFigureSet() const override;
	__declspec(dllexport) bool IsMovePossible(Pos mouseCell) const override;
	__declspec(dllexport) void MoveCurrentFiguresToNewCell(Pos mouseCell) override;
	__declspec(dllexport) void CreateFigures(TextureContainer& textures) override;
private:
	void CreateBoard(std::array < std::unique_ptr<ICell>, 64>& cells);
	void CreateWhite(TextureContainer& textures);
	void CreateBlack(TextureContainer& textures);
	Cells m_board;
	FiguresMap m_figures;
	Pos m_selectedFigureCell = Pos(std::numeric_limits<uint16_t>::max(), std::numeric_limits<uint16_t>::max());
};
