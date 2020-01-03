#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include "bets.h"

#define DRAW 0.15
#define WIN 0.4

void Event::setDecision()
{
    double dif = fabs(this->home.corrected_probability - this->away.corrected_probability);

    if (dif < DRAW)
        this->decision = "You should bet for draw!";
    else if (dif > WIN)
    {
        if (this->home.getBet() < this->away.getBet())
            this->decision = "You should bet for 1st team!";
        else
            this->decision = "You should bet for 2nd team!";
    }
}

void Event::correctProbability()
{
    double whole_probability;

    whole_probability = 1/this->home.getBet()+1/this->draw_bet+1/this->away.getBet();

    this->home.corrected_probability = this->home.getProbability()/whole_probability;
    this->away.corrected_probability = this->away.getProbability()/whole_probability;
    this->draw_corrected_probability = this->draw_probability/whole_probability;
}

ostream &operator<< (ostream &os, Event e)
{
    os << e.home.getName() << " - " << e.away.getName() << endl;
    os << e.home.getName() << ": bet = " << e.home.getBet() << ", probability = " << e.home.corrected_probability << endl;
    os << "Draw: bet = " << e.draw_bet << ", probability = " << e.draw_corrected_probability << endl;
    os << e.away.getName() << ": bet = " << e.away.getBet() << ", probability = " << e.away.corrected_probability << endl;
    os << e.decision << endl << endl;

    return os;
}

void Matchweek::printEvents()
{
    for (auto x : this->events)
        cout << x;
}

void Matchweek::openFile ()
{
    ifstream data("bets.txt");

    if (!data.good())
        exit(1);

    string input_string;
    vector<string> input;

    while (getline(data, input_string))
        input.push_back(input_string);
    data.close();

    for (auto x : input)
    {
        string s;
        vector<string> vs;
        stringstream stream(x);

        while(getline(stream,s,';'))
            vs.push_back(s);

        Team t1(vs[0],atof(vs[1].c_str()));
        Team t2(vs[2],atof(vs[3].c_str()));
        Event e(t1,t2,atof(vs[4].c_str()));

        this->events.push_back(e);
    }
}
