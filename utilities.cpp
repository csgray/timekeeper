// utilities.cpp
// Mike Bilan & Corey Gray
// 29 Nov 2016
// Source file contains reusable functions for timetracker.cpp

#include "utilities.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <sstream>
using std::istringstream;
#include <fstream>
using std::ifstream;
using std::ofstream;

// Function reads lines from specified files to populate vector list of character names
bool popNames(string file, vector<string> &names)
{
    ifstream names_file(file);

    // Check if file was able to be opened
	if (!names_file)
	{
		cout << "Error reading " << file << " - goodbye!" << endl;
		return false;
	}
	string line;

	// Read all lines in file until end of file or read error
	while (true)
	{
		getline(names_file, line);
		if (!names_file)
		{
			if (names_file.eof())
			{
				break;
			}
			else
			{
				cout << "Error reading " << file << " - goodbye!" << endl;
				return false;
			}
		}
		names.push_back(line);
	}

	// Close file once read is done to avoid potential conflicts
	names_file.close();
	return true;
}


// Function reads from file and stores in passed vector object
bool popNums(string file, vector<long long int> &data)
{
	ifstream inputfile(file);

	// Check if file was able to be opened
	if (!inputfile)
	{
		cout << "Error reading " << file << " - goodbye!" << endl;
		return false;
	}
	string line;

	// Read all lines of file until end of file or read error
	while (true)
	{
		getline(inputfile, line);
		if (!inputfile)
		{
			if (inputfile.eof())
			{
				break;
			}
			else
			{
				cout << "Error reading " << file << " - goodbye!" << endl;
				return false;
			}
		}

		// Convert strings to integer values and store in data vector
		istringstream iss(line);
		long long int temp;
		iss >> temp;
		data.push_back(temp);
	}
	inputfile.close();
    return true;
}


// Take user input for menu prompts, checking for errors in user entry
bool userIn(unsigned int &key, vector<string> names)
{
    while(true)
    {
		string skey;
		getline(cin, skey);
		if (!cin)
		{
			cout << "Input error - goodbye." << endl;
			return false;
		}
		else if (skey.empty())
		{
			cout << "Goodbye." << endl;
			return false;
		}
		bool error=false;

		// Input is numeric-only, verify only digit entries
		for(size_t x=0; x<skey.size(); ++x)
        {
            if(skey[x]<'0'||skey[x]>'9')
            {
                cout << "Invalid selection - please try again." << endl;
                error=true;
                break;
            }

        }
        if(error)
            continue;

        // Convert string selection to integer selection if digit-only value entered
		istringstream ikey(skey);
		ikey >> key;

		// Confirm valid user selection
        if (key > names.size())
        {
            cout << "Invalid selection - please try again." << endl;
            continue;
        }
        return true;
    }
}


// Save function specifically for vector string object containing character names
void saveName(string file, vector<string> data)
{
    // Open file output destination
    ofstream ofile(file);

    // Write all entries in data set to file
    for (size_t i = 0;
     i < data.size(); ++i)
    {
        ofile << data[i] << endl;
    }

    // Close file
    ofile.close();
}


// Save function for all vector objects that store integer values
void saveFile(string file, vector<long long int> data)
{
    // Open file output destination
    ofstream ofile(file);

    // Write all entries in data set to file
    for (size_t i = 0; i < data.size(); ++i)
    {
        ofile << data[i] << endl;
    }

    // Close file
    ofile.close();
}
