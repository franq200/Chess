#pragma once
#include <vector>
#include <memory>
#include "interface/IBoard.h"
#include <array>
#include <map>
#include <string>
#include <optional>
#include "Helper.h"

class IMoveExecutor;
class NormalMoveExecutor;
class TakingMoveExecutor;
class CastleMoveExecutor;

class ICell;
using ICellPtr = std::unique_ptr<ICell>;
class IFigure;
using IFigurePtr = std::shared_ptr<IFigure>;
class Window;

using Figures = std::vector < IFigurePtr>;
using FiguresMap = std::map<PlayerColor, Figures>;
using Cells = std::vector<std::vector<ICellPtr>>;
using MoveExecutorPtr = std::shared_ptr<IMoveExecutor>;
using MoveExecutors = std::vector<MoveExecutorPtr>;

using Positions = std::vector<Pos>;

class Board : public IBoard
{
public:
	//__declspec(dllexport) Board() = default;
	__declspec(dllexport) Board(std::array < ICellPtr, 64> cells, TexturesMap& textures);

	__declspec(dllexport) bool IsCellOccupied(Pos mouseCell, const IPlayerPtr& currentPlayer) const override;
	__declspec(dllexport) bool IsAnimating() const override;
	__declspec(dllexport) bool IsMovePossible(Pos mouseCell) const override;
	__declspec(dllexport) void MoveCurrentFiguresToNewCell(Pos mouseCell, IPlayerPtr& opponent) override;
	__declspec(dllexport) void SetCurrentFigure(Pos mouseCell, PlayerColor currentPlayer) override;
	__declspec(dllexport) void StartAnimation() override;
	__declspec(dllexport) void Animate(const Pos& mousePos) override;
	__declspec(dllexport) void EndAnimation(const Pos& mousePos) override;
	__declspec(dllexport) void CreateFigures(TexturesMap& textures, IPlayerPtr& white, IPlayerPtr& black) override;
	__declspec(dllexport) void Draw(IWindowPtr& window) override;
	friend class NormalMoveExecutor;
	friend class TakingMoveExecutor;
	friend class CastleMoveExecutor;
private:
	bool IsShortCastlePossible(const Positions& opponentTakingMoves) const;
	bool IsLongCastlePossible(const Positions& opponentTakingMoves) const;
	std::vector<Pos> GetTakingMoves(const IFigurePtr& currentFigure, const Figures& opponentFigures, const MoveExecutors& possibleMoves) const;
	void HighlightMoves(const MoveExecutors& possibleMoves);
	std::pair<Figures, Figures> GetPlayersFigures(PlayerColor currentPlayer) const;
	IFigurePtr GetCurrentFigure() const;
	bool IsItTakingMove(const Pos& move) const;
	bool IsCurrentFigureSet() const;
	void RemoveFigure(Pos mouseCell, IPlayerPtr& opponent);
	void UpdatePossibleMoves(PlayerColor currentPlayer);
	void RemoveHighlights();
	void CreateBoard(std::array < ICellPtr, 64>& cells);
	void CreateWhite(TexturesMap& textures);
	void CreateBlack(TexturesMap& textures);
	void DrawCells(IWindowPtr& window);
	void DrawFiguresAndHighlights(IWindowPtr& window);

	Cells m_board;
	FiguresMap m_figures;
	IFigurePtr m_whiteKing;
	IFigurePtr m_blackKing;
	std::optional<Pos> m_selectedFigureCell;
	std::optional<Pos> m_mousePosInFigure;
	std::vector<Pos> m_takingMoves;
	bool m_isAnimating = false;
};
