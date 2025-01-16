#include "Game.h"
#include "Helper.h"
#include "interface/ITexture.h"
#include "interface/IBoard.h"
#include "interface/IEvent.h"
#include "interface/IMouse.h"

Game::Game(TexturesMap& textures,
	IBoardPtr board,
	IWindowPtr window,
	IMousePtr mouse,
	IPlayerPtr white,
	IPlayerPtr black) :
	m_gameplay(textures, std::move(board), std::move(white), std::move(black)),
	m_window(std::move(window)),
	m_mouse(std::move(mouse))
{
	m_window->Create(GetResolution(), "Chess");
}

void Game::Update()
{
	while (m_window->IsOpen())
	{
		if (m_mouse->IsMouseInWindow(m_window))
		{
			m_mouse->Update(IMouse::UpdateType::current);
			Events();
			switch (m_gameState)
			{
			case GameState::playing:
				if (!m_gameplay.Update(m_window, m_mouse))
				{
					m_gameState = GameState::menu;
				}
			case GameState::menu:
				break;
			default:
				break;
			}
			m_mouse->Update(IMouse::UpdateType::previous);
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

Resolution Game::GetResolution() const
{
	return Resolution(size::windowSizeXPix, size::windowSizeYPix);
}
