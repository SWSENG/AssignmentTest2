#pragma once


class gameState
{
public:
	virtual void init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;

};