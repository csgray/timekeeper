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
	
	// Data vectors
	vector<string> names;
	vector<long long int> times;
	vector<int> levels;
	vector<int> ticks;

	// Populates names from file
	string file1 = "names.txt";
	ifstream names_file(file1);
	if (!names_file)
	{
		cout << "Error reading " << file1 << endl;
		return 0;
	}
	string line1;
	while (true)
	{
		getline(names_file, line1);
		if (!names_file)
		{
			if (names_file.eof())
			{
				break;
			}
			else
			{
				cout << "Error reading " << file1 << endl;
				return 0;
			}
		}
		names.push_back(line1);
	}
	names_file.close();

	// Populates times from file
	string file2 = "times.txt";
	ifstream times_file(file2);
	if (!times_file)
	{
		cout << "Error reading " << file2 << endl;
		return 0;
	}
	string line2;
	while (true)
	{
		getline(times_file, line2);
		if (!times_file)
		{
			if (times_file.eof())
			{
				break;
			}
			else
			{
				cout << "Error reading " << file2 << endl;
				return 0;
			}
		}
		istringstream iss(line2);
		long long int temp;
		iss >> temp;
		times.push_back(temp);
	}
	times_file.close();

	// Populates levels from file
	string file3 = "levels.txt";
	ifstream levels_file(file3);
	if (!levels_file)
	{
		cout << "Error reading " << file3 << endl;
		return 0;
	}
	string line3;
	while (true)
	{
		getline(levels_file, line3);
		if (!levels_file)
		{
			if (levels_file.eof())
			{
				break;
			}
			else
			{
				cout << "Error reading " << file3 << endl;
				return 0;
			}
		}
		istringstream iss(line3);
		int temp;
		iss >> temp;
		levels.push_back(temp);
	}
	levels_file.close();

	// Populates ticks from file
	string file4 = "ticks.txt";
	ifstream ticks_file(file4);
	if (!ticks_file)
	{
		cout << "Error reading " << file4 << endl;
		return 0;
	}
	string line4;
	while (true)
	{
		getline(ticks_file, line4);
		if (!ticks_file)
		{
			if (ticks_file.eof())
			{
				break;
			}
			else
			{
				cout << "Error reading " << file4 << endl;
				return 0;
			}
		}
		istringstream iss(line4);
		int temp;
		iss >> temp;
		ticks.push_back(temp);
	}
	ticks_file.close();

	while (true)
	{
		// Prints list of characters
		for (unsigned int i = 0; i < names.size(); ++i)
		{
			cout << i << ". " << names[i] << endl;
		}
		cout << endl;

		// Character selection prompt
		cout << "Select the character you wish to update." << endl;
		string skey;
		getline(cin, skey);
		if (!cin)
		{
			cout << "Input error." << endl;
			return 0;
		}
		int key;
		istringstream ikey(skey);
		ikey >> key;

		// Retrieves and calculates character data
		string name = names[key];
		long long int last_update = times[key];
		int level = levels[key];
		int next_level = (level + 1) * (level + 1) * 3600;
		int total_ticks = ticks[key];

		// Calculates elapsed time
		system_clock::time_point tp_now = system_clock::now();
		time_t now = system_clock::to_time_t(tp_now);
		int elapsed = now - last_update;
		total_ticks = total_ticks + elapsed;

		// Output to user
		cout << endl;
		cout << "You selected: " << name << endl;
		cout << "Character level is " << level << endl;
		cout << next_level << " seconds are needed for the next level." << endl;
		cout << "The difference in times is " << elapsed << " seconds." << endl;
		cout << "The total elapsed time is " << total_ticks << " seconds." << endl;
		cout << endl;

		// Increase level
		while (total_ticks >= next_level)
		{
			total_ticks = total_ticks - next_level;
			next_level = (level + 1) * (level + 1) * 3600;
			++level;
			cout << "Congratulations! " << name << " is now level " << level << "!" << endl;
			cout << "Next level: " << total_ticks << "/" << next_level << endl;
			cout << endl;
		}

		// Update files
		times[key] = now;
		levels[key] = level;
		ticks[key] = total_ticks;

		ofstream times_update(file2);
		for (unsigned int i = 0; i < times.size(); ++i)
		{
			times_update << times[i] << endl;
		}
		times_update.close();

		ofstream levels_update(file3);
		for (unsigned int i = 0; i < levels.size(); ++i)
		{
			levels_update << levels[i] << endl;
		}
		levels_update.close();

		ofstream ticks_update(file4);
		for (unsigned int i = 0; i < ticks.size(); ++i)
		{
			ticks_update << ticks[i] << endl;
		}
		ticks_update.close();
	}
}
