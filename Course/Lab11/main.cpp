#include <iostream>

using namespace std;

template<typename T1, typename T2>
class MyPair;

template<typename T1, typename T2>
ostream &operator<<(ostream & os,const MyPair<T1,T2> &pair);

template<typename T1, typename T2>
class MyPair {
private:
    T1 m_first;
    T2 m_second;
public:
    MyPair(T1,T2);
    T1 first() const;
    T2 second() const;
    friend ostream &operator<< <T1,T2>(ostream & os,const MyPair<T1,T2> &pair);
};

template<typename T1, typename T2>
ostream &operator<< (ostream & os,const MyPair<T1,T2> &pair)
{
    os << pair.first() << " " << pair.second();

    return os;
}

template<typename T1, typename T2>
MyPair<T1,T2>::MyPair(T1 f, T2 s)
{
    m_first = f;
    m_second = s;
}

template<typename T1, typename T2>
T1 MyPair<T1,T2>::first() const
{
    return m_first;
}

template<typename T1, typename T2>
T2 MyPair<T1,T2>::second() const
{
    return m_second;
}

int main()
{
    MyPair<int,int> number(-3,1);
    MyPair<string,int> avenue("Hollywood",45);
    MyPair<string,string> writer("Thomas","Cormen");

    cout << number << endl;
    cout << avenue << endl;
    cout << writer << endl;

    return 0;
}
