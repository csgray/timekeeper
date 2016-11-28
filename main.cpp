// main.cpp
// Mike Bilan and Corey Gray
// 27 Nov 2016
// Reads time from file, calculates elapsed time, and writes output to file

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <string>
using std::string;
using std::getline;
#include <sstream>
using std::istringstream;
#include <vector>
using std::vector;
# include <chrono>
using std::chrono::system_clock;

int main()
{
	cout << "Welcome to Time Tracker." << endl;
	cout << "This program reads the last time the file was updated and the total elapsed time since the first read." << endl;
	cout << "Then it updates the file with the current read time and total elapsed time." << endl;
	cout << endl;
	
	while (true)
	{
		// User prompt for file or quit
		cout << "Which file are we opening? Enter a blank line to quit." << endl;
		string filename;
		getline(cin, filename);
		if (!cin)
		{
			cout << "Input error." << endl;
			return 0;
		}

		// Quits
		if (filename.empty())
		{
			cout << "Thanks, goodbye!" << endl;
			return 0;
		}

		// Opens file
		ifstream infile(filename);
		
		// Error-checking (usually a nonexistent file)
		if (!infile)
		{
			cout << "File not found. Select a different file." << endl;
			cout << endl;
			continue;
		}

		// Reads lines from file.
		vector <string> times;
		while (true)
		{
			string line;
			getline(infile, line);
			if (!infile)
			{
				if (infile.eof())
				{
					break;
				}
				else
				{
					cout << "Error reading file." << endl;
					return 0;
				}
			}
			times.push_back(line);
		}

		// Closes file (otherwise it will error if opened later)
		infile.close();

		// Checks for an empty vector (from an empty file)
		if (times.empty())
		{
			cout << "Empty file." << endl;
			cout << endl;
			continue;
		}

		// Converts file strings to ints for manipulation
		// long long int required to not lose data while converting time_t to int
		long long int last_update;
		istringstream iss(times[0]);
		iss >> last_update;

		long long int total_ticks;
		istringstream iss2(times[1]);
		iss2 >> total_ticks;

		// Calculates elapsed time
		system_clock::time_point tp_now = system_clock::now();
		time_t now = system_clock::to_time_t(tp_now);
		long long int elapsed = now - last_update;
		total_ticks = total_ticks + elapsed;

		cout << endl;
		cout << "The difference in times is " << elapsed << " seconds." << endl;
		cout << "The total elapsed time is " << total_ticks << " seconds." << endl;

		// User-prompt for output file
		cout << "Where are we storing the new time?" << endl;
		getline(cin, filename);
		if (!cin)
		{
			cout << "Input error." << endl;
			continue;
		}

		// Opens output file and checks for errors
		ofstream outfile(filename);
		if (!outfile)
		{
			cout << "File write error!" << endl;
			return 0;
		}

		// Writes to file
		outfile << now << endl;
		outfile << total_ticks << endl;
		
		cout << endl;
		cout << "Write successful." << endl;
		cout << endl;
	}
}
