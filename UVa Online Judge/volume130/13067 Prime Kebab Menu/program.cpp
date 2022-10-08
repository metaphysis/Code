// Prime Kebab Menu
// UVa ID: 13067
// Verdict: Accepted
// Submission Date: 2022-10-08
// UVa Run Time: 0.910s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000010;

int primes[MAXN], cnt;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }

    long long n;
    while (cin >> n, n > 1)
    {
        int c = 0;
        for (int i = 0; i < cnt && primes[i] <= n; i++)
            while (n % primes[i] == 0) { n /= primes[i]; c++; }
        if (n > 1) c++;
        cout << c << '\n';
    }

    return 0;
}
