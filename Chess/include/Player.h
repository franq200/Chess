#pragma once
#include <vector>
#include "interface/IPlayer.h"

class IFigure;

class Player : public IPlayer
{
public:
	__declspec(dllexport) void AddFigures(std::vector<std::shared_ptr<IFigure>>& figures) override;
	__declspec(dllexport) void TryChangeCurrentFigure(Pos mousePos) override;
	__declspec(dllexport) bool HasFigure(const std::shared_ptr<IFigure>& figure) const override;
private:
	void UpdateCurrentFigure();
	std::shared_ptr<IFigure> m_currentFigure = nullptr;
	std::vector<std::shared_ptr<IFigure>> m_figures;
};

