#pragma once
#include <vector>
#include <memory>
#include "interface/IBoard.h"
#include <array>
#include <map>
#include <string>
#include <optional>
#include "Helper.h"

class ICell;
class IFigure;
class Window;

using Figures = std::vector < std::shared_ptr<IFigure>>;
using FiguresMap = std::map<PlayerColor, Figures>;
using Cells = std::vector<std::vector<std::unique_ptr<ICell>>>;

class Board : public IBoard
{
public:
	__declspec(dllexport) Board() = default;
	__declspec(dllexport) Board(std::array < std::unique_ptr<ICell>, 64> cells, TextureContainer& textures);
	__declspec(dllexport) void Draw(std::unique_ptr<IWindow>& window) override;
	__declspec(dllexport) bool IsCellOccupied(Pos mouseCell, const std::unique_ptr<IPlayer>& currentPlayer) const override;
	__declspec(dllexport) void SetCurrentFigure(Pos mouseCell, PlayerColor currentPlayer) override;
	__declspec(dllexport) bool IsMovePossible(Pos mouseCell) const override;
	__declspec(dllexport) void MoveCurrentFiguresToNewCell(Pos mouseCell, std::unique_ptr<IPlayer>& opponent) override;
	__declspec(dllexport) void CreateFigures(TextureContainer& textures, std::unique_ptr<IPlayer>& white, std::unique_ptr<IPlayer>& black) override;
	__declspec(dllexport) void Animate(const Pos& mousePos) override;
	__declspec(dllexport) void EndAnimation(const Pos& mousePos) override;
	__declspec(dllexport) bool IsAnimating() const override;
	__declspec(dllexport) void StartAnimation() override;
private:
	void RemoveFigure(Pos mouseCell, std::unique_ptr<IPlayer>& opponent);
	bool IsItTakingMove(const Pos& move) const;
	void DrawCells(std::unique_ptr<IWindow>& window);
	void DrawFigures(std::unique_ptr<IWindow>& window);
	std::pair<Figures, Figures> GetPlayersFigures(PlayerColor currentPlayer) const;
	void UpdatePossibleMoves(PlayerColor currentPlayer);
	bool IsCurrentFigureSet() const;
	void CreateBoard(std::array < std::unique_ptr<ICell>, 64>& cells);
	void CreateWhite(TextureContainer& textures);
	void CreateBlack(TextureContainer& textures);
	void RemoveHighlights();
	std::shared_ptr<IFigure> GetCurrentFigure() const;
	Cells m_board;
	FiguresMap m_figures;
	std::shared_ptr<IFigure> m_whiteKing;
	std::shared_ptr<IFigure> m_blackKing;
	std::optional<Pos> m_selectedFigureCell;
	std::optional<Pos> m_mousePosInFigure;
	std::vector<Pos> m_takingMoves;
	bool m_isAnimating = false;
};
