#pragma once
#include <vector>
#include <memory>
#include "interface/IBoard.h"
#include <array>
#include <map>
#include <string>

class ICell;
class IFigure;
class Window;

enum class FigureColor : uint8_t
{
	black = 0,
	white
};

class Board : public IBoard
{
public:
	__declspec(dllexport) Board() = default;
	__declspec(dllexport) Board(std::array < std::unique_ptr<ICell>, 64> cells, const TextureContainer& textures);
	__declspec(dllexport) void Draw(std::unique_ptr<IWindow>& window) override;
private:
	void CreateBoard(std::array < std::unique_ptr<ICell>, 64>& cells);
	__declspec(dllexport) void CreateFigures(const TextureContainer& textures);
	void CreateWhite(const TextureContainer& textures);
	void CreateBlack(const TextureContainer& textures);
	std::vector<std::vector<std::unique_ptr<ICell>>> m_board;
	std::map<FigureColor, std::vector<std::shared_ptr<IFigure>>> m_figures;
};
