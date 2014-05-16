#include <cstdlib>
#include "Timer.h"

Timer::Timer()
{
	QueryPerformanceFrequency(&frequency);
	startCount.QuadPart = 0;
	endCount.QuadPart = 0;

	stopped = 0;
	start_time_in_micro_sec = 0;
	end_time_in_micro_sec = 0;
}

void Timer::start()
{
	stopped = 0; // reset stop flag
	QueryPerformanceCounter(&startCount);
}

void Timer::stop()
{
	stopped = 1; // set timer stopped flag
	QueryPerformanceCounter(&endCount);
}

double Timer::get_elapsed_time_in_micro_sec()
{
	if (!stopped) {
		QueryPerformanceCounter(&endCount);
	}

	start_time_in_micro_sec = startCount.QuadPart * (1000000.0 / frequency.QuadPart);
	end_time_in_micro_sec = endCount.QuadPart * (1000000.0 / frequency.QuadPart);

	return end_time_in_micro_sec - start_time_in_micro_sec;
}

double Timer::get_elapsed_time_in_milli_sec()
{
	return this->get_elapsed_time_in_micro_sec() * 0.001;
}

double Timer::get_elapsed_time_in_sec()
{
	return this->get_elapsed_time_in_micro_sec() * 0.000001;
}

double Timer::get_elapsed_time()
{
	return this->get_elapsed_time_in_sec();
}

string Timer::get_time_stamp()
{
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	return asctime(timeinfo);
}