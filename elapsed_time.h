// elapsed_time.h
// Corey Gray and Mike Bilan
// 27 Nov 2016
// Header for elapsedtime.cpp

#ifndef ELAPSED_TIME_H_INCLUDED
#define ELAPSED_TIME_H_INCLUDED

# include <chrono>
using std::chrono::system_clock;

signed long long int elapsed_time(time_t last_update);

#endif