#pragma once
#include "interface/IGame.h"
#include "interface/IWindow.h"
#include "interface/IPlayer.h"
#include <memory>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <cstdint>

class ITexture;
class IBoard;
class IMouse;
using FigureName = std::string;
using TextureContainer = std::map<FigureName, std::unique_ptr<ITexture>>;
enum class PlayerColor : uint8_t;

class Game : public IGame
{
public:
	__declspec(dllexport) Game(TextureContainer& textures, std::unique_ptr<IBoard> board, std::unique_ptr<IWindow> window, std::unique_ptr<IMouse> mouse, std::unique_ptr<IPlayer> white, std::unique_ptr<IPlayer> black);
	__declspec(dllexport) void Update() override;
private:
	const FiguresVector& GetOpponentFigures() const;
	PlayerColor GetCurrentPlayer() const;
	bool TryEndGame() const;
	void MoveAndSetCurrentFigure();
	void Draw();
	void Events();
	void LoadTextures();
	void Move(Pos mouseCell);
	std::unique_ptr<IWindow> m_window;
	std::unique_ptr<IBoard> m_board;
	std::unique_ptr<IMouse> m_mouse;
	std::unique_ptr<IPlayer> m_whitePlayer;
	std::unique_ptr<IPlayer> m_blackPlayer;
	std::unique_ptr<IPlayer>* m_currentPlayer;
	TextureContainer m_textures;
	bool m_isMoveButtonPressed = false;
};

