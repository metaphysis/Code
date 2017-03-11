#include <iostream>
#include <cmath>

using namespace std;

// 判定给定的整数a是否为素数，如果是则返回true，否则返回false。
bool isPrime(int a)
{
    // 特殊情况判断。
    if (a <= 1) return false;
    
    // 判断是否为唯一的偶素数。
    if (a == 2) return true;
    
    // 不为2的偶数是合数。
    if ((a & 1) == 0) return false;
    
    // 试除法确定是否为素数。
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
