#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

/*
class Rectangle {
public:
    void draw()
    {
        cout << "Rectangle::draw" << endl;
    }
};

class Triangle {
public:
    void draw()
    {
        cout << "Triangle::draw" << endl;
    }
};

class A {
public:
    int draw()
    {
        return 0;
    }
};

template <typename T>
class Shape {
private:
    T m_draw;
public:
    void draw()
    {
        m_draw.draw();
    }
};
*/

class LessThan {
public:
    LessThan(int i) : m_state{i} {}
    bool operator() (int x)
    {
        return x < m_state;
    }
private:
    const int m_state;
};

int main()
{
    vector<int> v,v1;

    for (int i = 0; i < 10; i++)
        v.push_back(i);

    for (size_t i = 0; i < v.size(); i++)
        if (find_if(v.begin()+i,v.end(),LessThan(4)) == v.end())
            v1.push_back(v[i]);

    for (auto x : v1)
        cout << x << endl;

    /*
    int x = 3;

    LessThan less_than_3(x);
    for (int i = 0; i < 10; i++)
        if (less_than_3(i))
            cout << i << " < " << x << endl;
        else
            cout << i << " >= " << x << endl;

    x = 7;
    cout << endl;

    LessThan less_than_7(x);
    for (int i = 0; i < 10; i++)
        if (less_than_7(i))
            cout << i << " < " << x << endl;
        else
            cout << i << " >= " << x << endl;

    Shape<Triangle> shape1;
    Shape<Rectangle> shape2;
    Shape<A> shape3;

    shape1.draw();
    shape2.draw();
    shape3.draw();
    */

    return 0;
}
