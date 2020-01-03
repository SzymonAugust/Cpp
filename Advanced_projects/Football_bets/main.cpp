#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include "bets.h"

using namespace std;

int main()
{
    Matchweek m;
    setlocale(LC_ALL,"pl_PL");

    m.printEvents();

    return 0;
}
