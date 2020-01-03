#include <iostream>

using namespace std;

class Base {
public:
    void public_fun1();
private:
    void private_fun1();
protected:
    void protected_fun1();
};

class Derived : private Base {
public:
    void public_fun2();
    void public_fun1()
    {
        Base::public_fun1();
        cout << "Derived::public_fun1" << endl;
    }
};

class Derived2 : public Derived {
};

void Base::public_fun1()
{
    cout << "Base::public_fun1" << endl;
}

void Base::private_fun1()
{
    cout << "Base::private_fun1" << endl;
}

void Base::protected_fun1()
{
    cout << "Base::protected_fun1" << endl;
}

void Derived::public_fun2()
{
    cout << "Derived::public_fun2" << endl;
    protected_fun1();
}

int main()
{
    Base b1;
    Derived d1;
    Derived2 dd1;

    //b1.public_fun1();
    //b1.private_fun1();
    //b1.protected_fun1();

    d1.public_fun2();
    d1.public_fun1();

    //dd1.public_fun2();

    return 0;
}
