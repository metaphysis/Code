// Erdos Unit Fractions
// UVa ID: 11510
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

long long gcd(long long a, long long b)
{
    if (a < b) swap(a, b);
    return b ? gcd(b, a % b) : a;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    long long n;
    while (cin >> n, n > 0)
    {
        long long g = gcd(4, n);
        long long numerator = 4 / g, denominator = n / g;
        
        if (numerator == 1)
        {
            denominator *= 3;
            cout << denominator << ' ' << denominator << ' ' << denominator << '\n';
            continue;
        }
        
        if (numerator == 2)
        {
            cout << denominator;
            denominator *= 2;
            cout << denominator << ' ' << denominator << '\n';
            continue;
        }
        
        cout << denominator;
        numerator -= 1;
        
        g = gcd(numerator, denominator);
        numerator /= g, denominator /= g;
        
        if (numerator == 1)
        {
            denominator *= 2;
            denominator *= 2;
            cout << denominator << ' ' << denominator << '\n';
            continue;
        }
    }
    
    return 0;
}
