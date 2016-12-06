// Anagrammatic Primes
// UVa ID: 897
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

const int MAXN = 10000000;

int level[7] = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
int primes[MAXN], counter = 0;

void sieve()
{
    memset(primes, 0, sizeof(primes));
    for (int i = 2; i < MAXN; i++)
    {
        // 代码1：记录筛选得到的素数
        if (!primes[i]) primes[counter++] = i;

        // 开始标记合数的操作。
        for (int j = 0; j < counter && i * primes[j] < MAXN; j++)
        {
            // 代码2：将素数的倍数标记为合数。
            primes[i * primes[j]] = 1;

            // 代码3：退出标记操作。
            if (!(i % primes[j])) break;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    sieve();
    
    int n, upper;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < 7; i++)
            if (n < level[i])
            {
                upper = level[i];
                break;
            }
                
        int k = upper_bound(primes, primes + counter, n) - primes;
        
        bool successed = false;
        if (k < counter)
        {
            vector<int> digits;
            for (int i = k, t = primes[i]; t < upper; i++, t = primes[i])
            {
                cout << n << ' ' << t << '\n';
                while (t)
                {
                    int d = t % 10;
                    if (d % 2 == 0 || d == 5)
                    {
                        digits.clear();
                        break;
                    }
                    digits.push_back(d);
                    t /= 10;
                }

                if (digits.size() > 0)
                {
                    bool flag = true;
                    sort(digits.begin(), digits.end());
                    do
                    {
                        int next = 0;
                        for (int j = 0; j < digits.size(); j++)
                            next = next * 10 + digits[j];
                        if (!binary_search(primes, primes + counter, next))
                        {
                            flag = false;
                            break;
                        }
                    } while (next_permutation(digits.begin(), digits.end()));
                    
                    if (flag)
                    {
                        cout << primes[i] << '\n';
                        successed = true;
                        break;
                    }
                }
            }
        }
        
        if (!successed) cout << "0\n";
    }
    
	return 0;
}
