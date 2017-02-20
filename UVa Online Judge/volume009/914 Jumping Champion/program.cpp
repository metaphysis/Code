// Jumping Champion
// UVa ID: 914
// Verdict: Accepted
// Submission Date: 2017-02-11
// UVa Run Time: 0.010s
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
#include <vector>

using namespace std;

const int MAX_N = 1000000;

int primes[MAX_N], diff[MAX_N], counter = 0, total = 0;

void sieve()
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
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    sieve();

    int T, L, U, LL, UU;
    cin >> T;

    for (int i = 1; i <= T; i++)
    {
        cin >> L >> U;
        LL = lower_bound(primes, primes + counter, L) - primes;
        if (LL == counter)
        {
            cout << "No jumping champion\n";
            continue;
        }
        
        UU = lower_bound(primes, primes + counter, U) - primes;
        if (UU == 0)
        {
            cout << "No jumping champion\n";
            continue;            
        }

        if (UU == counter || primes[UU] > U)
        {
            UU--;
        }
        
        if (LL == UU)
        {
            cout << "No jumping champion\n";
            continue;
        }
        
        total = 0;
        for (int j = LL + 1; j <= UU; j++)
            diff[total++] = primes[j] - primes[j - 1];
            
        sort(diff, diff + total);
        
        int current = 0, max_times = 0, secondary_max_times = 0, times = 0;
        int max_times_number;

        for (int j = 0; j < total; j++)
        {
            if (diff[j] == current)
            {
                times++;
            }
            else
            {
                if (times >= max_times)
                {
                    secondary_max_times = max_times;
                    max_times = times;
                    max_times_number = current;
                }

                current = diff[j];
                times = 1;
            }
        }

        if (times >= max_times)
        {
            secondary_max_times = max_times;
            max_times = times;
            max_times_number = current;
        }
 
        if (max_times > secondary_max_times)
        {
            cout << "The jumping champion is " << max_times_number << '\n';
        }
        else
        {
            cout << "No jumping champion\n";
        }
    }

    return 0;
}
