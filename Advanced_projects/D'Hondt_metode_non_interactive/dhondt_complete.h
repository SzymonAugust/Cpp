#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#ifndef DHONDT_COMPLETE_H

class Party;
class Constituency;
void sortParties(std::vector<Party>&);

class Party {
private:
    std::string m_ID;
    std::string m_name;
    std::string m_type;
    double m_threshold_required;
    int m_votes = 0;
    int m_mandates = 0;
    double m_score;

    void print();
    void setScore();

    friend void openPartyFile(std::vector<Party>&);
    friend void printListOfParties(std::vector<Party>&);
    friend void openConstituencyFile(std::vector<Constituency>&);
    friend void useDHondtMethod(std::vector<Party>&,std::vector<Constituency>&);
    friend void sumPartiesPerConstituenciesWithCondition(std::vector<Party>&,std::vector<Constituency>&,std::string);
public:
    Party(std::string,std::string,std::string);

    std::string getID() { return m_ID; }
    std::string getName() { return m_name; }
    std::string getType() { return m_type; }
    int getVotes() { return m_votes; }
    int getMandates() { return m_mandates; }
    void addVotes(int i) { this->m_votes += i; }
    void addMandates(int i) { this->m_mandates += i; }
};

class Constituency {
private:
    int m_ID;
    int m_mandates;
    std::string m_name;
    std::vector<Party> m_parties;

    void print();

    friend void openConstituencyFile(std::vector<Constituency>&);
    friend void printListOfConstituencies(std::vector<Constituency>&);
    friend void useDHondtMethod(std::vector<Party>&,std::vector<Constituency>&);
    friend void sortParties(std::vector<Party>&);
    friend void sumPartiesPerConstituenciesWithCondition(std::vector<Party>&,std::vector<Constituency>&,std::string);

    Constituency(int,int,std::string,std::vector<Party>&);
};
#define DHONDT_COMPLETE_H

#endif // DHONDT_COMPLETE_H
