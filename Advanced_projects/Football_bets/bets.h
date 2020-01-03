#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>

using namespace std;

#ifndef BETS_H
#define BETS_H

class Team {
private:
    string name;
    double bet;
    double probability;
public:
    double corrected_probability = 0;
    Team(string s, double f) : name{s}, bet{f} { probability = 1/bet; }
    string getName() { return name; }
    double getBet() { return bet; }
    double getProbability() { return probability; }
};

class Event {
private:
    Team home;
    Team away;
    double draw_bet;
    double draw_probability;
    double draw_corrected_probability;
    string decision = "You shouldn't bet this one!";
public:
    Event(Team team1, Team team2, double d_b) : home{team1}, away{team2}, draw_bet{d_b} { draw_probability = 1/draw_bet; correctProbability(); setDecision(); }
    void correctProbability();
    void setDecision();
    friend ostream &operator<<(ostream &, Event);
};

class Matchweek {
private:
    vector<Event> events;
public:
    Matchweek() { openFile(); }
    void printEvents();
    void openFile();
};
#endif // BETS_H
