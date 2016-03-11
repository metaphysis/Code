#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(unsigned long long x)
{
    if (x <= 1)
        return false;
        
    if (x == 2)
        return true;
    
    if (x % 2 == 0)
        return false;
        
    long long i = 3;
    while (i <= (sqrt(x) + 1))
    {
        if (x % i == 0)
            return false;
        i += 2;
    }
    
    return true;
}

int main(int argc, char *argv[])
{
    long long x;
    
    while (cin >> x, x)
        cout << isPrime(x) << endl;
        
    return 0;
}
