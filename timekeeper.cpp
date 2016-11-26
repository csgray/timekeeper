// timekeeper.cpp
// Corey Gray
// 26 Nov 2016
// CS 201 Final Project: Tracks elapsed time and updates a file

# include <iostream>
using std::cout;
using std::endl;
# include <chrono>
using std::chrono::system_clock;

int main()
{
	system_clock::time_point tp_now = system_clock::now();
	time_t now = system_clock::to_time_t(tp_now);

	cout << "The time is " << now << " seconds since the epoch." << endl;

	time_t last_update = 1480201225; // Approximately 26 Nov 2016 14:00 Alaskan Standard Time
	signed long long int elapsed = now - last_update;

	cout << elapsed << " seconds has elapsed since the last update." << endl;
}