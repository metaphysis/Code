// LCM Cardinality
// UVa ID: 10892
// Verdict: Accepted
// Submission Date: 2017-03-18
// UVa Run Time: 0.030s
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

int gcd1(int a, int b)
{
    int t;
    while (b != 0) t = a, a = b, b = t % b;
    return a;
}

map<int, int> primeFrequencies;
vector<int> primeDivisors;
vector<long long> divisors;
        
void dfs(int depth, int number, int maxDepth)
{
    if (depth >= maxDepth)
    {
        divisors.push_back(number);
        return;
    }
    
    int next = number;
    for (int i = 0; i <= (int)primeFrequencies[primeDivisors[depth]]; i++)
    {
        if (i > 0) next *= primeDivisors[depth];
        dfs(depth + 1, next, maxDepth);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int primes[50000], counter;

    sieve1(primes, 50000, counter);
    
    int n, nn;
    
    while (cin >> n, n > 0)
    {
        nn = n;
        
        primeFrequencies.clear();
        while (nn > 1)
        {
            bool divided = false;
            for (int i = 0; i < counter; i++)
                if ((nn % primes[i]) == 0)
                {
                    primeFrequencies[primes[i]]++;
                    nn /= primes[i];
                    divided = true;
                    break;
                }
                
            if (!divided)
            {
                primeFrequencies[nn]++;
                break;
            }
        }
        
        primeDivisors.clear();
        divisors.clear();
        
        int total = 1;
        for (auto f : primeFrequencies)
        {
            total *= (f.second + 1);
            primeDivisors.push_back(f.first);
        }        
        
        // 回溯获得所有的约数。
        dfs(0, 1, (int)primeDivisors.size());
        
        // 检查两个约数的最小公倍数是否为n。
        for (int i = 1; i < (int)divisors.size() - 1; i++)
            for (int j = i + 1; j < (int)divisors.size() - 1; j++)
                if ((divisors[i] / gcd1(divisors[i], divisors[j]) * divisors[j]) == n)
                    total++;

        cout << n << ' ' << total << '\n';
    }
    
    return 0;
}
