#pragma once
#include <string>

class ITexture
{
public:
	virtual ~ITexture() = default;
	virtual bool LoadFromFile(const std::string& filename) = 0;
private:
};

