// Colin and Ryan
// UVa ID: 10880
// Verdict: Accepted
// Submission Date: 2018-01-12
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

const int MAXN = 50000;
int primes[MAXN], cnt;
    
void sieve(int *primes, int n, int &cnt)
{
    cnt = 0, memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

vector<int> findDivisor(int n)
{
    map<int, int> factors;
    for (int i = 0; i < cnt && n > 1; i++)
    {
        while (n % primes[i] == 0)
        {
            n /= primes[i];
            factors[primes[i]]++;
        }
    }
    if (n > 1) factors[n]++;

    vector<int> divisors = {1};
    for (auto f : factors)
    {
        int base = 1, countOfDivisors = divisors.size();
        for (int i = 1; i <= f.second; i++)
        {
            base *= f.first;
            for (int j = 0; j < countOfDivisors; j++)
                divisors.push_back(divisors[j] * base);
        }
    }

    sort(divisors.begin(), divisors.end());
    
    return divisors;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    sieve(primes, MAXN, cnt);
    
    int cases, R, C;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case #" << c << ":";
        cin >> C >> R;
        if (C == R)
        {
            cout << " 0\n";
            continue;
        }

        vector<int> divisors = findDivisor(C - R);
        for (auto d : divisors)
            if (d > R)
                cout << ' ' << d;
        cout << '\n';
    }

    return 0;
}
