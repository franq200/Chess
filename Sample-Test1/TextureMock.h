#pragma once
#include "gmock/gmock.h"
#include "interface/ITexture.h"

class TextureMock : public ITexture
{
public:
	MOCK_METHOD(bool, LoadFromFile, (const std::string& filename), (override));
	MOCK_METHOD(const sf::Texture*, GetTexture, (), (const override));
};

