#include "Game.h"
#include "Helper.h"
#include "ITexture.h"
#include "IBoard.h"

Game::Game(std::unique_ptr<ITexture> texture, std::unique_ptr<IBoard> board):
	m_texture(std::move(texture)), m_board(std::move(board))
{
	LoadTextures();
}

void Game::Update()
{
	while (m_window.isOpen())
	{
		Events();
		Draw();
	}
}

void Game::Draw()
{
	m_window.clear();

	m_window.display();
}

void Game::Events()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();
	}
}

void Game::LoadTextures()
{
	bool isLoaded = true;
	textures::blackPawn = std::move(m_texture);
	textures::blackQueen = std::move(m_texture);
	textures::blackKing = std::move(m_texture);
	textures::blackKnight = std::move(m_texture);
	textures::blackRook = std::move(m_texture);
	textures::blackBishop = std::move(m_texture);
	textures::whitePawn = std::move(m_texture);
	textures::whiteQueen = std::move(m_texture);
	textures::whiteKing = std::move(m_texture);
	textures::whiteKnight = std::move(m_texture);
	textures::whiteRook = std::move(m_texture);
	textures::whiteBishop = std::move(m_texture);
	isLoaded &= textures::blackQueen->LoadFromFile("textures\\figures\\BQueen.png");
	isLoaded &= textures::blackPawn->LoadFromFile("textures\\figures\\BPawn.png");
	isLoaded &= textures::blackKing->LoadFromFile("textures\\figures\\BKing.png");
	isLoaded &= textures::blackKnight->LoadFromFile("textures\\figures\\BKnight.png");
	isLoaded &= textures::blackRook->LoadFromFile("textures\\figures\\BRook.png");
	isLoaded &= textures::blackBishop->LoadFromFile("textures\\figures\\BBishop.png");
	isLoaded &= textures::whitePawn->LoadFromFile("textures\\figures\\WPawn.png");
	isLoaded &= textures::whiteQueen->LoadFromFile("textures\\figures\\WQueen.png");
	isLoaded &= textures::whiteKing->LoadFromFile("textures\\figures\\WKing.png");
	isLoaded &= textures::whiteKnight->LoadFromFile("textures\\figures\\WKnight.png");
	isLoaded &= textures::whiteRook->LoadFromFile("textures\\figures\\WRook.png");
	isLoaded &= textures::whiteBishop->LoadFromFile("textures\\figures\\WBishop.png");
	if (!isLoaded)
	{
		throw(std::exception("failed to load textures"));
	}
}
