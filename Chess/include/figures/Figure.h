#pragma once
#include "interface/IFigure.h"
#include "Helper.h"
#include <memory>
#include <vector>

class IRectangleShape;
class ITexture;

using Positions = std::vector<Pos>;

class Figure : public IFigure
{
public:
	__declspec(dllexport) Figure() = default;
	virtual ~Figure() override = default;
	__declspec(dllexport) Figure(const ITexture& texture, Pos pos, Size size);
	__declspec(dllexport) bool IsInRange(Pos mousePos) override;
	__declspec(dllexport) void SetOutlineThickness(int thickness) override;
	__declspec(dllexport) void SetOutlineColor(Color color) override;
	__declspec(dllexport) void Draw(IWindowPtr& window) override;
	__declspec(dllexport) void SetPosition(Pos pos) override;
	__declspec(dllexport) Pos GetPosition() const override;
	__declspec(dllexport) Pos GetPixelPosition() const override;
	__declspec(dllexport) virtual std::vector<Pos> CalculatePossibleMoves(const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) override;
	__declspec(dllexport) void ChangeTempPos(const Pos& tempPos) override;
	__declspec(dllexport) void RestorePositionBeforeAnimation() override;
	__declspec(dllexport) Pos GetPixelTempPosition() const override;
	__declspec(dllexport) bool IsInPossibleMoves(const Pos& destinationPos) const override;
	__declspec(dllexport) Pos GetCellTempPosition() const override;
	__declspec(dllexport) void OnAnimation() override;
	__declspec(dllexport) bool IsFigureTaking(Pos destinationCell, const FiguresVector& opponentPlayerFigures) const;
protected:
	std::unique_ptr<IRectangleShape> m_figure;

	virtual bool IsMoveAllowed(Pos destinationCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const;
	virtual bool IsMoveAllowedForThisFigure(const Pos& destinationCell) const = 0;

	Positions GetTopPath(const Pos pos, const Pos destinationCell) const;
	Positions GetDownPath(const Pos pos, const Pos destinationCell) const;
	Positions GetLeftPath(const Pos pos, const Pos destinationCell) const;
	Positions GetRightPath(const Pos pos, const Pos movdestinationCelleCell) const;

	Positions GetRightTopPath(const Pos pos, const Pos destinationCell) const;
	Positions GetRightDownPath(const Pos pos, const Pos destinationCell) const;
	Positions GetLeftTopPath(const Pos pos, const Pos destinationCell) const;
	Positions GetLeftDownPath(const Pos pos, const Pos destinationCell) const;

	std::vector<Pos> HandleDiagonalMovement(int xDifferenceRaw, int yDifferenceRaw, Pos pos, Pos destinationCell) const;
	std::vector<Pos> HandleBasicMovement(int xDifferenceRaw, int yDifferenceRaw, Pos pos, Pos destinationCell) const;

	virtual std::vector<Pos> GetMovePath(Pos destinationCell, Pos currentPos) const;
	bool IsCollisionWithCurrentPlayer(const std::vector<Pos>& movePath, const FiguresVector& currentPlayerFigures) const;
	bool IsCollisionWithOpponent(const std::vector<Pos>& movePath, const FiguresVector& opponentPlayerFigures) const;
	bool IsCollisionWithAnyPlayer(Pos destinationCell, const FiguresVector& currentPlayerFigures, const FiguresVector& opponentPlayerFigures) const;

	Positions m_directions;
	int m_moveCounter = 0;
	std::vector<Pos> m_possibleMoves;
};

