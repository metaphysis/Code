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

const int MAXN = 1000000;

int primes[MAXN], phi[MAXN] = {0, 1}, counterOfPrimes = 0;

void sieve1(int *primes, int n, int &counterOfPrimes)
{
    // 初始时假定所有数为素数，从最小的素数开始筛除。
    counterOfPrimes = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
        if (primes[i])
        {
            // 记录筛选得到的素数。
            primes[counterOfPrimes++] = i;

            // 如果i为素数则将其倍数标记为非素数。
            for (int j = i + i; j < n; j += i) primes[j] = 0;
        }
}

int getPhi(int m)
{
    int phi = m;
    for (int i = 0; i < counterOfPrimes; i++) {
        if (primes[i] > m) break;
        if (m % primes[i] == 0)
        {
            while (m % primes[i] == 0) m /= primes[i];
            phi -= phi / primes[i];
        }
    }
    if (m > 1) phi -= phi / m;
    return phi;
}

void sieve2(int *primes, int n, int &counterOfPrimes)
{
    counterOfPrimes = 0; iota(phi, phi + n, 0);

    for (int i = 2; i < n; i++)
        if (phi[i] == i)
        {
            primes[counterOfPrimes++] = i;
            for (int j = i; j < n; j += i) phi[j] -= phi[j] / i;
        }
}

void sieve3(int *primes, int n, int &counterOfPrimes)
{
    // 初始时假定所有数为素数，从最小的素数开始筛除。
    counterOfPrimes = 0; iota(primes, primes + n, 0);

    for (int i = 2; i < n; i++)
    {
        if (primes[i] == i)
        {
            // 素数的欧拉函数值为值减去一。
            phi[i] = i - 1;

            // 记录筛选得到的素数。
            primes[counterOfPrimes++] = i;

            // 如果i为素数则将其倍数标记为非素数。标记的方式是i的倍数所对应的元素值
            // 设置为它的最小素因子，即i。
            for (int j = i + i; j < n; j += i)
                if (primes[j] == j)
                    primes[j] = i;
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
    sieve1(primes, MAXN, counterOfPrimes);
    
    int n;
    while (cin >> n, n > 0) cout << getPhi(n) << '\n';
    cout << '\n';

    sieve2(primes, MAXN, counterOfPrimes);
    for (int i = 0; i <= 1000; i++) cout << primes[i] << ' ' << getPhi(primes[i]) << '\n';
    cout << '\n';

    sieve3(primes, MAXN, counterOfPrimes);
    for (int i = 0; i <= 1000; i++) cout << primes[i] << ' ' << phi[primes[i]] << '\n';

    return 0;
}
