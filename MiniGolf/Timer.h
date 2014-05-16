#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <iostream>
#include <windows.h>

using namespace std;

class Timer
{
public:
	Timer();

	void start();

	void stop();

	double get_elapsed_time();

	double get_elapsed_time_in_sec();

	double get_elapsed_time_in_milli_sec();

	double get_elapsed_time_in_micro_sec();

	string get_time_stamp();

private:
	double start_time_in_micro_sec;

	double end_time_in_micro_sec;

	int stopped;

	LARGE_INTEGER frequency;

	LARGE_INTEGER startCount;

	LARGE_INTEGER endCount;
};

#endif