#include <iostream>

using namespace std;

class C {
private:
    double x_;
public:
    C (double x = 0) : x_{x}
    {
        cout << "constructor..." << endl;
    }

    C(const C &other) : x_{other.x_}
    {
        cout << "copy constructor..." << endl;
    }
};

int main()
{
   //sterta (pamięć alokowana) C *p1 = new C(1)       |stos    C c1(1.5)
    C c1(1.5);
    C c2(c1);
    C c3 = c1;
    C c4 = 1.5;

    return 0;
}
