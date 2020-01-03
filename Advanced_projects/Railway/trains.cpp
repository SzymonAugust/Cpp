#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "trains.h"

#define HOUR 60
#define DAY 24

Railway::Railway()
{
    Timetable();
}

Railway::Route::City::City(int x, int y, string n)
{
    time_h = x;
    time_m = y;
    name = n;
}

Railway::Route::Connection::Connection(City c1, City c2)
{
    if (c2.TimeToMinutes() > c1.TimeToMinutes())
    {
        period_of_time = c2.TimeToMinutes() - c1.TimeToMinutes();
        city_from = c1.name;
        city_to = c2.name;
    }
    else if (c1.TimeToMinutes() > c2.TimeToMinutes() and (c2.time_h - c1.time_h) < 0)
    {
        period_of_time = DAY * HOUR + c2.time_m - c1.TimeToMinutes();
        city_from = c1.name;
        city_to = c2.name;
    }
}

Railway::Route::Route(string n)
{
    name = n;
}

ostream &operator<<(ostream &os,Railway::Route &route)
{
    os << route.name << ": ";

    for (auto x: route.vector_of_cities)
    {
        os << x.name << " " << x.time_h << ":";
        if (x.time_m < 10)
           cout << "0" << x.time_m << " ";
        else
            cout << x.time_m << " ";
    }

    os << endl << "Route " << route.name << " takes " << route.hours << " hours, " << route.minutes << " minutes." << endl;

    return os;
}

int Railway::Route::City::TimeToMinutes()
{
    return this->time_h * HOUR + this->time_m;
}

void Railway::Route::TimeToHours()
{
    this->hours = static_cast<int>(this->time_t/HOUR);
    this->minutes = time_t - this->hours * HOUR;
}

void Railway::Route::MakeCity(int hour, int minute, string name)
{
    this->vector_of_cities.push_back(Railway::Route::City(hour,minute,name));
}

void Railway::Route::MakeConnection(size_t number)
{
    this->vector_of_connections.push_back(Railway::Route::Connection(this->vector_of_cities[number],this->vector_of_cities[number+1]));
}

void Railway::Route::TotalTime()
{
    for (auto x: this->vector_of_connections)
        this->time_t += x.period_of_time;
}

void Railway::MakeRoute(vector<Data> data, string s)
{
    Route route(s);
    size_t i;

    for (auto x : data)
        route.MakeCity(x.h,x.m,x.n);

    for (i = 0; i < data.size()-1; i++)
        route.MakeConnection(i);

    route.TotalTime();
    route.TimeToHours();

    this->vector_of_routes.push_back(route);
}

bool operator==(const Railway::Route &route1,const Railway::Route &route2) //sprawdzenie, czy trasy się przecinają
{
    for (auto x : route1.vector_of_cities)
        for (auto y : route2.vector_of_cities)
            if (x == y)
                return 1;
    return 0;
}

bool operator<(Railway::Route::City &city1, Railway::Route::City &city2)
{
    if (city1.TimeToMinutes() < city2.TimeToMinutes())
        return 1;
    return 0;
}

bool operator>(Railway::Route::City &city1, Railway::Route::City &city2)
{
    if (city1.TimeToMinutes() > city2.TimeToMinutes())
        return 1;
    return 0;
}

bool operator==(const Railway::Route::City &city1, const Railway::Route::City &city2) //sprawdzenie, czy nazwy miast są te same
{
    if (city1.name == city2.name)
        return 1;
    return 0;
}

ostream &operator<<(ostream &os, Railway &railway)
{
    os << "***** ALL ROUTES IN TIMETABLE *****" << endl << endl;
    for (auto x : railway.vector_of_routes)
        os << x << endl;
    return os;
}

bool Railway::RoutesCrossing(const Railway::Route& city1, const Railway::Route& city2)
{
    if (city1 == city2)
        return 1;
    return 0;
}

