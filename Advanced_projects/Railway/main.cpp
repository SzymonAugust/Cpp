#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "trains.h"

using namespace std;

int main()
{
    Railway network;
    Interface menu;
    vector<int> choices = {1,2,1,1,5,1,3};
    vector<string> cities_from = {"Gdynia", "Krakow", "Warszawa", "Bialystok"};
    vector<string> cities_to = {"Krakow", "Gdansk", "Bielsko-Biala", "Wroclaw"};
    vector<int> time_h = {5,7,9,13};
    vector<int> time_m = {20,31,50,68};

    menu.activity(network, choices, cities_from, cities_to, time_h, time_m);

    return 0;
}
