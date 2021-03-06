// utilities.h
// Mike Bilan & Corey Gray
// 29 Nov 2016
// Header for utilities.cpp

#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

#include <string>
using std::string;
#include <vector>
using std::vector;

bool checkFiles(string file1, string file2, string file3, string file4);

bool makeFiles(string file1, string file2, string file3, string file4);

bool popNames(string file, vector<string> &names);

bool popNums(string file, vector<long long int> &data);

bool userIn(unsigned int &key, vector<string> names);

void saveName(string file, vector<string> data);

void saveFile(string file, vector<long long int> data);

#endif // UTILITIES_H_INCLUDED
