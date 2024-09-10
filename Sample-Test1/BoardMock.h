#pragma once
#include <gmock/gmock.h>
#include "interface/IBoard.h"

class BoardMock : public IBoard
{
public:
    MOCK_METHOD(void, Draw, (std::unique_ptr<IWindow>& window), (override));
    MOCK_METHOD(bool, IsCellOccupied, (Pos mouseCell, const std::unique_ptr<IPlayer>& currentPlayer), (const, override));
    MOCK_METHOD(void, SetCurrentFigure, (Pos mouseCell, PlayerColor currentPlayer), (override));
    MOCK_METHOD(bool, IsMovePossible, (Pos mouseCell), (const, override));
    MOCK_METHOD(void, MoveCurrentFiguresToNewCell, (Pos mouseCell, std::unique_ptr<IPlayer>& opponent), (override));
    MOCK_METHOD(void, CreateFigures, (TexturesMap& textures, IPlayerPtr& white, IPlayerPtr& black), (override));
    MOCK_METHOD(void, Animate, (const Pos& mousePos), (override));
    MOCK_METHOD(void, EndAnimation, (const Pos& mousePos), (override));
    MOCK_METHOD(bool, IsAnimating, (), (const, override));
    MOCK_METHOD(void, StartAnimation, (), (override));
};
