#pragma once
#include <SFML/Graphics.hpp>
#include "interface/ITexture.h"

class Texture : public ITexture
{
public:
	__declspec(dllexport) bool LoadFromFile(const std::string& filename) override;
	__declspec(dllexport) const sf::Texture* GetTexture() const override;
private:
	sf::Texture m_texture;
};

