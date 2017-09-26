#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int a)
{
    if (a <= 1) return false;
    if (a == 2) return true;
    if ((a & 1) == 0) return false;

    int high = (int)sqrt(a);
    for (int i = 3; i <= high; i += 2)
        if (a % i == 0)
            return false;

    return true;
}

int main(int argc, char *argv[])
{
    int a;
    
    while (cin >> a)
        cout << a << (isPrime(a) ? " is prime number.\n" : " is not prime number.\n");
        
    return 0;
}
