#pragma once
#include <vector>
#include "IBoard.h"
#include "Cell.h"

class Board : public IBoard
{
public:
	void Draw(std::unique_ptr<IWindow> window) override;
private:
	std::vector<std::vector<Cell>> m_board;
};

