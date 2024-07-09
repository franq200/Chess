#pragma once
#include <vector>
#include "interface/IPlayer.h"

class Player : public IPlayer
{
public:
	__declspec(dllexport) void AddFigures(FiguresVector& figures) override;
	__declspec(dllexport) void TryChangeCurrentFigure(Pos mousePos) override;
	__declspec(dllexport) bool HasFigure(const std::shared_ptr<IFigure>& figure) const override;
	__declspec(dllexport) const FiguresVector& GetFigures() const override;
	__declspec(dllexport) bool IsAnyMovePossible(FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const override;
private:
	void UpdateCurrentFigure();
	std::shared_ptr<IFigure> m_currentFigure = nullptr;
	FiguresVector m_figures;
};

