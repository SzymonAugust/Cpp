#include <iostream>
#include "add.h"

int main()
{
    using std::cout;
    using std::endl;

    int x = 2, y = 3;

    cout << "add(" << x << "," << y << ") = " << add(x,y) << endl;
    cout << "SQR(" << x+y << ") = " << SQR(x+y) << endl;

    return 0;
}
