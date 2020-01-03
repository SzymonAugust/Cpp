#include <iostream>
#include <vector>
#include <algorithm>

#ifndef DHONDT_METHOD_H
#define DHONDT_METHOD_H

class Party {
public:
    std::string m_name;
    double m_score = 0;
    int m_mandates = 0;
    int m_voters;
};

void setListOfParties(std::vector<Party>&,int);
void getListOfParties(std::vector<Party>&,double);
void modifyListOfParties(std::vector<Party>&,int);
void sortListOfParties(std::vector<Party>&);
void D_HondtMethod(std::vector<Party>&,double,int);

#endif // DHONDT_METHOD_H
