#pragma once
#include <memory>
#include <deque>
#include "interface/IPlayer.h"

class IFigure;

class Player : public IPlayer
{
public:
	void TryChangeCurrentFigure(Pos mousePos) override;
private:
	std::shared_ptr<IFigure> m_currentFigure = nullptr;
	std::deque<std::shared_ptr<IFigure>> m_figures;
};

