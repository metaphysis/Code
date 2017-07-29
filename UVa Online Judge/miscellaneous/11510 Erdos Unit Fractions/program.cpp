// Erdos Unit Fractions
// UVa ID: 11510
// Verdict: Accepted
// Submission Date: 2017-07-29
// UVa Run Time: 0.490s
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

long long solution[10000][3] = {0};
    
void sieve(int *primes, int n, int &countOfPrimes)
{
    countOfPrimes = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
    {
        if (primes[i]) primes[countOfPrimes++] = i;
        for (int j = 0; j < countOfPrimes && i * primes[j] < n; j++)
        {
            primes[i * primes[j]] = 0;
            if (!(i % primes[j])) break;
        }
    }
}

void findFractions(int p)
{
    if (p % 2 == 0)
    {
        solution[p][0] = p / 2;
        solution[p][1] = solution[p][2] = p;
    }
    else if (p % 3 == 2)
    {
        solution[p][0] = (p + 1) / 3;
        solution[p][1] = p;
        solution[p][2] = p * (p + 1) / 3;
    }
    else if (p % 4 == 3)
    {
        solution[p][0] = solution[p][1] = (p + 1) / 2;
        solution[p][2] = p * (p + 1) / 4;
    }
    else
    {
        long long lowX = p / 4 + 1, upX = (p + 1) / 2;
        long long lowY = upX, upY = p * ((5 + sqrt(4 * p - 3)) / 4);
        
        bool found = false;
        for (long long i = lowX; i <= upX && !found; i++)
            for (long long j = lowY; j <= upY; j++)
            {
                long long a = 4 * i * j - p * j - p * i;
                long long mn = p * i * j;
                if (a > 0 && mn % a == 0)
                {
                    solution[p][0] = i, solution[p][1] = j, solution[p][2] = mn / a;
                    found = true;
                    break;
                }
            }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int MAXN = 10000, primes[MAXN], countOfPrimes;

    sieve(primes, MAXN, countOfPrimes);

    for (int i = 0; i < countOfPrimes; i++)
    {
        int p = primes[i];
        findFractions(p);
        for (int j = 2 * p, k = 2; j < 10000; j += p, k++)
            if (!solution[j][0])
                for (int m = 0; m < 3; m++)
                    solution[j][m] = k * solution[p][m];
    }
    
    int n;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i > 0) cout << ' ';
            cout << solution[n][i];
        }
        cout << '\n';
    }

    return 0;
}
