#pragma once
#include "interface/IGame.h"
#include "interface/IWindow.h"
#include "interface/IPlayer.h"
#include <memory>
#include <map>
#include <string>

enum class PlayerColor : uint8_t
{
	black = 0,
	white
};

class ITexture;
class IBoard;
class IMouse;
using FigureName = std::string;
using TextureContainer = std::map<FigureName, std::unique_ptr<ITexture>>;
using PairOfPlayers = std::pair<std::unique_ptr<IPlayer>, std::unique_ptr<IPlayer>>;

class Game : public IGame
{
public:
	__declspec(dllexport) Game(TextureContainer& textures, std::unique_ptr<IBoard> board, std::unique_ptr<IWindow> window, std::unique_ptr<IMouse> mouse, PairOfPlayers players);
	__declspec(dllexport) void Update() override;
private:
	void Move();
	void Draw();
	void Events();
	void LoadTextures();
	std::unique_ptr<IWindow> m_window;
	std::unique_ptr<IBoard> m_board;
	std::unique_ptr<IMouse> m_mouse;
	std::map<PlayerColor, std::unique_ptr<IPlayer>> m_player;
	PlayerColor m_currentPlayer;
	TextureContainer m_textures;
	bool m_isMoveButtonPressed = false;
};

