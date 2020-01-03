#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "dhondt_complete.h"

int main()
{
    std::vector<Party> parties;
    std::vector<Constituency> constituencies;

    openPartyFile(parties);
    openConstituencyFile(constituencies);

    sumPartiesPerConstituenciesWithCondition(parties,constituencies,"votes");
    useDHondtMethod(parties,constituencies);
    sumPartiesPerConstituenciesWithCondition(parties,constituencies,"mandates");

    printListOfParties(parties);
    printListOfConstituencies(constituencies);

    return 0;
}
