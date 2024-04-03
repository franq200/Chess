#pragma once
#include <vector>
#include <memory>
#include "IBoard.h"

class ICell;

class Board : public IBoard
{
public:
	Board() = default;
	Board(std::unique_ptr<ICell> cell);
	void Draw(std::unique_ptr<IWindow> window) override;
private:
	std::vector<std::vector<std::unique_ptr<ICell>>> m_board;
};

