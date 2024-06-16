#include "Game.h"
#include "Helper.h"
#include "interface/ITexture.h"
#include "interface/IBoard.h"
#include "interface/IEvent.h"
#include "interface/IMouse.h"

Game::Game(TextureContainer& textures, std::unique_ptr<IBoard> board, std::unique_ptr<IWindow> window, std::unique_ptr<IMouse> mouse, PairOfPlayers players):
	m_textures(std::move(textures)), m_board(std::move(board)), m_window(std::move(window)), m_mouse(std::move(mouse))
{
	m_player[PlayerColor::white] = (std::move(players.first));
	m_player[PlayerColor::black] = (std::move(players.second));
	LoadTextures();
	m_board->CreateFigures(m_textures);
	m_window->Create(Resolution(size::windowSizeXPix, size::windowSizeYPix), "Chess");
}

void Game::Update()
{
	while (m_window->IsOpen())
	{
		Events();
		if (m_mouse->IsMouseInWindow(m_window))
		{
			Move();
		}
		Draw();
	}
}

void Game::Move()
{
	Pos mouseCell = m_mouse->GetPosition(m_window);
	if (m_board->IsCurrentFigureSet() && m_mouse->IsButtonPressed(IMouse::Button::Left) && m_board->IsMovePossible(mouseCell) && !m_isMoveButtonPressed)
	{
		m_board->MoveCurrentFiguresToNewCell(mouseCell);
		m_isMoveButtonPressed = true;
	}
	if (m_mouse->IsButtonPressed(IMouse::Button::Left))
	{
		if (!m_isMoveButtonPressed)
		{
			Pos mousePos = m_mouse->GetPosition(m_window);
			if (m_board->IsCellOccupied(mouseCell, static_cast<FigureColors>(m_currentPlayer)))
			{
				m_board->SetCurrentFigure(mouseCell);
			}
			m_isMoveButtonPressed = true;
		}
	}
	else
	{
		m_isMoveButtonPressed = false;
	}
}

void Game::Draw()
{
	m_window->Clear();
	m_board->Draw(m_window);
	m_window->Display();
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

void Game::LoadTextures()
{
	bool isLoaded = true;
	isLoaded &= m_textures["blackQueen"]->LoadFromFile("..\\Chess\\textures\\figures\\BQueen.png");
	isLoaded &= m_textures["blackPawn"]->LoadFromFile("..\\Chess\\textures\\figures\\BPawn.png");
	isLoaded &= m_textures["blackKing"]->LoadFromFile("..\\Chess\\textures\\figures\\BKing.png");
	isLoaded &= m_textures["blackKnight"]->LoadFromFile("..\\Chess\\textures\\figures\\BKnight.png");
	isLoaded &= m_textures["blackRook"]->LoadFromFile("..\\Chess\\textures\\figures\\BRook.png");
	isLoaded &= m_textures["blackBishop"]->LoadFromFile("..\\Chess\\textures\\figures\\BBishop.png");
	isLoaded &= m_textures["whitePawn"]->LoadFromFile("..\\Chess\\textures\\figures\\WPawn.png");
	isLoaded &= m_textures["whiteQueen"]->LoadFromFile("..\\Chess\\textures\\figures\\WQueen.png");
	isLoaded &= m_textures["whiteKing"]->LoadFromFile("..\\Chess\\textures\\figures\\WKing.png");
	isLoaded &= m_textures["whiteKnight"]->LoadFromFile("..\\Chess\\textures\\figures\\WKnight.png");
	isLoaded &= m_textures["whiteRook"]->LoadFromFile("..\\Chess\\textures\\figures\\WRook.png");
	isLoaded &= m_textures["whiteBishop"]->LoadFromFile("..\\Chess\\textures\\figures\\WBishop.png");
	isLoaded &= m_textures["boardGrey"]->LoadFromFile("..\\Chess\\textures\\board\\LightGrey.png");
	isLoaded &= m_textures["boardRed"]->LoadFromFile("..\\Chess\\textures\\board\\LightRed.png");
	if (!isLoaded)
	{
		throw(std::exception("failed to load textures"));
	}
}
