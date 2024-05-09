#pragma once
#include <vector>
#include <memory>
#include "interface/IBoard.h"
#include <array>

class ICell;
class IFigure;
class Window;

class Board : public IBoard
{
public:
	__declspec(dllexport) Board() = default;
	__declspec(dllexport) Board(std::array < std::unique_ptr<ICell>, 64> cells);
	__declspec(dllexport) void Draw(std::unique_ptr<IWindow> window) override;
private:
	void CreateFigures();
	void CreateBoard(std::array < std::unique_ptr<ICell>, 64>& cells);
	std::vector<std::vector<std::unique_ptr<ICell>>> m_board;
	std::vector<std::shared_ptr<IFigure>> m_figures;
};

