#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

#ifndef TRAINS_H
#define TRAINS_H

struct Data {       //do czytania z pliku
    string n;       //nazwa miasta
    int h;          //czas odjazdu - godziny
    int m;          //czas odjazdu - minuty
};

class Railway {
public:
    class Route {
    public:
        class City {
        public:
            string name;
            int time_h;     //czas odjazdu - tylko godziny
            int time_m;     //czas odjazdu - tylko minuty

            City(int,int,string);
            int TimeToMinutes();
            friend bool operator==(const City&,const City&);
            friend bool operator<(City&,City&);
            friend bool operator>(City&,City&);
        };

        class Connection {
        public:
            int period_of_time;         //czas podróży między dwoma miastami
            string city_from;
            string city_to;

            Connection(City,City);
        };

        string name;
        vector<City> vector_of_cities;
        vector<Connection> vector_of_connections;
        int time_t = 0;  //całkowity czas przejazdu - w minutach
        int hours;      //czas przejazdu - tylko godziny
        int minutes;        //czas przejazdu - tylko minuty

        Route(string);
        friend bool operator==(const Route&,const Route&);
        friend ostream &operator<<(ostream&,Route&);
        void MakeCity(int,int,string);
        void MakeConnection(size_t);
        void TotalTime();
        void TimeToHours();
        bool CityInRoute(string);
    };


    vector<Route> vector_of_routes;


    void MakeRoute(vector<Data>,string);
    friend ostream &operator<<(ostream&,Railway&);
    bool RoutesCrossing(const Route&, const Route&);
    void SearchRoutes(string,string,int,int);
    void Timetable();
    Railway();
};

class Interface {
private:
    int is_used = 0;
public:
    void show ();
    void activity(Railway&,vector<int>,vector<string>&,vector<string>&,vector<int>&,vector<int>&);
};

#endif // TRAINS_H
