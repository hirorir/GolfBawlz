#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>

class Timer
{
private:
	float32 dt; // Delta time.
	UINT64 time_begin; // Start time of timer.
	UINT64 time_end; // End time of timer.

public:
	// Construct a clock.
	explicit Timer()
	{
		dt = 1.0f / 30.0f; // Initial dt.
	}

	void start() // Record the start time of the timer.
	{
		time_begin = read_hi_res_timer();
	}

	void end() // Record the end time of the timer.
	{
		time_end = read_hi_res_timer();
		dt = (float32)(time_end - time_begin) * 1000 / (float32)read_hi_res_timer_frequency();
	}

	float32 get_dt() // Query seconds passed.
	{
		return dt;
	}

	static UINT64 read_hi_res_timer_frequency() // Gives machine clock frequency.
	{
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);
		return (UINT64)freq.QuadPart;
	}

	static UINT64 read_hi_res_timer()
	{
		LARGE_INTEGER tim;
		QueryPerformanceCounter(&tim);
		return (UINT64)tim.QuadPart;
	}
};

#endif