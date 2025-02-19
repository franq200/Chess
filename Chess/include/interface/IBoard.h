#pragma once
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "Helper.h"

enum class PlayerColor : uint8_t
{
	white = 0,
	black
};

class NormalMoveExecutor;
class TakingMoveExecutor;
class CastleMoveExecutor;
class IMoveExecutor;
class IPlayer;
class ITexture;
class IFigure;
class IWindow;

using IPlayerPtr = std::unique_ptr<IPlayer>;
using ITexturePtr = std::unique_ptr<ITexture>;
using IWindowPtr = std::unique_ptr<IWindow>;
using IFigurePtr = std::shared_ptr<IFigure>;

using FigureName = std::string;
using TexturesMap = std::map<FigureName, ITexturePtr>;
using FiguresVector = std::vector<IFigurePtr>;
using MoveExecutorPtr = std::shared_ptr<IMoveExecutor>;
using MoveExecutors = std::vector<MoveExecutorPtr>;

class IBoard
{
public:
	virtual ~IBoard() = default;
	virtual bool IsCellOccupied(Pos mouseCell, const IPlayerPtr& currentPlayer) const = 0;
	virtual bool IsMovePossible(Pos mouseCell) const = 0;
	virtual void MoveCurrentFiguresToNewCell(Pos mouseCell, IPlayerPtr& opponent) = 0;
	virtual void SetCurrentFigure(Pos mouseCell, PlayerColor currentPlayer) = 0;
	virtual void Animate(const Pos& mousePos) = 0;
	virtual void EndAnimation(const Pos& mousePos) = 0;
	virtual void CreateFigures(TexturesMap& textures, IPlayerPtr& white, IPlayerPtr& black) = 0;
	virtual void Draw(IWindowPtr& window) = 0;
};

