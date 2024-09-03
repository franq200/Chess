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
class Gameplay;
class IBoard;
class IMouse;
using FigureName = std::string;
using TextureContainer = std::map<FigureName, std::unique_ptr<ITexture>>;
enum class PlayerColor : uint8_t;

enum class GameState {
	playing = 0,
	menu
};

class Game
{
public:
	__declspec(dllexport) Game(TextureContainer& textures, std::unique_ptr<IBoard> board, std::unique_ptr<IWindow> window, std::unique_ptr<IMouse> mouse, std::unique_ptr<IPlayer> white, std::unique_ptr<IPlayer> black);
	__declspec(dllexport) void Update();
private:
	void Events();

	std::unique_ptr<IWindow> m_window;
	std::unique_ptr<IMouse> m_mouse;
	GameState m_gameState = GameState::playing;
	Gameplay m_gameplay;
};

