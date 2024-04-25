#include "Game.h"
#include "Helper.h"
#include "interface/ITexture.h"
#include "interface/IBoard.h"
#include "interface/IEvent.h"

Game::Game(std::array<std::unique_ptr<ITexture>, 14> texture, std::unique_ptr<IBoard> board, std::unique_ptr<IWindow> window):
	m_board(std::move(board)), m_window(std::move(window))
{
	LoadTextures(texture);
}

void Game::Update()
{
	while (m_window->IsOpen())
	{
		Events();
		Draw();
	}
}

void Game::Draw()
{
	m_window->Clear();

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

void Game::LoadTextures(std::array<std::unique_ptr<ITexture>, 14>& textures)
{
	bool isLoaded = true;
	textures::blackPawn = std::move(textures.at(0));
	textures::blackQueen = std::move(textures.at(1));
	textures::blackKing = std::move(textures.at(2));
	textures::blackKnight = std::move(textures.at(3));
	textures::blackRook = std::move(textures.at(4));
	textures::blackBishop = std::move(textures.at(5));
	textures::whitePawn = std::move(textures.at(6));
	textures::whiteQueen = std::move(textures.at(7));
	textures::whiteKing = std::move(textures.at(8));
	textures::whiteKnight = std::move(textures.at(9));
	textures::whiteRook = std::move(textures.at(10));
	textures::whiteBishop = std::move(textures.at(11));
	textures::boardGrey = std::move(textures.at(12));
	textures::boardRed = std::move(textures.at(13));
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
	isLoaded &= textures::boardGrey->LoadFromFile("textures\\figures\\BoardGrey.png");
	isLoaded &= textures::boardRed->LoadFromFile("textures\\figures\\BoardRed.png");
	if (!isLoaded)
	{
		throw(std::exception("failed to load textures"));
	}
}
