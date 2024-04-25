#pragma once
#include <SFML/Graphics.hpp>
#include "interface/ITexture.h"

class Texture : public ITexture
{
public:
	bool LoadFromFile(const std::string& filename) override;
	const sf::Texture* GetTexture() const override;
private:
	sf::Texture m_texture;
};

