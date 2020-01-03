#include <iostream>

using namespace std;

int main()
{
    float a = 0.1, b = 0.2, c = 0.3;
    float z = (a+b)+c;
    float x = a+(b+c);

    if (z == x)
        printf("x and z are equal\n");
    else
        printf("x and z aren't equal\n");

    return 0;
}
