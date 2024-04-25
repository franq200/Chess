#include "Texture.h"
#include <string>

bool Texture::LoadFromFile(const std::string& filename)
{
    return m_texture.loadFromFile(filename);
}

const sf::Texture* Texture::GetTexture() const
{
    return &m_texture;
}
