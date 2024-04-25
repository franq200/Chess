#pragma once
class IGame
{
public:
	virtual ~IGame() = default;
	virtual void Update() = 0;
};

