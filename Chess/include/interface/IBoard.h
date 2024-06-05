#pragma once
#include <memory>
#include <map>
#include <string>
#include "Helper.h"

class ITexture;

using FigureName = std::string;
using TextureContainer = std::map<FigureName, std::unique_ptr<ITexture>>;

class IWindow;

class IBoard
{
public:
	virtual ~IBoard() = default;
	virtual void Draw(std::unique_ptr<IWindow>& window) = 0;
	virtual bool IsCellOccupied(Pos mousePos) const = 0;
	virtual void SetCurrentFigure(Pos mousePos) = 0;
	virtual bool IsCurrentFigureSet() const = 0;
	virtual bool IsMovePossible(Pos mousePos) const = 0;
	virtual void MoveCurrentFiguresToNewCell(Pos mousePos) = 0;
	virtual void CreateFigures(TextureContainer& textures) = 0;
};

