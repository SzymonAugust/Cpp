#include <iostream>
#include <vector>

uint32_t fib(uint32_t n)
{
    return (n == 0 or n == 1) ? n:(fib(n-2)+fib(n-1));
}

uint32_t f(uint32_t n)
{
    return n/2;
}

int main()
{
    using namespace std;
    int n;

    for (n = 20; n < 100; n++)
        cout << "fib[" << n << "] = " << fib(n) << endl;
}
