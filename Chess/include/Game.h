#pragma once
#include "interface/IGame.h"
#include "interface/IWindow.h"
#include <memory>
#include <array>

class ITexture;
class IBoard;

class Game : public IGame
{
public:
	__declspec(dllexport) Game(std::array<std::unique_ptr<ITexture>, 14> texture, std::unique_ptr<IBoard> board, std::unique_ptr<IWindow> window);
	__declspec(dllexport) void Update() override;
private:
	void Draw();
	void Events();
	void LoadTextures(std::array<std::unique_ptr<ITexture>, 14>&);
	std::unique_ptr<IWindow> m_window;
	std::unique_ptr<IBoard> m_board;
};

