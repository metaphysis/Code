// Gauss Prime
// UVa ID: 1415
// Verdict: Accepted
// Submission Date: 2019-04-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20010;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[MAXN] = {}, cnt = 0;
    for (int i = 2; i < MAXN; i++)
    {
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }
    int cases, a, b, N;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> a >> b;
        if (a == 0) cout << "No\n";
        else
        {
            N = a * a + 2 * b * b;
            bool flag = true;
            for (int i = 0; i < cnt && primes[i] * primes[i] <= N; i++)
                if (N % primes[i] == 0)
                {
                    flag = false;
                    break;
                }
            cout << (flag ? "Yes" : "No") << '\n';
        }
    }

    return 0;
}
