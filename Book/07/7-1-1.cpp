#include <iostream>
#include <cmath>

using namespace std;

// 判定给定的整数p是否为素数，如果是则返回true，否则返回false。
bool is_prime(int p)
{
    // 特殊情况判断。
    if (p <= 1) return false;
    
    // 判断是否为唯一的偶素数。
    if (p == 2) return true;
    
    // 不为2的偶数是合数。
    if (p & 1 == 0) return false;
    
    // 试除法确定是否为素数。
    int high_limit = sqrt(p) + 1;
    for (int i = 3; i <= high_limit; i += 2)
        if (p % i == 0)
            return false;
 
    return true;
}

int main(int argc, char *argv[])
{
    int p;
    
    while (cin >> p)
        cout << p << (is_prime(p) ? " is prime number.\n" : " is not prime number.\n");
        
    return 0;
}
