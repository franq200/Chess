#pragma once
#include <vector>
#include "Helper.h"

class IWindow;

class IFigure
{
public:
	using FiguresVector = std::vector<std::shared_ptr<IFigure>>;
	virtual ~IFigure() = default;
	virtual bool IsInRange(Pos mousePos) = 0;
	virtual void SetOutlineThickness(int thickness) = 0;
	virtual void SetOutlineColor(Color color) = 0;
	virtual void Draw(std::unique_ptr<IWindow>& window) = 0;
	virtual void SetPosition(Pos pos) = 0;
	virtual Pos GetPosition() const = 0;
	virtual Pos GetPixelPosition() const = 0;
	virtual std::vector<Pos> CalculatePossibleMoves(const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) = 0;
	virtual void ChangeTempPos(const Pos& tempPos) = 0;
	virtual void SetCurrentPos() = 0;
	virtual Pos GetPixelTempPosition() const = 0;
	virtual bool IsInPossibleMoves(const Pos& destinationPos) const = 0;
	virtual Pos GetCellTempPosition() const = 0;
	virtual void OnAnimation() = 0;
	virtual bool IsFigureTaking(Pos destinationCell, const FiguresVector& opponentPlayerFigures) const = 0;
};

