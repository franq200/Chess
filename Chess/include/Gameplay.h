#pragma once
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

enum class GameState {
	playing = 0,
	menu
};

class Gameplay
{
public:
	__declspec(dllexport) Gameplay(TextureContainer& textures, std::unique_ptr<IBoard> board, std::unique_ptr<IPlayer> white, std::unique_ptr<IPlayer> black);
	__declspec(dllexport) void Update(std::unique_ptr<IWindow> window, std::unique_ptr<IMouse> mouse);
private:
	void AnimateMoving(std::unique_ptr<IWindow> window, std::unique_ptr<IMouse> mouse);
	const FiguresVector& GetOpponentFigures() const;
	PlayerColor GetCurrentPlayer() const;
	bool TryEndGame() const;
	void MoveAndSetCurrentFigure(std::unique_ptr<IWindow> window, std::unique_ptr<IMouse> mouse);
	void Draw(std::unique_ptr<IWindow> window);
	void LoadTextures();
	void Move(Pos mouseCell);
	void Reset();
	void EndGame();
	void StartNewGame();
	std::unique_ptr<IBoard> m_board;
	std::unique_ptr<IPlayer> m_whitePlayer;
	std::unique_ptr<IPlayer> m_blackPlayer;
	std::unique_ptr<IPlayer>* m_currentPlayer;
	TextureContainer m_textures;
	bool m_isMoveButtonPressed = false;
	GameState m_gameState = GameState::playing;
};

