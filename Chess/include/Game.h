#pragma once
#include "interface/IGame.h"
#include "interface/IWindow.h"
#include <memory>
#include <map>
#include <string>

class ITexture;
class IBoard;
class IMouse;
using FigureName = std::string;
using TextureContainer = std::map<FigureName, std::unique_ptr<ITexture>>;

class Game : public IGame
{
public:
	__declspec(dllexport) Game(TextureContainer& textures, std::unique_ptr<IBoard> board, std::unique_ptr<IWindow> window, std::unique_ptr<IMouse> mouse);
	__declspec(dllexport) void Update() override;
private:
	void Move();
	void Draw();
	void Events();
	void LoadTextures();
	std::unique_ptr<IWindow> m_window;
	std::unique_ptr<IBoard> m_board;
	std::unique_ptr<IMouse> m_mouse;
	TextureContainer m_textures;
	bool m_isMoveButtonPressed = false;
};

