#include "defs.h"

void initTimer(void)
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	d_secondsPerTick = 1.0 / (double)frequency.QuadPart;

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	li_timeCount = counter.QuadPart;
}

float timeElapsed(void)
{
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);

	__int64 timeInterval = counter.QuadPart - li_timeCount;
	li_timeCount = counter.QuadPart;

	double secondsElapsed = (double)timeInterval * d_secondsPerTick;
	d_timeElapsed += secondsElapsed;

	return (float)d_timeElapsed;
}