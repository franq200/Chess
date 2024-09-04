#include "Gameplay.h"
#include "Helper.h"
#include "interface/ITexture.h"
#include "interface/IBoard.h"
#include "interface/IEvent.h"
#include "interface/IMouse.h"

Gameplay::Gameplay(TextureContainer& textures,
	std::unique_ptr<IBoard> board,
	std::unique_ptr<IPlayer> white,
	std::unique_ptr<IPlayer> black) :
	m_textures(std::move(textures)),
	m_board(std::move(board)),
	m_whitePlayer(std::move(white)),
	m_blackPlayer(std::move(black)),
	m_currentPlayer(&m_whitePlayer)
{
	LoadTextures();
	m_board->CreateFigures(m_textures, m_whitePlayer, m_blackPlayer);
}

void Gameplay::Update(std::unique_ptr<IWindow> window, std::unique_ptr<IMouse> mouse)
{
	TryEndGame();
	MoveAndSetCurrentFigure(std::move(window), std::move(mouse));
	if (m_board->IsAnimating())
	{
		AnimateMoving(std::move(window), std::move(mouse));
	}
	Draw(std::move(window));
}

void Gameplay::AnimateMoving(std::unique_ptr<IWindow> window, std::unique_ptr<IMouse> mouse)
{
	if (mouse->IsButtonPressed(IMouse::Button::Left))
	{
		m_board->Animate(mouse->GetPixelPosition(window));
	}
	else
	{
		Pos mouseCell = mouse->GetCellPosition(window);
		if (m_board->IsMovePossible(mouseCell))
		{
			Move(mouseCell);
		}
		m_board->EndAnimation(mouse->GetCellPosition(window));
	}
}

const FiguresVector& Gameplay::GetOpponentFigures() const
{
	if (*m_currentPlayer == m_whitePlayer)
	{
		return m_blackPlayer->GetFigures();
	}
	return m_whitePlayer->GetFigures();
}

PlayerColor Gameplay::GetCurrentPlayer() const
{
	if (*m_currentPlayer == m_whitePlayer)
	{
		return PlayerColor::white;
	}
	return PlayerColor::black;
}

bool Gameplay::TryEndGame() const
{
	return m_currentPlayer->get()->IsAnyMovePossible(GetOpponentFigures());
}

void Gameplay::MoveAndSetCurrentFigure(std::unique_ptr<IWindow> window, std::unique_ptr<IMouse> mouse)
{
	Pos mouseCell = mouse->GetCellPosition(window);
	if (mouse->IsButtonPressed(IMouse::Button::Left))
	{
		m_board->StartAnimation();
		if (!m_isMoveButtonPressed)
		{
			if (m_board->IsMovePossible(mouseCell))
			{
				Move(mouseCell);
			}
			if (m_board->IsCellOccupied(mouseCell, *m_currentPlayer))
			{
				m_board->SetCurrentFigure(mouseCell, GetCurrentPlayer());
			}
			m_isMoveButtonPressed = true;
		}
	}
	else
	{
		m_isMoveButtonPressed = false;
	}
}

void Gameplay::Move(Pos mouseCell)
{
	m_board->MoveCurrentFiguresToNewCell(mouseCell);
	m_isMoveButtonPressed = true;
	m_currentPlayer = (*m_currentPlayer == m_whitePlayer) ? &m_blackPlayer : &m_whitePlayer;
}

void Gameplay::Reset()
{
	EndGame();
	StartNewGame();
}

void Gameplay::EndGame()
{
	m_board->Reset();
}

void Gameplay::StartNewGame()
{
	m_isMoveButtonPressed = false;
	m_currentPlayer = &m_whitePlayer;
}

void Gameplay::Draw(std::unique_ptr<IWindow> window)
{
	window->Clear();
	m_board->Draw(window);
	window->Display();
}

void Gameplay::LoadTextures()
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