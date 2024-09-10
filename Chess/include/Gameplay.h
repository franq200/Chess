#pragma once
#include "interface/IPlayer.h"
#include <memory>
#include <map>
#include <string>

using IPlayerPtr = std::unique_ptr<IPlayer>;
class IWindow;
using IWindowPtr = std::unique_ptr<IWindow>;
class ITexture;
using ITexturePtr = std::unique_ptr<ITexture>;
class IBoard;
using IBoardPtr = std::unique_ptr<IBoard>;
class IMouse;
using IMousePtr = std::unique_ptr<IMouse>;
using FigureName = std::string;
using TexturesMap = std::map<FigureName, ITexturePtr>;
enum class PlayerColor : uint8_t;

class Gameplay
{
public:
	__declspec(dllexport) Gameplay(TexturesMap& textures, IBoardPtr board, IPlayerPtr white, IPlayerPtr black);
	__declspec(dllexport) bool Update(IWindowPtr& window, IMousePtr& mouse);
private:
	const FiguresVector& GetOpponentFigures() const;
	PlayerColor GetCurrentPlayerColor() const;
	bool TryEndGame() const;
	void AnimateMoving(IWindowPtr& window, IMousePtr& mouse);
	void MoveAndSetCurrentFigure(IWindowPtr& window, IMousePtr& mouse);
	void Move(Pos mouseCell);
	void ChangeCurrentPlayer();
	void LoadTextures();
	void Draw(IWindowPtr& window);

	IBoardPtr m_board;
	IPlayerPtr m_whitePlayer;
	IPlayerPtr m_blackPlayer;
	IPlayerPtr* m_currentPlayer;
	TexturesMap m_textures;
	bool m_isMoveButtonPressed = false;
};

