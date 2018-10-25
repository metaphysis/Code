// Count DePrimes
// UVa ID: 11408
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5000001;

int numbers[MAXN] = {}, sum[MAXN] = {};
int primes[400000], cnt = 0;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i < MAXN; i++)
    {
        if (!numbers[i])
        {
            primes[cnt++] = i;
            numbers[i] = 1 + numbers[i - 1];
        }
        else
        {
            sum[i] = 0, n = i;
            for (int j = 0; j < cnt && n > primes[j]; j++)
                if (n % primes[j] == 0)
                {
                    sum += primes[j];
                    while (n % primes[j] == 0)
                        n /= primes[j];
                    break;
                }
            if (n != 1) sum[i] += sum[n];
            if (binary_search(primes, primes + cnt, sum)) numbers[i] = 1 + numbers[i - 1];
            else numbers[i] = numbers[i - 1];
        }
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            numbers[i * primes[j]] = 1;
            if (i % primes[j] == 0) break;
        }
    }

    int a, b;
    while (cin >> a, a > 0)
    {
        cin >> b;
        cout << numbers[b] - numbers[a - 1] << '\n';
    }

    return 0;
}
