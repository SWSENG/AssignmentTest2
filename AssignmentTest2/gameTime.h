#pragma once
#ifndef GAMETIME_H
#define GAMETIME_H

#include "systemClass.h"

class GameTime
{
public:
	GameTime();
	~GameTime();

	void init(int fps);
	int framesToUpdate();
private:
	LARGE_INTEGER timer_freq;
	LARGE_INTEGER time_now;
	LARGE_INTEGER time_previous;
	float intervalsPerFrame;
	int Requested_FPS;
};
#endif