#pragma once
#include <string>

namespace sf
{
	class Texture;
}

class ITexture
{
public:
	virtual ~ITexture() = default;
	virtual bool LoadFromFile(const std::string& filename) = 0;
	virtual const sf::Texture* GetTexture() const = 0;
private:
};

