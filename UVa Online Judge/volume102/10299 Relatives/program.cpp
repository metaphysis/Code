// Relatives
// UVa ID: 10299
// Verdict: Accepted
// Submission Date: 2018-03-10
// UVa Run Time: 0.300s
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

const int MAXN = 32000;

int primes[MAXN], cnt = 0;

void sieve(int *primes, int n, int &cnt)
{
    // 初始时假定所有数为素数，从最小的素数开始筛除。
    cnt = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            // 记录筛选得到的素数。
            primes[cnt++] = i;

            // 如果i为素数则将其倍数标记为非素数。
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

int getPhi(int m)
{
    int phi = m;
    for (int i = 0; i < cnt; i++) {
        if (primes[i] > m) break;
        if (m % primes[i] == 0)
        {
            while (m % primes[i] == 0) m /= primes[i];
            phi -= phi / primes[i];
        }
    }
    if (m > 1) phi -= phi / m;
    return phi;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    sieve(primes, MAXN, cnt);

    int n;
    while (cin >> n, n > 0)
    {
        if (n == 1) cout << "0\n";
        else cout << getPhi(n) << '\n';
    }

    return 0;
}
