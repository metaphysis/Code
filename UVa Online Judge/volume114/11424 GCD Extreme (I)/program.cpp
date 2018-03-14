// GCD Extreme (I)
// UVa ID: 11424
// Verdict: Accepted
// Submission Date: 2017-03-23
// UVa Run Time: 0.180s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200001;

int primes[MAXN], phi[MAXN] = {0, 1}, counter = 0;
long long sum[MAXN] = {0};

void sieve(int *primes, int n, int &counter)
{
    // 初始时假定所有数为素数，从最小的素数开始筛除。
    counter = 0;
    memset(primes, -1, n * sizeof(int));

    for (int i = 2; i < n; i++)
    {
        if (primes[i] == -1)
        {
            // 素数的欧拉函数值为值减去一。
            phi[i] = i - 1;

            // 记录筛选得到的素数。
            primes[counter++] = i;

            // 如果i为素数则将其倍数标记为非素数。标记的方式是i的倍数所对应的元素值
            // 设置为它的最小素因子，即i。
            for (int j = i + i; j < n; j += i)
                if (primes[j] == -1) primes[j] = i;
        }
        else
        {
            // 非素数保存的是它的最小素因子，根据递推关系计算欧拉函数值。
            int k = i / primes[i];
            if (k % primes[i] == 0) phi[i] = primes[i] * phi[k];
            else phi[i] = (primes[i] - 1) * phi[k];
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    sieve(primes, MAXN, counter);
    
    for (int i = 2; i < MAXN; i++)
    {
        sum[i] += sum[i - 1] + phi[i];

        int upper = sqrt(i);
        for (int j = 2; j <= upper; j++)
            if (i % j == 0)
            {
                int k = i / j;
                sum[i] += k * phi[j];
                if (j != k) sum[i] += j * phi[k];
            }
    }

    int n;
    while (cin >> n, n > 0) cout << sum[n] << '\n';

    return 0;
}
