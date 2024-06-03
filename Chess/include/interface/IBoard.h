#pragma once
#include <memory>
#include <map>
#include <string>

class ITexture;

using FigureName = std::string;
using TextureContainer = std::map<FigureName, std::unique_ptr<ITexture>>;

class IWindow;

class IBoard
{
public:
	virtual ~IBoard() = default;
	virtual void Draw(std::unique_ptr<IWindow>& window) = 0;
	virtual void CreateFigures(const TextureContainer& textures) {}
};

