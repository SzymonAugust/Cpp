#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "bets.h"

#define SIZE 16

void openFile(vector<string> &vs)
{
    ifstream data("bets.txt");

    if (!(data.good()))
        exit(1);

    string input_string;
    vector<string> input;

    while(getline(data, input_string))
        input.push_back(input_string);
    data.close();

    for (auto x : input)
    {
        string tmp;
        stringstream s(x);

        while (getline(s,tmp,';'))
            vs.push_back(tmp);
    }
}

void fillPossibleResults(vector<int> &vs, int zero, int one, int two, int three, int four, int five)
{
    for (int i = 0; i < zero; i++)
        vs.push_back(0);
    for (int i = 0; i < one; i++)
        vs.push_back(1);
    for (int i = 0; i < two; i++)
        vs.push_back(2);
    for (int i = 0; i < three; i++)
        vs.push_back(3);
    for (int i = 0; i < four; i++)
        vs.push_back(4);
    for (int i = 0; i < five; i++)
        vs.push_back(5);
}

void drawResults(vector<int> &whole, vector<int> &home, vector<int> &away)
{
    unsigned long long home_size = home.size();
    unsigned long long away_size = away.size();
    unsigned long long tmp_h;
    unsigned long long tmp_a;

    for (int i = 0; i < SIZE/2; i++)
    {
        tmp_h = static_cast<unsigned long long>(rand()) % home_size;
        tmp_a = static_cast<unsigned long long>(rand()) % away_size;

        whole.push_back(home[tmp_h]);
        whole.push_back(away[tmp_a]);
    }
}
