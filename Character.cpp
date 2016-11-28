/*Source File for Class Character
27 Nov 2016
Michael Bilan & Corey Gray
This is the source for class Character, including member-specific functions for updating values.*/

#include "Character.h"
#include <string>
using std::string;
#include <ctime>
using std::time_t;
using std::time;
#include <sstream>
using std::istringstream;
#include <iostream>
using std::cout;
using std::endl;

//source build for function skillUp in Character.h
int Character::skillUp()
{
    //sets threshold for comparison equal to number of skills squared multiplied by one hour in seconds
    int newskill = (_skills*_skills)*3600;
    //gets current epoch time
    time_t now = time(NULL);
    //compares current epoch to last stored time value
    int diff = (now - _lasttime);
    //compares time difference to newskill threshold to determine if a skill upgrade happens
    if((diff/3600)>=newskill)
    {
        //if threshold met or exceeded, increase skill count by 1 and set previous time to current time
        ++_skills;
        _lasttime = now;
    }
    return diff/3600;
}

void Character::setname(string name)
{
    _charname = name;
}

void Character::setlevel(string level)
{
    istringstream iss(level);
    iss >> _level;
}

void Character::sethpmax(string hpm)
{
    istringstream iss(hpm);
    iss >> _hpmax;
}

void Character::sethpcur(string hpc)
{
    istringstream iss(hpc);
    iss >> _hpcur;
}

void Character::setskills(string skl)
{
    istringstream iss(skl);
    iss >> _skills;
}

void Character::settime(string tmlst)
{
    istringstream iss(tmlst);
    iss >> _lasttime;
}

void Character::printinfo()
{
    cout << "Name: " << _charname << endl;
    cout << "Level: " << _level << endl;
    cout << "HP Max: " << _hpmax << endl;
    cout << "HP Current: " << _hpcur << endl;
    cout << "Skills Known: " << _skills << endl;
    cout << "Time Since Last Update: " << skillUp() << endl;
}
