#pragma once
#include <vector>
#include "interface/IPlayer.h"
#include "Helper.h"

class Player : public IPlayer
{
public:
	__declspec(dllexport) void AddFigures(FiguresVector& figures, std::shared_ptr<IFigure>) override;
	__declspec(dllexport) void TryChangeCurrentFigure(Pos mousePos) override;
	__declspec(dllexport) bool HasFigure(const std::shared_ptr<IFigure>& figure) const override;
	__declspec(dllexport) const FiguresVector& GetFigures() const override;
	__declspec(dllexport) bool IsAnyMovePossible(const FiguresVector& opponentPlayerFigures) const override;
	__declspec(dllexport) void RemoveFigure(Pos mouseCell) override;
private:
	std::vector<Pos> GetOpponentTakingMoves(const FiguresVector& opponentPlayerFigures) const;
	void UpdateCurrentFigure();
	std::shared_ptr<IFigure> m_currentFigure = nullptr;
	std::shared_ptr<IFigure> m_king = nullptr;
	FiguresVector m_figures;
};

