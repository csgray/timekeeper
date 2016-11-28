// main.cpp
// Mike Bilan and Corey Gray
// 27 Nov 2016
// Reads time from file, calculates elapsed time, and writes output to file

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <ctime>
using std::time_t;
using std::time;
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

int main()
{
	cout << "Welcome to Time Tracker." << endl;
	string filename;

	while (true)
	{
		cout << "Which file are we opening? (Enter to exit)" << endl;
		getline(cin, filename);
		if (!cin)
		{
			cout << "Input error." << endl;
			continue;
		}
		if (filename.empty())
		{
			cout << "Thanks, goodbye!" << endl;
		}
		break;
	}

	ifstream infile(filename);
	if (!infile)
	{
		cout << "Error" << endl;
	}

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
				cout << "Error." << endl;
				return 0;
			}
		}
		times.push_back(line);
	}

	int oldt;
	istringstream iss(times[0]);
	iss >> oldt;

	int elapsed;
	istringstream iss2(times[1]);
	iss2 >> elapsed;

	time_t now = time(NULL);

	long int diff = now - oldt;

	elapsed = elapsed + diff;

	cout << "The difference in times is " << diff << " seconds." << endl;
	cout << "The total elapsed time is " << elapsed << " seconds." << endl;

	while (true)
	{
		cout << "Where are we storing the new time?" << endl;
		getline(cin, filename);
		if (!cin)
		{
			cout << "Input error." << endl;
			continue;
		}
		break;
	}

	ofstream outfile(filename);
	outfile << now << endl;
	outfile << elapsed << endl;
	return 0;

}
