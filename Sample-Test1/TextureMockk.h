#pragma once
#include "gmock/gmock.h"
#include "interface/ITexture.h"

class TextureMockk : public ITexture
{
public:
	MOCK_METHOD(bool, LoadFromFile, (const std::string& filename), (override));
};

