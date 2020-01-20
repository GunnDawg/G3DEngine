#pragma once


struct DeltaClock

{
	static void Init()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&prevTime);
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		secondsPerCount = 1.0f / countsPerSec;
	}

	static void BeginTick()
	{
		currentTime = 0u;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
		deltaTime = (currentTime - prevTime) * secondsPerCount * 1000;
	}
	static void EndTickk()
	{
		prevTime = currentTime;
	}

	inline static i64 prevTime = 0u;
	inline static i64 currentTime = 0u;
	inline static i64 countsPerSec = 0u;
	inline static float secondsPerCount = 0.0f;
	inline static float deltaTime = 0.0f;
};