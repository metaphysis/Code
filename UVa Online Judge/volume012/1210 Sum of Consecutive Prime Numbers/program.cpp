// Sum of Consecutive Prime Numbers
// UVa ID: 1210
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[20010] = {0}, cnt = 0;
    for (int i = 2; i < 20010; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < 20010; j += i)
                primes[j] = 1;
            if (i > 10000) break;
        }
    int answer[100010] = {0};
    for (int i = 0; i < cnt; i++)
    {
        int sum = 0;
        for (int j = i; j < cnt; j++)
        {
            sum += primes[j];
            answer[sum]++;
            if (sum > 10000) break;
        }
    }
    int n;
    while (cin >> n, n > 0)
    {
        cout << answer[n] << '\n';
    }
    return 0;
}
