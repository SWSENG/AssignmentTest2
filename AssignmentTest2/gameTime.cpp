#include "gameTime.h"

bool GameTime::Initialize()
{
	LARGE_INTEGER i;

	if (!QueryPerformanceFrequency(&i))
		return false;

	frequencySeconds = (float)(i.QuadPart);

	QueryPerformanceCounter(&i);
	start = i.QuadPart;
	totalGameTime = 0;

	return true;
}

void GameTime::Update()
{
	LARGE_INTEGER i;

	QueryPerformanceCounter(&i);
	elapsedTime = (float)(i.QuadPart - start) / frequencySeconds;

	start = i.QuadPart;
	totalGameTime += elapsedTime;
}

