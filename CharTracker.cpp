/*Final Project
Michael Bilan & Corey Gray
27 Nov 2016
Program will allow user to input character name to access .txt file containing character data, then update data based on present time.*/

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
using std::getline;
#include <fstream>
using std::ifstream;
using std::ofstream;
#include <vector>
using std::vector;
#include <sstream>
using std::istringstream;

#include "Character.h"

//takes text input from user when called, errors checks input source
void userin(string &uin)
{
    while(true)
    {
        getline(cin, uin);
        if(!cin)
        {
            cout << "Input error, please try again." << endl;
            continue;
        }
        break;
    }
}

//imports character data from file to current runtime instance
bool getChar(Character &worksheet, string const filename)
{
    vector<string> info;
    while (true)
    {
        string line;
        ifstream ofile(filename);
        getline(ofile,line);
        //error check text file input
        if(!ofile)
        {
            //if error was caused by end of file, break loop
            if(ofile.eof())
                break;
            else
            {
                //if error was not caused by end of file, print error message and return false for error flag
                cout << "Error reading from file." << endl;
                return false;
            }
        }
        //add current line to string
        info.push_back(line);
    }
    worksheet.setname(info[0]);
    worksheet.setlevel(info[1]);
    worksheet.sethpmax(info[2]);
    worksheet.sethpcur(info[3]);
    worksheet.setskills(info[4]);
    worksheet.settime(info[5]);
    return true;
}

int main()
{
    string charname;
    string filename;
    Character nchar;

    cout << "Welcome to the Character Time Tracker!" << endl;
    while (true)
    {
        cout << "Which character are you working on today? (Enter to exit)" << endl;
        userin(charname);
        if(charname.empty())
        {
            cout << "Good-bye!" << endl;
            return 0;
        }
        cout << charname << " selected!" << endl << endl;
        cout << "Looking for file '" << charname << ".txt'" << endl;
        filename = charname + ".txt";
        ifstream ofile(filename);
        if (!ofile)
        {
            cout << "Character file '" << filename << "' not found." << endl << endl;
        }
        else
            break;
    }
    cout << "Success!" << endl << endl;
    cout << "Importing character data..." << endl;
    bool error = getChar(nchar, filename);
    if (!error)
    {
        cout << "Sorry, good-bye." << endl;
        return 0;
    }

    cout << "Done!" << endl << endl;
    nchar.printinfo();
}
