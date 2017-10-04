// GCD + LCM
// UVa ID: 11317
// Verdict: Accepted
// Submission Date: 2017-02-23
// UVa Run Time: 1.110s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// Euler's totient function
//

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

#define ull unsigned long long

const int MAXN = 1000001;

int primes[MAXN], phi[MAXN] = {0, 1}, counter = 0;
double gcd[MAXN] = {0.0}, lcm[MAXN] = {0.0};

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
    sieve(primes, MAXN, counter);
    
    for (int i = 1; i < MAXN; i++)
        for (int j = i + i, k = 2; j < MAXN; j += i, k++)
            gcd[j] += log10(i) * phi[k];

    for (int i = 2; i < MAXN; i++)
    {
        lcm[i] = lcm[i - 1] + log10(i);
        gcd[i] += gcd[i - 1];

        //int upper = sqrt(i);
        //for (int j = 2; j <= upper; j++)
        //    if (i % j == 0)
        //    {
        //        int k = i / j;
        //        gcd[i] += log10(k) * phi[j];
        //        if (j != k) gcd[i] += log10(j) * phi[k];
        //    }
    }

    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ": ";
        cout << ((long long)(gcd[n] / 100) + 1) << ' ';
        cout << ((long long)(lcm[n] * (n - 1) - gcd[n]) / 100 + 1) << '\n';
    }
    
    return 0;
}
