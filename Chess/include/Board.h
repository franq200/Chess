#pragma once
#include <vector>
#include <memory>
#include "interface/IBoard.h"

class Cell;
class IFigure;
class Window;

class Board : public IBoard
{
public:
	Board() = default;
	Board();
	void Draw(std::unique_ptr<IWindow> window) override;
private:
	void CreateFigures();
	void CreateBoard();
	std::vector<std::vector<Cell>> m_board;
	std::vector<std::shared_ptr<IFigure>> m_figures;
};

