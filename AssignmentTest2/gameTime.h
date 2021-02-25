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
	void init(int fps);
	void Update();
	int framesToUpdate();
private:
	LONGLONG start;
	LARGE_INTEGER timer_freq;
	LARGE_INTEGER time_now;
	LARGE_INTEGER time_previous;
	float intervalsPerFrame;
	int Requested_FPS;
	float frequencySeconds;
};

//class FrameTimer {
//
//public:
//	bool init(int);
//	int framesToUpdate();
//	float elapsedTime;
//	float totalGameTime;
//private:
//	LARGE_INTEGER timer_freq;
//	LARGE_INTEGER time_now;
//	LARGE_INTEGER time_previous;
//	int Requested_FPS;
//	float intervalsPerFrame;
//
//};


//class GameTimer
//{
//public:
//	GameTimer();
//
//	float TotalTime()const;		//the game total time
//	float DeltaTime()const;		//the time between every frame
//
//	void Reset();               //use before message loop
//	void Start();              //use when cancle pause
//	void Stop();              //use when stop
//	void Tick();             //use with every frame
//
//private:
//	double m_SecondsPerCount;  //the time between counter the unit is second
//	double m_DeltaTime;
//
//	__int64 m_BaseTime;
//	__int64 m_PausedTime;
//	__int64 m_StopTime;
//	__int64 m_PrevTime;
//	__int64 m_CurrTime;
//
//	bool m_Stopped;
//};
#endif /* GAME_H */