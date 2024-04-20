#pragma once
#include <memory>
#include <vector>
#include "interface/IPlayer.h"

class IFigure;

class Player : public IPlayer
{
public:
	void TryChangeCurrentFigure(Pos mousePos) override;
private:
	std::shared_ptr<IFigure> m_currentFigure = nullptr;
	std::vector<std::shared_ptr<IFigure>> m_figures;
};

