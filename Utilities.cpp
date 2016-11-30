#include "Utilities.h"
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

bool popNames(string file, vector<string> &names)
{
    ifstream names_file(file);
	if (!names_file)
	{
		cout << "Error reading " << file << " - goodbye!" << endl;
		return false;
	}
	string line;
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
	names_file.close();
	return true;
}

bool popNums(string file, vector<long long int> &data)
{
	ifstream inputfile(file);
	if (!inputfile)
	{
		cout << "Error reading " << file << " - goodbye!" << endl;
		return false;
	}
	string line;
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
		istringstream iss(line);
		long long int temp;
		iss >> temp;
		data.push_back(temp);
	}
	inputfile.close();
    return true;
}

bool userIn(int &key, vector<string> names)
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

		istringstream ikey(skey);
		ikey >> key;

        if (key > names.size())
        {
            cout << "Invalid selection - please try again." << endl;
            continue;
        }
        return true;
    }
}

void saveName(string file, vector<string> data)
{
    ofstream ofile(file);
    for (time_t i = 0; i < data.size(); ++i)
    {
        ofile << data[i] << endl;
    }
    ofile.close();
}

void saveFile(string file, vector<long long int> data)
{
    ofstream ofile(file);
    for (size_t i = 0; i < data.size(); ++i)
    {
        ofile << data[i] << endl;
    }
    ofile.close();
}