void Railway::SearchRoutes(string from_where, string to_where, int hour, int minute)
{
    vector<Railway::Route> tmp_routes;
    int time = HOUR * hour + minute;

    for (auto x: this->vector_of_routes)
        if (x.CityInRoute(from_where) and x.CityInRoute(to_where))              //szukanie trasy z oboma miastami
            for (size_t y = 0; y < x.vector_of_cities.size(); y++)
                if (x.vector_of_cities[y].name.find(from_where) != string::npos and x.vector_of_cities[y].TimeToMinutes() > time)   //znajdowanie miasta, z którego wyjeżdża pociąg po zadanej godzinie
                    for (size_t z = y+1; z < x.vector_of_cities.size(); z++)
                        if  (x.vector_of_cities[z].name.find(to_where) != string::npos) //znajdowanie miasta docelowego
                        {
                            tmp_routes.push_back(x);
                            break;
                        }
    if (tmp_routes.size())
    {
        cout << "***** ROUTES FOUND *****" << endl << endl;
        for (auto x : tmp_routes)
            cout << x << endl;
    }
    else
        cout << "***** NO ROUTE FOUND *****" << endl << endl;
}

bool Railway::Route::CityInRoute(string city)
{
    return any_of(this->vector_of_cities.begin(), this->vector_of_cities.end(), [city](const City & tmp)->bool { return !tmp.name.find(city); });                     //lambda & algorithm
}       //lambda & algorithm

void Railway::Timetable()
{
    ifstream schedule("routes.txt");

    if (!schedule.good())
    {
        exit(1);
    }

    string input_string;
    vector<string> trains;

    while (getline(schedule, input_string))
        trains.push_back(input_string);
    schedule.close();

    for (auto train : trains)
    {
        Data d;
        vector<Data> vd;
        string tmp;
        vector<string> unit;
        stringstream stream(train);

        while (getline(stream, tmp, ';'))
            unit.push_back(tmp);

        string train_name = unit[1] + ' ' + unit[0];
        unit.erase(unit.begin(), unit.begin()+2);
        int c = 0;

        for (auto it : unit)
        {
            switch(c)
            {
            case 0:{
                d.n = it; break;}
            case 1:{
                string x = it;
                d.h = atoi(x.c_str()); break;}
            case 2:{
                string x = it;
                d.m = atoi(x.c_str()); break;}
            }
            c +=1;

            if (!(c = c%3))
                vd.push_back(d);
        }
        this->MakeRoute(vd, train_name);
    }
}

void Interface::show ()
{
    cout << "*************************" << endl;
    if (!is_used)
        cout << "*        Welcome!       *" << endl;
    cout << "*1.    Search routes    *" << endl;
    cout << "*2.   Show all routes   *" << endl;
    cout << "*3.        Exit         *" << endl;
    cout << "*************************" << endl;

    this->is_used++;
}

void Interface::activity (Railway &railway, vector<int> choice, vector<string> &city1, vector<string> &city2,vector<int> &h, vector<int> &m)
{
    size_t i = 0, j = 0;
    while (true)
    {
        this->show();
        cout << "Option chosen: " << choice[i] << "." << endl;
        if (choice[i] == 1 or choice[i] == 2 or choice[i] == 3)
            switch (choice[i])
            {
                case 1:
                    cout << "Give the names of cities:" << endl;
                    cout << "From: " << city1[j] << endl;
                    cout << "To: " << city2[j] << endl;
                    cout << "And time to start journey in HH:MM format:" << endl;
                    cout << "Hour (HH): " << h[j] << endl;
                    cout << "Minutes (MM): " << m[j] << endl;
                    if (h[j] < 0 or h[j] > 23 or m[j] <0 or m[j] > 59)
                    {
                        cout << "***** INCORRECT TIME *****" << endl;
                        break;
                    }
                    railway.SearchRoutes(city1[j], city2[j],h[j],m[j]);
                    j++;
                    break;
                case 2:
                    cout << railway << endl;
                    break;
                case 3:
                    cout << "***** GOOD BYE! *****" << endl;
                    goto fin;
            }
        else
        {
            cout << "***** INCORRECT OPTION, PLEASE TRY AGAIN *****" << endl;
        }
    i++;
    }

    fin : ;
}
