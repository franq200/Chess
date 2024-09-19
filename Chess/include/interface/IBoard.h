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
using IPlayerPtr = std::unique_ptr<IPlayer>;
class ITexture;
using ITexturePtr = std::unique_ptr<ITexture>;
class IWindow;
using IWindowPtr = std::unique_ptr<IWindow>;
class IFigure;
using IFigurePtr = std::shared_ptr<IFigure>;

using FigureName = std::string;
using TexturesMap = std::map<FigureName, ITexturePtr>;
using FiguresVector = std::vector<IFigurePtr>;

class IBoard
{
public:
	virtual ~IBoard() = default;
	virtual bool IsCellOccupied(Pos mouseCell, const IPlayerPtr& currentPlayer) const = 0;
	virtual bool IsAnimating() const = 0;
	virtual bool IsMovePossible(Pos mouseCell) const = 0;
	virtual void MoveCurrentFiguresToNewCell(Pos mouseCell, IPlayerPtr& opponent) = 0;
	virtual void SetCurrentFigure(Pos mouseCell, PlayerColor currentPlayer) = 0;
	virtual void StartAnimation() = 0;
	virtual void Animate(const Pos& mousePos) = 0;
	virtual void EndAnimation(const Pos& mousePos, IPlayerPtr& opponent) = 0;
	virtual void CreateFigures(TexturesMap& textures, IPlayerPtr& white, IPlayerPtr& black) = 0;
	virtual void Draw(IWindowPtr& window) = 0;
};

