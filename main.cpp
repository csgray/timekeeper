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
# include <map>
using std::map;

int main()
{
	cout << "Welcome to Time Tracker." << endl;
	cout << "This program reads the last time the file was updated and the total elapsed time since the first read." << endl;
	cout << "Then it updates the file with the current read time and total elapsed time." << endl;
	cout << endl;
	
	// Creates a map of key-value pairs from a file of character names
	string file1 = "names.txt";
	ifstream names_file(file1);
	if (!names_file)
	{
		cout << "Error reading " << file1 << endl;
		return 0;
	}

	vector <string> vnames;
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
		vnames.push_back(line1);
	}
	names_file.close();

	map<int, string> names;
	for (unsigned int i = 0; i < vnames.size(); ++i)
	{
		names[i] = vnames[i];
	}
		
	// Creates a map of key-value pairs from a file of character levels
	string file2 = "levels.txt";
	ifstream levels_file(file2);
	if (!levels_file)
	{
		cout << "Error reading " << file2 << endl;
		return 0;
	}

	vector <string> slevels;
	string line2;
	while (true)
	{
		getline(levels_file, line2);
		if (!levels_file)
		{
			if (levels_file.eof())
			{
				break;
			}
			else
			{
				cout << "Error reading " << file2 << endl;
				return 0;
			}
		}
		slevels.push_back(line2);
	}
	levels_file.close();

	map<int, vector<long long int>> levels;
	for (unsigned int i = 0; i < slevels.size(); ++i)
	{
		vector<long long int> ilevels;
		istringstream iss(slevels[i]);
		long long int temp;
		
		while (iss >> temp)
		{
			ilevels.push_back(temp);
		}
		
		levels[i] = ilevels;
	}

	// Prints map of characters
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
	vector<long long int> char_levels = levels[key];
	int level = char_levels[0];
	int next_level = (level + 1) * (level + 1) * 3600;
	long long int last_update = char_levels[1];
	long long int total_ticks = char_levels[2];

	// Calculates elapsed time
	system_clock::time_point tp_now = system_clock::now();
	time_t now = system_clock::to_time_t(tp_now);
	long long int elapsed = now - last_update;
	total_ticks = total_ticks + elapsed;

	// Output to user
	cout << endl;
	cout << "You selected: " << names[key] << endl;
	cout << "Character level is " << level << endl;
	cout << next_level << " seconds are needed for the next level." << endl;
	cout << "The difference in times is " << elapsed << " seconds." << endl;
	cout << "The total elapsed time is " << total_ticks << " seconds." << endl;

	// TODO: Update file with new values
	// Update the char_levels vector then use that to update the levels map?
	// Then write all of levels map to file2?
}
