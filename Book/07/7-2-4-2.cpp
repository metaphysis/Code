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

int primes[MAXN], phi[MAXN] = {0, 1}, counter = 0;

void sieve(int *primes, int n, int &counter)
{
    // 初始时假定所有数为素数，从最小的素数开始筛除。
    counter = 0; iota(primes, primes + n, 0);

    for (int i = 2; i < n; i++)
    {
        if (primes[i] == i)
        {
            // 素数的欧拉函数值为值减去一。
            phi[i] = i - 1;

            // 记录筛选得到的素数。
            primes[counter++] = i;

            // 如果i为素数则将其倍数标记为非素数。标记的方式是i的倍数所对应的元素值
            // 设置为它的最小素因子，即i。
            for (int j = i + i; j < n; j += i)
                if (primes[j] == j) primes[j] = i;
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
    
    for (int i = 0; i <= 10000; i++) cout << primes[i] << ' ' << phi[i] << '\n';
        
    return 0;
}
