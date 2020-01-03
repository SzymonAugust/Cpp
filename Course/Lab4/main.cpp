#include <iostream>

void swap2ints_pnt (int *p, int *q)
{
    int tmp;

    tmp = *p;
    *p = *q;
    *q = tmp;
}

void swap2ints_ref (int &a, int &b)
{
    int tmp;

    tmp = a;
    a = b;
    b = tmp;
}

int main()
{
    using namespace std;
    int x = 1, y = 2;
    int *px = &x, *py = &y;
    cout << "x = " << x << ", y = " << y << endl; // x = 1, y = 2
    swap2ints_pnt(px, py);
    cout << "x = " << x << ", y = " << y << endl; // x = 2, y = 1
    swap2ints_ref(x, y);
    cout << "x = " << x << ", y = " << y << endl; // x = 1, y = 2

    return 0;
}
