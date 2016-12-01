// timetracker.cpp
// Mike Bilan and Corey Gray
// 27 Nov 2016
// Maintains a psuedo-database of characters where each 'table' is a separate file
// and tracks the elapsed seconds towards each character's next level

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
#include <sstream>
using std::istringstream;
#include "utilities.h"

int main()
{
	cout << "Welcome to Time Tracker." << endl;
	cout << "This program maintains a psuedo-database of characters and tracks the elapsed seconds towards their next level." << endl;
	cout << endl;

    // Source file names, cannot be modified
    const string fileNames = "names.txt";
    const string fileTimes = "times.txt";
    const string fileLevels = "levels.txt";
    const string fileTicks = "ticks.txt"; // 'ticks' are seconds

	// Data vectors
	vector<string> names;
	vector<long long int> times;
	vector<long long int> levels;
	vector<long long int> ticks;

	// Checks if all required text database files are available
	// If a file is unavailable, creates new file database
	if(!checkFiles(fileNames,fileTimes,fileLevels,fileTicks))
    {
        cout << "One or more required database files were unavailable." << endl;
        cout << "Creating new database files...";
        if(!makeFiles(fileNames,fileTimes,fileLevels,fileTicks))
        {
            cout << "Error in file creation. Goodbye." << endl;
            return 0;
        }
        cout << " Done!" << endl << endl;
    }

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
		cout << names.size() << ". Create a new character." << endl;
		cout << names.size()+1 << ". Delete a character." << endl;
		cout << endl;

		// Take character selection from user
        unsigned int selection;
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
			cout << endl;
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
		// Character removal
		else if (selection == names.size()+1)
        {
            cout << endl;
            cout << "Which character do you want to remove? (Enter to cancel)" << endl;
    		for (size_t i = 0; i < names.size(); ++i)
            {
                cout << i << ". " << names[i] << endl;
            }
            cout << endl;
            string remchar;
            getline(cin, remchar);
            if(!cin)
            {
                cout << "Input error." << endl;
                return 0;
            }
            else if (remchar.empty())
            {
                continue;
            }
            istringstream rmc(remchar);
            int choice;
            rmc >> choice;

            // Erase data for user selection
            cout << "Deleting " << names[choice] << " and all associated data... ";
            names.erase(names.begin()+choice);
            times.erase(times.begin()+choice);
            levels.erase(levels.begin()+choice);
            ticks.erase(ticks.begin()+choice);
            cout << "Done!" << endl;

            // Update name file
			saveName(fileNames,names);
			cout << endl;
			continue;
        }


		// Retrieves and calculates character data
		string name = names[selection];
		long long int last_update = times[selection];
		long long int level = levels[selection];
		long long int next_level = (level + 1) * (level + 1) * 3600;
		long long int total_ticks = ticks[selection];
		long long int elapsed = now - last_update;
		total_ticks = total_ticks + elapsed;

		// Output to user
		cout << endl;
		cout << "You selected: " << name << endl;
		cout << "You last accessed this character " << elapsed << " seconds ago." << endl;
		cout << "They are level " << level << "." << endl;
		cout << "They now have " << total_ticks << "/" << next_level << " seconds towards their next level." << endl;
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

		// Update non-name objects and save to respective source files
		times[selection] = now;
		levels[selection] = level;
		ticks[selection] = total_ticks;

		saveFile(fileTimes, times);
		saveFile(fileLevels, levels);
		saveFile(fileTicks, ticks);
	}
}
