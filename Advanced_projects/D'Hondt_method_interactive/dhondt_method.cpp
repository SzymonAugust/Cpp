#include <iostream>
#include <vector>
#include <algorithm>
#include "dhondt_method.h"

void setListOfParties(std::vector<Party> &list, int number_of_parties)
{
    for (int i = 0; i < number_of_parties; i++)
    {
        Party party;

        std::cout << "Party no. " << i+1 << std::endl;
        std::cout << "Set party's name: ";
        std::cin >> party.m_name;
        std::cout << "Set party's score (in percentage): ";
        std::cin >> party.m_score;

        list.push_back(party);
    }

    std::cout << std::endl << std::endl;
}

void getListOfParties(std::vector<Party> &list, double limit)
{
    for (auto party : list)
    {
        std::cout << party.m_name << std::endl;
        std::cout << "Party's score: " << party.m_score << std::endl;
        std::cout << "In parliament: ";

        if (party.m_score >= limit)
        {
            std::cout << "Yes" << std::endl;
            std::cout << "Number of mandates: " << party.m_mandates << std::endl;
        }

        else
            std::cout << "No" << std::endl;

        std::cout << "Voters: " << party.m_voters << std::endl;
    }
}

void modifyListOfParties(std::vector<Party> &list, int voting_people)
{
    for (auto &party : list)
    {
        party.m_voters = static_cast<int>(voting_people*party.m_score*0.01);
    }
}

void sortListOfParties(std::vector<Party> &list)
{
    std::sort(list.begin(),list.end(),[](Party party_1, Party party_2){return party_1.m_voters > party_2.m_voters;});
}

void D_HondtMethod(std::vector<Party> &list, double limit, int limit_2)
{
    std::vector<Party> successful_parties;
    std::vector<Party>::iterator it;

    for (auto party : list)
        if (party.m_score >= limit)
            successful_parties.push_back(party);

    for (int i = 0; i < limit_2; i++)
    {
        sortListOfParties(successful_parties);
        it = std::find_if(list.begin(),list.end(),[successful_parties](const Party &party)->bool{return party.m_name == successful_parties[0].m_name;});
        it->m_mandates += 1;
        successful_parties[0].m_voters = static_cast<int>(it->m_voters/(it->m_mandates+1));
    }
}
