#pragma once
#include <vector>
#include "Helper.h"

class IMoveExecutor;
class IWindow;
using IWindowPtr = std::unique_ptr<IWindow>;
using MoveExecutorPtr = std::shared_ptr<IMoveExecutor>;
class Board;
class IPlayer;
using IPlayerPtr = std::unique_ptr<IPlayer>;

class IFigure
{
public:
	using IFigurePtr = std::shared_ptr<IFigure>;
	using FiguresVector = std::vector<IFigurePtr>;
	virtual ~IFigure() = default;
	virtual bool IsInRange(Pos mousePos) = 0;
	virtual void SetOutlineThickness(int thickness) = 0;
	virtual void SetOutlineColor(Color color) = 0;
	virtual void Draw(IWindowPtr& window) = 0;
	virtual void SetPixelPosition(Pos pos) = 0;
	virtual Pos GetPosition() const = 0;
	virtual std::vector<MoveExecutorPtr> CalculatePossibleMoves(const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) = 0;
	virtual void SetShapePos(const Pos& tempPos) = 0;
	virtual void RestorePositionBeforeAnimation() = 0;
	virtual Pos GetPixelTempPosition() const = 0;
	virtual bool IsInPossibleMoves(const Pos& destinationPos) const = 0;
	virtual Pos GetCellTempPosition() const = 0;
	virtual bool IsFigureTaking(Pos destinationCell, const FiguresVector& opponentPlayerFigures) const = 0;
	virtual std::shared_ptr<IFigure> Clone() = 0;
	virtual void OnMove(Board& board, IPlayerPtr& opponent, Pos mouseCell) = 0;
	virtual void SetPossibleMoves(const std::vector<MoveExecutorPtr>& possibleMoves) = 0;
	friend bool operator==(const std::shared_ptr<IFigure>& lhs, const std::shared_ptr<IFigure>& rhs);

	virtual bool IsKing() const { return false; };
	virtual bool IsRook() const { return false; };
	virtual bool IsPawn() const { return false; };
protected:
	Pos m_startingPos;
};

