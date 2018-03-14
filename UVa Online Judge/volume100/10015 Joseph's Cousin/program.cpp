// Joseph's Cousin
// UVa ID: 10015
// Verdict: Accepted
// Submission Date: 2017-12-23
// UVa Run Time: 0.310s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int survivor[3510] = {0}, primes[50000], cnt = 0;
    
    memset(primes, 1, sizeof(primes));
    for (int i = 2; i < 50000; i++)
    {
        if (primes[i]) primes[cnt++] = i;
        for (int j = i + i; j < 50000; j += i)
            primes[j] = 0;
        if (cnt >= 3510) break;
    }
    
    int n;
    while (cin >> n, n > 0)
    {
        if (!survivor[n])
        {
            vector<int> circle(n);
            iota(circle.begin(), circle.end(), 1);

            int k = 0;
            for (int i = 0; (i + 1) < n; i++)
            {
                k = (k + primes[i] - 1) % circle.size();
                k = circle.erase(circle.begin() + k) - circle.begin();
                k = k % circle.size();
            }

            survivor[n] = circle.front();
        }

        cout << survivor[n] << '\n';
    }

    return 0;
}
