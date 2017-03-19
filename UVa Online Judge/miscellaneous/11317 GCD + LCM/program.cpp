// GCD + LCM
// UVa ID: 11317
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// Euler's totient function
//

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

#define ull unsigned long long

void sieve(int *primes, int n, int &counter)
{
    counter = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++) {
        if (primes[i]) primes[counter++] = i;
        for (int j = 0; j < counter && i * primes[j] < n; j++) {
            primes[i * primes[j]] = 0;
            if (!(i % primes[j])) break;
        }
    }
}

int main(int argc, char *argv[])
{
    const int BASE = 1000000;
    int primes[BASE], counter = 0;

    sieve(primes, BASE, counter);
    
    int cases = 0, n;
    
    while (cin >> n, n > 0)
    {        
        map<int, ull> totalCount;
        for (int i = 2; i <= n; i++)
        {
            map<int, ull> primeCount;
            
            int nn = i;
            while (nn > 1)
            {
                bool divided = false;
                for (int j = 0; j < counter; j++)
                    if (nn % primes[j] == 0)
                    {
                        primeCount[primes[j]]++;
                        nn /= primes[j];
                        divided = true;
                        break;
                    }
                if (!divided)
                {
                    primeCount[n]++;
                    break;
                }
            }
            
            ull product = 1;
            for (auto p : primeCount)
                product *= (p.second + 1);
            for (auto p : primeCount)
                totalCount[p.first] += product * p.second / 2;
        }
    }
    
    return 0;
}
