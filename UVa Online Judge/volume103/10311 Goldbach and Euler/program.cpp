// Goldbach and Euler
// UVa ID: 10311
// Verdict: Accepted
// Submission Date: 2018-03-08
// UVa Run Time: 1.080s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000010;

bool visited[MAXN] = {0};
int primes[6000000], cnt = 0;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i * i < MAXN; i++)
        if (!visited[i])
            for (int j = i * i; j < MAXN; j += i)
                visited[j] = true;
    for (int i = 2; i < MAXN; i++)
        if (!visited[i])
            primes[cnt++] = i;
            
    int n;
    while (cin >> n)
    {
        cout << n;
        if (n % 2 == 1)
        {
            if (binary_search(primes, primes + cnt, n - 2))
                cout << " is the sum of " << 2 << " and " << (n - 2) << ".\n";
            else
                cout << " is not the sum of two primes!\n";
        }
        else
        {
            int half = n / 2;
            int k = lower_bound(primes, primes + cnt, half) - primes;
            bool found = false;
            for (int i = k; i >= 0; i--)
                if (binary_search(primes + k, primes + cnt, n - primes[i]))
                {
                    if (primes[i] != (n - primes[i]))
                    {
                        cout << " is the sum of " << primes[i] << " and " << n - primes[i] << ".\n";
                        found = true;
                        break;
                    }
                }
            if (!found) cout << " is not the sum of two primes!\n";
        }
    }

    return 0;
}
