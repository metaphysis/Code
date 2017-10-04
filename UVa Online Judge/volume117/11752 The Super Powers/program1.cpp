// The Super Powers
// UVa ID: 11752
// Verdict: Accepted
// Submission Date: 2017-09-14
// UVa Run Time: 0.010s
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

typedef unsigned long long ull;

void sieve(ull *primes, int n, int &counterOfPrimes)
{
    // 初始时假定所有数为素数，从最小的素数开始筛除。
    counterOfPrimes = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            // 记录筛选得到的素数。
            primes[counterOfPrimes++] = i;

            // 如果i为素数则将其倍数标记为非素数。
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    ull primes[1 << 16];
    int counterOfPrimes = 0;
    
    sieve(primes, 1 << 16, counterOfPrimes);
    
    set<ull> powers;
    powers.insert(1);

    double top = pow(2, 64), start_double;
    ull start_ull, exponent;
    for (ull i = 2; i <= 65536; i++)
    {
        exponent = 1, start_double = i, start_ull = i;
        while (true)
        {
            exponent++, start_double *= i, start_ull *= i;
            if (start_double >= top) break;
            if (binary_search(primes, primes + counterOfPrimes, exponent)) continue;
            if (powers.find(start_ull) != powers.end()) continue;
            powers.insert(start_ull);
        }
    }
    
    for (auto p : powers) cout << p << '\n';

    return 0;
}
