#include "Game.h"
#include "Helper.h"
#include "interface/ITexture.h"
#include "interface/IBoard.h"
#include "interface/IEvent.h"
#include "interface/IMouse.h"

Game::Game(TextureContainer& textures,
	std::unique_ptr<IBoard> board,
	std::unique_ptr<IWindow> window,
	std::unique_ptr<IMouse> mouse,
	std::unique_ptr<IPlayer> white,
	std::unique_ptr<IPlayer> black) :
	m_gameplay(textures, std::move(board), std::move(white), std::move(black)),
	m_window(std::move(window)),
	m_mouse(std::move(mouse))
{
	m_window->Create(Resolution(size::windowSizeXPix, size::windowSizeYPix), "Chess");
}

void Game::Update()
{
	while (m_window->IsOpen())
	{
		if (m_mouse->IsMouseInWindow(m_window))
		{
			Events();
			switch (m_gameState)
			{
			case GameState::playing:
				m_gameplay.Update(m_window, m_mouse);
			case GameState::menu:
				break;
			default:
				break;
			}
		}
	}
}

void Game::Events()
{
	IEvent event;
	while (m_window->PollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window->Close();
	}
}
