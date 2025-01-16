#pragma once
#include "interface/IBoard.h"
#include <memory>
#include <map>
#include <string>

class IPlayer;
class IMouse;
class IWindow;
class IBoard;
class ITexture;

using IPlayerPtr = std::unique_ptr<IPlayer>;
using IWindowPtr = std::unique_ptr<IWindow>;
using ITexturePtr = std::unique_ptr<ITexture>;
using IBoardPtr = std::unique_ptr<IBoard>;
using IMousePtr = std::unique_ptr<IMouse>;
using FigureName = std::string;
using TexturesMap = std::map<FigureName, ITexturePtr>;

class Gameplay
{
public:
	__declspec(dllexport) Gameplay(TexturesMap& textures, IBoardPtr board, IPlayerPtr white, IPlayerPtr black);
	__declspec(dllexport) bool Update(IWindowPtr& window, IMousePtr& mouse);
private:
	const FiguresVector& GetOpponentFigures() const;
	PlayerColor GetCurrentPlayerColor() const;
	bool TryEndGame() const;
	void TryMoveAndSetCurrentFigure(IWindowPtr& window, IMousePtr& mouse);
	void Move(Pos mouseCell);
	void ChangeCurrentPlayer();
	void LoadTextures();
	void Draw(IWindowPtr& window);

	IBoardPtr m_board;
	IPlayerPtr m_whitePlayer;
	IPlayerPtr m_blackPlayer;
	IPlayerPtr* m_currentPlayer;
	TexturesMap m_textures;
};

