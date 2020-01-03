#include <iostream>
#include <vector>
#include <algorithm>
#include "dhondt_method.h"

int main()
{
    std::vector<Party> list_of_parties;
    int parties_that_took_part, eligible_voters, voters_took_part, max_mandates;
    double voter_turnout, election_threshold;

    std::cout << "Welcome to D'Hondt method calculator!" << std::endl;
    std::cout << "Set number of parties that took part in elections: ";
    std::cin >> parties_that_took_part;
    std::cout << "Set election threshold (in percentage): ";
    std::cin >> election_threshold;
    std::cout << "Set eligible voters: ";
    std::cin >> eligible_voters;
    std::cout << "Set voter turnout (in percentage): ";
    std::cin >> voter_turnout;
    std::cout << "Set maximum number of mandates: ";
    std::cin >> max_mandates;
    std::cout << std::endl;

    voters_took_part = static_cast<int>(voter_turnout*0.01*eligible_voters);

    setListOfParties(list_of_parties,parties_that_took_part);
    modifyListOfParties(list_of_parties,voters_took_part);
    sortListOfParties(list_of_parties);
    D_HondtMethod(list_of_parties,election_threshold,max_mandates);
    getListOfParties(list_of_parties,election_threshold);

    return 0;
}
