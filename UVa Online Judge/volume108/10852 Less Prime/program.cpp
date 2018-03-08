// Less Prime
// UVa ID: 10852
// Verdict: Accepted
// Submission Date: 2018-03-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[10010] = {0}, cnt = 0;
    for (int i = 2; i < 10010; i++)
        if (isPrime(i))
            primes[i] = 1;
    for (int i = 2; i < 10010; i++)
        if (primes[i])
            primes[cnt++] = i;

    int cases, n;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        int remainder = 0, x;
        for (int i = 0; i < cnt; i++)
            if (primes[i] <= n)
            {
                int mod = n % primes[i];
                if (mod > remainder)
                {
                    remainder = mod;
                    x = primes[i];
                }
            }
            else break;
        cout << x << '\n';
    }

    return 0;
}
