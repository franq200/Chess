#pragma once
#include <vector>
#include "interface/IPlayer.h"
#include "Helper.h"

class Player : public IPlayer
{
public:
	__declspec(dllexport) void AddFigures(FiguresVector& figures, IFigurePtr) override;
	__declspec(dllexport) void TryChangeCurrentFigure(Pos mousePos) override;
	__declspec(dllexport) bool HasFigure(const IFigurePtr& figure) const override;
	__declspec(dllexport) const FiguresVector& GetFigures() const override;
	__declspec(dllexport) bool IsAnyMovePossible(const FiguresVector& opponentPlayerFigures) const override;
	__declspec(dllexport) void RemoveFigure(Pos mouseCell) override;
private:
	std::vector<Pos> GetOpponentTakingMoves(const FiguresVector& opponentPlayerFigures) const;
	void UpdateCurrentFigure();
	IFigurePtr m_currentFigure = nullptr;
	IFigurePtr m_king = nullptr;
	FiguresVector m_figures;
};

