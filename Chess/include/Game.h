#pragma once
#include "interface/IPlayer.h"
#include "interface/IWindow.h"
#include "Gameplay.h"
#include <memory>

enum class GameState {
	playing = 0,
	menu
};

class Game
{
public:
	__declspec(dllexport) Game(TexturesMap& textures, IBoardPtr board, IWindowPtr window, IMousePtr mouse, IPlayerPtr white, IPlayerPtr black);
	__declspec(dllexport) void Update();
private:
	void Events();

	Resolution GetResolution() const;

	IWindowPtr m_window;
	IMousePtr m_mouse;
	GameState m_gameState = GameState::playing;
	Gameplay m_gameplay;
};

