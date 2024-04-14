#pragma once
#include <vector>
#include <memory>
#include "interface/IBoard.h"
#include "interface/ICell.h"

class Window;

class Board : public IBoard
{
public:
	Board() = default;
	Board(std::unique_ptr<ICell> cell);
	void Draw(std::unique_ptr<Window> window) override;
private:
	std::vector<std::vector<std::unique_ptr<ICell>>> m_board;
};

