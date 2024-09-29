#pragma once
#include <vector>
#include "interface/IPlayer.h"
#include "Helper.h"

class Player : public IPlayer
{
public:
	__declspec(dllexport) void AddFigures(FiguresVector& figures, IFigurePtr king) override;
	__declspec(dllexport) void TryChangeCurrentFigure(Pos mousePos) override;
	__declspec(dllexport) bool HasFigure(const IFigurePtr& figure) const override;
	__declspec(dllexport) const FiguresVector& GetFigures() const override;
	__declspec(dllexport) bool IsAnyMovePossible(const FiguresVector& opponentPlayerFigures) const override;
	__declspec(dllexport) void RemoveFigure(Pos mouseCell) override;
private:
	bool IsKingUnderAttack(const std::vector<Pos>& opponentTakingMoves) const;
	bool CanKingEscape(const FiguresVector& opponentPlayerFigures) const;
	std::vector<Pos> GetOpponentTakingMoves(const FiguresVector& opponentPlayerFigures, const FiguresVector& currentPlayerFigures) const;
	std::pair<FiguresVector, IFigurePtr> CloneFigures() const;
	IFigurePtr m_currentFigure = nullptr;
	IFigurePtr m_king = nullptr;
	FiguresVector m_figures;
};

