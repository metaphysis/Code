// Minimum Sum LCM
// UVa ID: 10791
// Verdict: Accepted
// Submission Date: 2017-03-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

void sieve1(int *primes, int n, int &counter)
{
    counter = 0;
    memset(primes, 1, n * sizeof(int));

    for (int i = 2; i < n; i++)
    {
        // 代码1：记录筛选得到的素数
        if (primes[i]) primes[counter++] = i;

        // 开始标记合数的操作。
        for (int j = 0; j < counter && i * primes[j] < n; j++)
        {
            // 代码2：将素数的倍数标记为合数。
            primes[i * primes[j]] = 0;

            // 代码3：退出标记操作。
            if (!(i % primes[j])) break;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int primes[50000], counter = 0;

    sieve1(primes, 50000, counter);
    
    int cases = 0;
    long long n;
    
    while (cin >> n, n != 0)
    {
        cout << "Case " << ++cases << ": ";
        
        map<int, int> primeCounter;
        while (n > 1)
        {
            bool divided = false;
            for (int i = 0; i < counter; i++)
                if ((n % primes[i]) == 0)
                {
                    primeCounter[primes[i]]++;
                    n /= primes[i];
                    divided = true;
                    break;
                }
            if (!divided) break;
        }
        
        // 未能整除完毕，是素数。
        if (n > 1) primeCounter[n]++;
        
        // 特殊情况。
        if (primeCounter.size() <= 1) primeCounter[1]++;
        if (primeCounter.size() == 1)
        {
            cout << "2\n";
            continue;
        }
        
        long long total = 0;
        for (auto pc : primeCounter)
            total += pow(pc.first, pc.second);
        
        cout << total << '\n';
    }
    
    return 0;
}
