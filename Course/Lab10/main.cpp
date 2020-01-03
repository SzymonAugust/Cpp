#include <iostream>

using namespace std;

double divide (double x, double y)
{
    if (y == 0)
        throw y;
    return x/y;
}

int main()
{
    double c1 = 3;
    double c2 = 0;

    try {
        divide(c1,c2);
    }

    catch (double y)
    {
        cout << "Error! Dividing by " << y << "!" << endl;
    }

    return 0;
}
