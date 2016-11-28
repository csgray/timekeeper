/*Header File for Class Character
Michael Bilan & Corey Gray
27 Nov 2016
This is the header file for the class Character, which prototypes the class object with some base values.*/

#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <string>
using std::string;
#include <ctime>
using std::time;
using std::time_t;

class Character
{
public:
    //default constructor sets name to Unnamed Hero, with default stats
    Character()
    {
        _charname = "Unnamed Hero";
        _level = 1;
        _hpmax = 10;
        _hpcur = _hpmax;
        _skills = 1;
        time_t now = time(NULL);
        _lasttime = now;
    }
    //constructor takes names and builds default character with that name
    Character(string name)
    {
        _charname = name;
        _level = 1;
        _hpmax = 10;
        _hpcur = _hpmax;
        _skills = 1;
        time_t now = time(NULL);
        _lasttime = now;
    }
    //constructor builds character with all stat input
    Character(string name, int lvl, int hpm, int hpc, int skl, int lstm)
    {
        _charname = name;
        _level = lvl;
        _hpmax = hpm;
        _hpcur = hpc;
        _skills = skl;
        _lasttime = lstm;
    }

    //prototype for skillUp
    int skillUp();
    void setname(string name);
    void setlevel(string level);
    void sethpmax(string hpm);
    void sethpcur(string hpc);
    void setskills(string skl);
    void settime(string tmlst);
    void printinfo();

private:
    //data members for class Character
    string _charname;
    int _level;
    int _hpmax;
    int _hpcur;
    int _skills;
    int _lasttime;
};


#endif // CHARACTER_H_INCLUDED
