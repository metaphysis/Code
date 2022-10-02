// DPA Number II
// UVa ID: 13194
// Verdict: Accepted
// Submission Date: 2022-10-02
// UVa Run Time: 0.280s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

int primes[MAXN];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cnt = 0;
    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }

    int cases;
    cin >> cases;
    while (cases--)
    {
        long long n;
        cin >> n;
        long long sum = 1, nn = 2 * n;
        for (int i = 0; i < cnt && primes[i] * primes[i] <= n; i++)
        {
            if (n % primes[i]) continue;
            long long p = primes[i];
            while (n % primes[i] == 0)
            {
                n /= primes[i];
                p *= primes[i];
            }
            sum *= (p - 1) / (primes[i] - 1);
            if (sum > nn) break;
        }
        if (n > 1) sum *= 1 + n;
        if (sum < nn) cout << "deficient";
        else if (sum == nn) cout << "perfect";
        else cout << "abundant";
        cout << '\n';
    }

    return 0;
}
