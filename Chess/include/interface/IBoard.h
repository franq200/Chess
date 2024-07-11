#pragma once
#include <memory>
#include <map>
#include <string>
#include "Helper.h"

enum class PlayerColor : uint8_t
{
	white = 0,
	black
};

class IPlayer;
class ITexture;
class IFigure;
using FigureName = std::string;
using TextureContainer = std::map<FigureName, std::unique_ptr<ITexture>>;
using FiguresVector = std::vector<std::shared_ptr<IFigure>>;

class IPlayer;
class IWindow;

class IBoard
{
public:
	virtual ~IBoard() = default;
	virtual void Draw(std::unique_ptr<IWindow>& window) = 0;
	virtual bool IsCellOccupied(Pos mouseCell, const std::unique_ptr<IPlayer>& currentPlayer) const = 0;
	virtual void SetCurrentFigure(Pos mouseCell) = 0;
	virtual bool IsMovePossible(Pos mouseCell, PlayerColor currentPlayer) const = 0;
	virtual void MoveCurrentFiguresToNewCell(Pos mouseCell) = 0;
	virtual void CreateFigures(TextureContainer& textures, std::unique_ptr<IPlayer>& white, std::unique_ptr<IPlayer>& black) = 0;
};

