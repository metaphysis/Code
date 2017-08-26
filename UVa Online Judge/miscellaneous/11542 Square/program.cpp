// Square
// UVa ID: 11542
// Verdict: Accepted
// Submission Date: 2017-08-26
// UVa Run Time: 0.020s
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

const int MAXN = 110;

int n, m;

void sieve(int *primes, int n, int &counterOfPrimes)
{
    counterOfPrimes = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            primes[counterOfPrimes++] = i;
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

int gaussianElimination(vector<vector<int>> &A)
{
    int i = 0, j = 0;

    while (i < m && j < n)
    {
        int pivot = i;
        for (int k = i; k < m; k++)
            if (A[k][j])
            {
                pivot = k;
                break;
            }

        if (A[pivot][j])
        {
            if (pivot != i) swap(A[i], A[pivot]);
            for (int u = i + 1; u < m; u++)
                if (A[u][j])
                    for (int k = i; k <= n; k++)
                        A[u][k] ^= A[i][k];
            i++;
        }
        j++;
    }

    return i;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[510], counterOfPrimes;
    
    sieve(primes, 510, counterOfPrimes);
    
    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        m = -1;
        vector<vector<int>> A(MAXN, vector<int>(MAXN, 0));

        for (int i = 0; i < n; i++)
        {
            long long x;
            cin >> x;
            for (int j = 0; j < counterOfPrimes; j++)
                while (x % primes[j] == 0)
                {
                    m = max(m, j);
                    A[j][i]++;
                    A[j][i] %= 2;
                    x /= primes[j];
                }
        }

        m++;
        int fixed = gaussianElimination(A);

        cout << (1LL << (n - fixed)) - 1 << '\n';
    }
    
    return 0;
}
