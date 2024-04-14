#pragma once
class IGame
{
public:
	~IGame() = default;
	virtual void Update() = 0;
};

