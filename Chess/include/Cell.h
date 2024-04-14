#pragma once
#include <memory>
#include "interface/ICell.h"
#include "interface/IRectangleShape.h"

class IRectangleShape;
class Window;

class Cell : public ICell
{
public:
	void Draw(std::unique_ptr<Window> window) override;
private:
	 std::unique_ptr<IRectangleShape> m_cell;
};

