#include "figures/Figure.h"
#include "interface/IRectangleShape.h"

bool Figure::IsInRange(Pos mousePos)
{
    Pos pos = m_figure->GetPosition();
    bool isInXRange = mousePos.x - pos.x <= size::cellSizeX && mousePos.x - pos.x >= 0;
    bool isInYRange = mousePos.y - pos.y <= size::cellSizeX && mousePos.y - pos.y >= 0;
    return isInXRange && isInYRange;
}
