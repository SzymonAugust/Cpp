#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "bets.h"

#define ZERO_H 70
#define ONE_H 85
#define TWO_H 85
#define THREE_H 36
#define FOUR_H 19
#define FIVE_H 1

#define ZERO_A 90
#define ONE_A 101
#define TWO_A 59
#define THREE_A 31
#define FOUR_A 10
#define FIVE_A 3

using namespace std;

int main()
{
    vector<int> possible_home_results;
    vector<int> possible_away_results;
    vector<int> results;
    size_t i;
    vector<string> matchday;
    vector<string>::iterator iter_matchday;

    srand(static_cast<unsigned>(time(nullptr)));

    openFile(matchday);
    fillPossibleResults(possible_home_results,ZERO_H,ONE_H,TWO_H,THREE_H,FOUR_H,FIVE_H);
    fillPossibleResults(possible_away_results,ZERO_A,ONE_A,TWO_A,THREE_A,FOUR_A,FIVE_A);
    drawResults(results,possible_home_results,possible_away_results);

    for(iter_matchday = matchday.begin(), i = 0; iter_matchday != matchday.end(); iter_matchday += 2, i +=2)
        cout << *iter_matchday << " - " << *(iter_matchday+1) << " " << results[i] << ":" << results[i+1] << endl;

    return 0;
}
