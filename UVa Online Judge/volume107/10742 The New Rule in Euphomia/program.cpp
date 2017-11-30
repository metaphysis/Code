// The New Rule in Euphomia
// UVa ID: 10742
// Verdict: Accepted
// Submission Date: 2017-11-30
// UVa Run Time: 0.030s
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

const int MAXN = 1000010;

void sieve(int *primes, int n, int &cnt)
{
    cnt = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[MAXN], cnt;
    sieve(primes, MAXN, cnt);
    
    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ": ";
        
        int C = 0;
        int i = upper_bound(primes, primes + cnt, n / 2) - primes;
        C += i * (i - 1) / 2;

        for (int j = i; j < cnt; j++)
        {
            if (primes[j] >= n) break;
            int k = upper_bound(primes, primes + cnt, (n - primes[j])) - primes;
            C += k;
        }
        
        cout << C << '\n';
    }

    return 0;
}
