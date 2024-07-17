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
	__declspec(dllexport) void Draw(std::unique_ptr<IWindow>& window) override;
	__declspec(dllexport) void SetPosition(Pos pos) override;
	__declspec(dllexport) Pos GetPosition() const override;
	__declspec(dllexport) virtual bool IsMovePossible(Pos moveCell, FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const override;
	__declspec(dllexport) virtual std::vector<Pos> GetEveryPossibleMoves(FiguresVector currentPlayerFigures, FiguresVector opponentPlayerFigures) const override;
	__declspec(dllexport) std::vector<Pos> GetMovePath(Pos destinationCell, Pos currentPos) const;
	__declspec(dllexport) bool IsCollisionWithCurrentPlayer(const std::vector<Pos>& movePath, const FiguresVector& currentPlayerFigures) const;
	__declspec(dllexport) bool IsCollisionWithOpponent(const std::vector<Pos>& movePath, const FiguresVector& opponentPlayerFigures) const;
	__declspec(dllexport) bool IsFigureTaking(Pos destinationCell, const FiguresVector& opponentPlayerFigures);
protected:
	std::unique_ptr<IRectangleShape> m_figure;

	virtual bool IsMoveAllowedForThisFigure(uint8_t yDifference, uint8_t xDifference) const = 0;

	Positions GetTopPath(const Pos pos, const Pos moveCell) const;
	Positions GetDownPath(const Pos pos, const Pos moveCell) const;
	Positions GetLeftPath(const Pos pos, const Pos moveCell) const;
	Positions GetRightPath(const Pos pos, const Pos moveCell) const;

	Positions GetRightTopPath(const Pos pos, const Pos moveCell) const;
	Positions GetRightDownPath(const Pos pos, const Pos moveCell) const;
	Positions GetLeftTopPath(const Pos pos, const Pos moveCell) const;
	Positions GetLeftDownPath(const Pos pos, const Pos moveCell) const;

	std::vector<Pos> HandleDiagonalMovement(int xDifferenceRaw, int yDifferenceRaw, Pos pos, Pos moveCell) const;
	std::vector<Pos> HandleBasicMovement(int xDifferenceRaw, int yDifferenceRaw, Pos pos, Pos moveCell) const;

	Positions m_directions;
};

