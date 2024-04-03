#pragma once
#include "gmock/gmock.h"
#include "..\Chess\ITexture.h"

class TextureMockk : public ITexture
{
public:
	MOCK_METHOD(bool, LoadFromFile, (const std::string& filename), (override));
};

