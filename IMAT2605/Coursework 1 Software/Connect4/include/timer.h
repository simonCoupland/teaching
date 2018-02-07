#pragma once

// Static ensures the variables are around for the emntire lifetime of the program
static double s_dTimeElapsed = 0;
static double s_dSecondsPerTick = 0;
static __int64 s_liTimeCount = 0;

// Start the timer
void initTimer(void);
// Find out how many seconds have elapsed
float timeElapsed(void);