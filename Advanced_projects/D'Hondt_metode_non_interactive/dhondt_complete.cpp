#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "dhondt_complete.h"

#define ALL_VOTERS 18470710

void Party::print()
{
    std::cout << m_name << " (" << m_ID << ")" << std::endl;
    std::cout << "Type: " << m_type << std::endl;
    std::cout << "Votes: " << m_votes << std::endl;
    std::cout << "Election threshold required: " << m_threshold_required << std::endl;
    std::cout << "Election score: " << std::printf("%.2lf",m_score) << std::endl;
    std::cout << "Mandates: " << m_mandates << std::endl;
}

void Party::setScore()
{
    this->m_score = static_cast<double>(this->m_votes)/ALL_VOTERS*100;
}

Party::Party(std::string s1,std::string s2,std::string s3)
{
    this->m_ID = s1;
    this->m_name = s2;
    this->m_type = s3;

    if (this->m_type == "minority")
        this->m_threshold_required = 0;
    else if (this->m_type == "coalition")
        this->m_threshold_required = 8;
    else
        this->m_threshold_required = 5;
}

void Constituency::print()
{
    std::cout << "Constituency no. " << m_ID << " [" << m_name << "]" << std::endl;
    std::cout << "Mandates: " << m_mandates << std::endl;

    for (auto party : this->m_parties)
    {
        std::cout << party.getID() << std::endl;
        std::cout << "Voters: " << party.getVotes() << std::endl;
        std::cout << "Mandates: " << party.getMandates() << std::endl;
    }
}

Constituency::Constituency(int i1, int i2, std::string s, std::vector<Party> &vp)
{
    this->m_ID = i1;
    this->m_mandates = i2;
    this->m_name = s;

    for (auto p : vp)
    {
        Party party(p.getID(),p.getName(),p.getType());

        party.addVotes(p.getVotes());

        this->m_parties.push_back(p);
    }

    sortParties(this->m_parties);
}

void sortParties(std::vector<Party> &parties)
{
    std::sort(parties.begin(), parties.end(), [](Party party_1, Party party_2){ return party_1.getVotes() > party_2.getVotes(); });
}

void openPartyFile(std::vector<Party> &parties)
{
    std::ifstream data("party_list.txt");

    if (!data.good())
        exit(0);

    std::string input_string;
    std::vector<std::string> input;

    while (getline(data,input_string))
        input.push_back(input_string);
    data.close();

    for (auto x : input)
    {
        std::string s;
        std::vector<std::string> vs;
        std::stringstream stream(x);

        while(getline(stream,s,';'))
            vs.push_back(s);

        Party p(vs[0],vs[1],vs[2]);

        parties.push_back(p);
    }
}

void openConstituencyFile(std::vector<Constituency> &constituencies)
{
    std::ifstream data("constituency_list.txt");

    if (!data.good())
         exit(0);

    std::string input_string;
    std::vector<std::string> input;

    while (getline(data,input_string))
         input.push_back(input_string);
    data.close();

    for (auto x : input)
    {
        int mandates = 0;
        int ID = 0;
        int i = 0;
        std::string name;
        std::string s;
        std::vector<std::string> vs;
        std::vector<std::string>::iterator iter;
        std::vector<Party> vp;
        std::stringstream stream(x);

        while(getline(stream,s,';'))
        {
            if (i == 0)
                ID = atoi(s.c_str());
            else if (i == 1)
                name = s;
            else if (i == 2)
                mandates = atoi(s.c_str());
            else
               vs.push_back(s);
            i++;
        }

        for (iter = vs.begin(); iter != vs.end(); iter += 2)
        {
            Party p(*iter,"","");
            p.addVotes(atoi((*(iter+1)).c_str()));
            vp.push_back(p);
        }

        Constituency c(ID,mandates,name,vp);

        constituencies.push_back(c);
    }
}

void useDHondtMethod(std::vector<Party> &parties, std::vector<Constituency> &constituencies)
{
    for (auto &constituency : constituencies)
    {
        std::vector<Party> tmp_parties;
        std::vector<Party>::iterator tmp_iter_1;
        std::vector<Party>::iterator tmp_iter_2;

        for (auto party : constituency.m_parties)
            tmp_parties.push_back(party);

        for (int i = 0; i < constituency.m_mandates; i++)
        {
            sortParties(tmp_parties);
            tmp_iter_1 = std::find_if(constituency.m_parties.begin(),constituency.m_parties.end(),[tmp_parties](const Party &party)->bool{ return party.m_ID == tmp_parties[0].m_ID; });
            tmp_iter_2 = std::find_if(parties.begin(),parties.end(),[tmp_iter_1](const Party party){ return party.m_ID == tmp_iter_1->m_ID; });
            if (tmp_iter_2->m_score < tmp_iter_2->m_threshold_required)
            {
                i--;
                tmp_parties.erase(tmp_parties.begin());
                continue;
            }
            tmp_iter_1->addMandates(1);
            tmp_parties[0].m_votes = static_cast<int>(tmp_iter_1->m_votes/(tmp_iter_1->m_mandates+1));
        }
    }
}

void sumPartiesPerConstituenciesWithCondition(std::vector<Party> &parties, std::vector<Constituency> &constituencies, std::string condition)
{
    for (auto &constituency : constituencies)
    {
        for (auto &party : constituency.m_parties)
        {
            std::vector<Party>::iterator iter;

            iter = std::find_if(parties.begin(),parties.end(),[party](const Party party_1){ return party.m_ID == party_1.m_ID; });
            if (condition == "mandates")
                iter->addMandates(party.getMandates());
            else if (condition == "votes")
                iter->addVotes(party.getVotes());
        }
    }

    if (condition == "votes")
    {
        for (auto &party : parties)
            party.setScore();

        sortParties(parties);
    }
}

void printListOfParties(std::vector<Party> &parties)
{
    for (auto party : parties)
    {
        party.print();
        std::cout << std::endl;
    }
}

void printListOfConstituencies(std::vector<Constituency> &constituencies)
{
    for (auto constituency : constituencies)
    {
        constituency.print();
        std::cout << std::endl;
    }
}
