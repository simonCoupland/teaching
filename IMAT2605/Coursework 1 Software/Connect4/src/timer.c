#include "defs.h"

void initTimer(void)
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	s_dSecondsPerTick = 1.0 / (double)frequency.QuadPart;

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	s_liTimeCount = counter.QuadPart;
}

float timeElapsed(void)
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	__int64 timeInterval = counter.QuadPart - s_liTimeCount;
	s_liTimeCount = counter.QuadPart;

	double secondsElapsed = (double)timeInterval * s_dSecondsPerTick;
	s_dTimeElapsed += secondsElapsed;

	return (float)s_dTimeElapsed;
}