// Anagrammatic Primes
// UVa ID: 897
// Verdict: Accepted
// Submission Date: 2016-12-06
// UVa Run Time: 0.060s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000000;

int level[7] = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
int primes[MAXN], counter = 0;
int anagrammatic[10000];

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
    
    // 剔除包含数字0，2，4，5，6，8的素数，它们不是乱序素数。
    int next_counter = 0;
    for (int i = 0, t = primes[i]; i < counter; i++, t = primes[i])
    {
        if (t < 10)
        {
            primes[next_counter++] = primes[i];
            continue;
        }
        
        bool added = true;
        while (t)
        {
            int d = t % 10;
            if (d % 2 == 0 || d == 5)
            {
                added = false;
                break;
            }
            t /= 10;
        }
        
        if (added) primes[next_counter++] = primes[i];
    }
    counter = next_counter;
    
    // 逐个检查剩余的素数是否为乱序素数。
    next_counter = 0;
    for (int i = 0, t = primes[i]; i < counter; i++, t = primes[i])
    {
        if (t < 10)
        {
            anagrammatic[next_counter++] = primes[i];
            continue;
        }
        
        vector<int> digits;
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
            
            if (flag) anagrammatic[next_counter++] = primes[i];
        }
    }
    
    int n, upper;
    while (cin >> n, n > 0)
    {
        for (int i = 0; i < 7; i++)
            if (n < level[i])
            {
                upper = level[i];
                break;
            }
                
        int k = upper_bound(anagrammatic, anagrammatic + next_counter, n) - anagrammatic;
        if (k < counter && anagrammatic[k] < upper) cout << anagrammatic[k] << '\n';
        else cout << "0\n";
    }
    
	return 0;
}
