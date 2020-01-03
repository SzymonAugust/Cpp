#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#ifndef BETS_H
#define BETS_H

void openFile (vector<string>&);
void fillPossibleResults(vector<int>&,int,int,int,int,int,int);
void drawResults(vector<int>&,vector<int>&,vector<int>&);

#endif // BETS_H
