// Reaching the Fix-Point
// UVa ID: 11226
// Verdict: Accepted
// Submission Date: 2018-03-11
// UVa Run Time: 0.190s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int length[500010] = {0};
int primes[710] = {0}, cnt = 0;

void getPrimes()
{
    for (int i = 2; i * i < 710; i++)
        if (!primes[i])
            for (int j = i * i; j < 710; j += i)
                primes[j] = 1;
    for (int i = 2; i < 710; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            length[i] = 1;
        }
}

int sopf(int n)
{
    if (length[n]) return length[n];
    else
    {
        int sum = 0, x = n;
        for (int i = 0; i < cnt && x > 1; i++)
        {
            while (x % primes[i] == 0)
            {
                sum += primes[i];
                x /= primes[i];
            }
        }
        if (x > 1) sum += x;
        if (sum == n) length[n] = 1;
        else length[n] = 1 + sopf(sum);
        return length[n];
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    getPrimes();
    
    for (int i = 2; i <= 500000; i++)
        if (!length[i])
            length[i] = sopf(i);
    
    int cases, n, m;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        if (n > m) swap(n, m);
        int maxLength = 0;
        for (int i = n; i <= m; i++)
            maxLength = max(maxLength, length[i]);
        cout << "Case #" << c << ":\n";
        cout << maxLength << '\n';
    }

    return 0;
}
