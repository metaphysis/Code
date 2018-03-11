// Another New Function
// UVa ID: 10990
// Verdict: Accepted
// Submission Date: 2018-03-11
// UVa Run Time: 0.800s
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

const int MAXN = 2000001;

int primes[MAXN], phi[MAXN] = {0, 1}, sodf[MAXN] = {0, 1, 1}, cnt = 0;

void sieve()
{
    iota(primes, primes + MAXN, 0);

    for (int i = 2; i < MAXN; i++)
    {
        if (primes[i] == i)
        {
            phi[i] = i - 1;
            primes[cnt++] = i;
            for (int j = i + i; j < MAXN; j += i)
                if (primes[j] == j)
                    primes[j] = i;
        }
        else
        {
            int k = i / primes[i];
            if (k % primes[i] == 0) phi[i] = primes[i] * phi[k];
            else phi[i] = (primes[i] - 1) * phi[k];
        }
    }
}

int getSodf(int n)
{
    if (sodf[n]) return sodf[n];
    return 1 + getSodf(phi[n]);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    sieve();
    for (int i = 1; i < MAXN; i++)
        sodf[i] = getSodf(i);
        
    int cases, m, n;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> m >> n;
        long long sum = 0;
        for (int i = m; i <= n; i++)
            sum += sodf[i];
        cout << sum << '\n';
    }
    
    return 0;
}
