// main.cpp
// Mike Bilan and Corey Gray
// 27 Nov 2016
// Reads time from file, calculates elapsed time, and writes output to file

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
using std::getline;
#include <vector>
using std::vector;
#include <chrono>
using std::chrono::system_clock;
#include "Utilities.h"

int main()
{
	cout << "Welcome to Time Tracker." << endl;
	cout << "This program reads the last time the file was updated and the total elapsed time since the first read." << endl;
	cout << "Then it updates the file with the current read time and total elapsed time." << endl;
	cout << endl;

    // Source file names, cannot be modified
    const string fileNames = "names.txt";
    const string fileTimes = "times.txt";
    const string fileLevels = "levels.txt";
    const string fileTicks = "ticks.txt";

	// Data vectors
	vector<string> names;
	vector<long long int> times;
	vector<long long int> levels;
	vector<long long int> ticks;

	// Populates names from file, quits if file was unavailable
	if(!popNames(fileNames, names))
    {
        return 0;
    }

	// Populates times from file, quits if file was unavailable
	if(!popNums(fileTimes, times))
    {
        return 0;
    }

	// Populates levels from file, quits if file was unavailable
	if(!popNums(fileLevels, levels))
    {
        return 0;
    }

	// Populates ticks from file, quits if file was unavailable
    if(!popNums(fileTicks, ticks))
    {
        return 0;
    }

	while (true)
	{
		// Character selection prompt
		cout << "Select the character you wish to update or create a new character." << endl;
		cout << "Or enter a blank line to quit." << endl;

		// Prints list of characters
		for (size_t i = 0; i < names.size(); ++i)
		{
			cout << i << ". " << names[i] << endl;
		}
		cout << names.size() << ". " << "Create a new character." << endl;
		cout << endl;

		//take character selection from user
        int selection;
        if(!userIn(selection, names))
        {
            return 0;
        }

		// Current time
		system_clock::time_point tp_now = system_clock::now();
		time_t now = system_clock::to_time_t(tp_now);

		// New character creation
		if (selection == names.size())
		{
			cout << endl;
			cout << "What is this new character called? Blank line to cancel." << endl;
			string new_name;
			getline(cin, new_name);
			if (!cin)
			{
				cout << "Input error." << endl;
				return 0;
			}
			if (new_name.empty())
			{
				continue;
			}

			// Update vectors for new character entry
			names.push_back(new_name);
			times.push_back(now);
			levels.push_back(0);
			ticks.push_back(0);

			// Update name file
			saveName(fileNames,names);
		}


		// Retrieves and calculates character data
		string name = names[selection];
		long long int last_update = times[selection];
		int level = levels[selection];
		int next_level = (level + 1) * (level + 1) * 3600;
		int total_ticks = ticks[selection];
		int elapsed = now - last_update;
		total_ticks = total_ticks + elapsed;

		// Output to user
		cout << endl;
		cout << "You selected: " << name << endl;
		cout << "Character level is " << level << endl;
		cout << next_level << " seconds are needed for the next level." << endl;
		cout << "You last accessed this character " << elapsed << " seconds." << endl;
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

		// Update non-name files
		times[selection] = now;
		levels[selection] = level;
		ticks[selection] = total_ticks;

		saveFile(fileTimes, times);
		saveFile(fileLevels, levels);
		saveFile(fileTicks, ticks);
	}
}
