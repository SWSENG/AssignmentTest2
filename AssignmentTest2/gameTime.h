#pragma once
#ifndef GAMETIME_H
#define GAMETIME_H

#include <Windows.h>

class GameTime
{
public:
	float elapsedTime;
	float totalGameTime;

	bool Initialize();
	void Update();
private:
	LONGLONG start;
	float frequencySeconds;
};
#endif /* GAME_H */