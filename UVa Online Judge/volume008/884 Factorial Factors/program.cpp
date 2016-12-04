// Factorial Factors
// UVa ID: 884
// Verdict: Accepted
// Submission Date: 2016-12-02
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

const int MAX_N = 1000000;

int primes[MAX_N + 1], counter = 0;
int terms[MAX_N + 1] = {0}, is_primes[MAX_N + 1] = {0};
int total[MAX_N + 1] = {0};

void sieve()
{
    // 初始时假定所有数为素数，从最小的素数开始筛除。
    memset(primes, 0, sizeof(primes));
    for (int i = 2; i <= MAX_N; i++)
        if (!primes[i])
        {
            // 记录筛选得到的素数。
            primes[counter++] = i;

            // 如果i为素数则将其倍数标记为非素数。
            for (int j = i + i; j <= MAX_N; j += i) primes[j] = -1;
        }
        
    for (int i = 0; i < counter; i++) is_primes[primes[i]] = 1;
}

void sieve1()
{
    memset(primes, 0, sizeof(primes));
    for (int i = 2; i < MAX_N; i++)
    {
        // 代码1：记录筛选得到的素数
        if (!primes[i]) primes[counter++] = i;

        // 开始标记合数的操作。
        for (int j = 0; j < counter && i * primes[j] < MAX_N; j++)
        {
            // 代码2：将素数的倍数标记为合数。
            primes[i * primes[j]] = -1;

            // 代码3：退出标记操作。
            if (!(i % primes[j])) break;
        }
    }
    
    for (int i = 0; i < counter; i++) is_primes[primes[i]] = 1;
}

int findTerms(int n)
{
    if (is_primes[n]) return 1;
    
    if (!terms[n])
    {
        int nn = n;
        for (int i = 0; i < counter; i++)
            if (nn % primes[i] == 0)
            {
                nn /= primes[i];
                break;
            }
            
        return terms[n] = 1 + findTerms(nn);
    }

    return terms[n];
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    sieve();

    for (int i = 2; i <= MAX_N; i++)
    {
        terms[i] = findTerms(i);
        total[i] = terms[i] + total[i - 1];
    }
    
    int n;
    while (cin >> n) cout << total[n] << '\n';
    
	return 0;
}
