#pragma once
#include <SFML/Graphics.hpp>
#include "interface/ITexture.h"

class Texture : public ITexture
{
public:
	bool LoadFromFile(const std::string& filename) override;
private:
	sf::Texture m_texture;
};

