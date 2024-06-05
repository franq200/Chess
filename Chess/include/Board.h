#pragma once
#include <vector>
#include <memory>
#include "interface/IBoard.h"
#include <array>
#include <map>
#include <string>
#include "Helper.h"

class ICell;
class IFigure;
class Window;

struct WhiteStartingIndex
{
	Pos rook1 = Pos (0, 7);
	Pos knight1 = Pos(1, 7);
	Pos bishop1 = Pos(2, 7);
	Pos queen = Pos(3, 7);
	Pos king = Pos(4, 7);
	Pos bishop2 = Pos(5, 7);
	Pos knight2 = Pos(6, 7);
	Pos rook2 = Pos(7, 7);
};

struct BlackStartingIndex
{
	Pos rook1 = Pos(0, 0);
	Pos knight1 = Pos(1, 0);
	Pos bishop1 = Pos(2, 0);
	Pos queen = Pos(3, 0);
	Pos king = Pos(4, 0);
	Pos bishop2 = Pos(5, 0);
	Pos knight2 = Pos(6, 0);
	Pos rook2 = Pos(7, 0);
};

enum class FigureColor : uint8_t
{
	black = 0,
	white
};

class Board : public IBoard
{
public:
	__declspec(dllexport) Board() = default;
	__declspec(dllexport) Board(std::array < std::unique_ptr<ICell>, 64> cells, TextureContainer& textures);
	__declspec(dllexport) void Draw(std::unique_ptr<IWindow>& window) override;
	__declspec(dllexport) bool IsCellOccupied(Pos mousePos) const override;
	__declspec(dllexport) void SetCurrentFigure(Pos mousePos) override;
	__declspec(dllexport) bool IsCurrentFigureSet() const override;
	__declspec(dllexport) bool IsMovePossible(Pos mousePos) const override;
	__declspec(dllexport) void MoveCurrentFiguresToNewCell(Pos mousePos) override;
	__declspec(dllexport) void CreateFigures(TextureContainer& textures) override;
private:
	//void CreateFigures(TextureContainer& textures);
	void CreateBoard(std::array < std::unique_ptr<ICell>, 64>& cells);
	void CreateWhite(TextureContainer& textures);
	void CreateBlack(TextureContainer& textures);
	std::vector<std::vector<std::unique_ptr<ICell>>> m_board;
	std::map<FigureColor, std::vector<std::shared_ptr<IFigure>>> m_figures;
};
