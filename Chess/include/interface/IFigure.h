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
	virtual bool IsMovePossible(Pos destinationCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const = 0;
	virtual std::vector<Pos> GetEveryPossibleMoves(const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const = 0;
	//virtual std::vector<Pos> GetMovePath(Pos destinationCell, Pos currentPos) const = 0;
	//virtual bool IsCollisionWithCurrentPlayer(const std::vector<Pos>& movePath, const FiguresVector& currentPlayerFigures) const = 0;
	//virtual bool IsCollisionWithOpponent(const std::vector<Pos>& movePath, const FiguresVector& opponentPlayerFigures) const = 0;
	//virtual bool IsFigureTaking(Pos destinationCell, const FiguresVector& opponentPlayerFigures) = 0;
};

