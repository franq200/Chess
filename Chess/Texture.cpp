#include "Texture.h"

bool Texture::LoadFromFile(const std::string& filename)
{
    return m_texture.loadFromFile(filename);
}
