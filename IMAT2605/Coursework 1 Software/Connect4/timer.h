#pragma once

static double d_timeElapsed = 0;
static double d_secondsPerTick = 0;
static __int64 li_timeCount = 0;

void initTimer(void);
float timeElapsed(void);