// elapsedtime.cpp
// Corey Gray and Mike Bilan
// 26 Nov 2016
// CS 201 Final Project: Returns elapsed time based on last_update time fed into function

# include <chrono>
using std::chrono::system_clock;

signed long long int elapsedtime(time_t last_update)
{
	system_clock::time_point tp_now = system_clock::now();
	time_t now = system_clock::to_time_t(tp_now);
	signed long long int elapsed = now - last_update;
	return elapsed;
}