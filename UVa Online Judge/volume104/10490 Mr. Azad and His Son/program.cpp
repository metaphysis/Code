// Mr. Azad and His Son
// UVa ID: 10490
// Verdict: Accepted
// Submission Date: 2018-03-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int primes[46000], cnt = 0;
    for (int i = 2; i * i < 46000; i++)
        if (!primes[i])
            for (int j = i * i; j < 46000; j += i)
                primes[j] = 1;
    for (int i = 2; i < 46000; i++)
        if (!primes[i])
            primes[cnt++] = i;
            
    int n;
    while (cin >> n, n > 0)
    {
        if (!binary_search(primes, primes + cnt, n))
        {
            cout << "Given number is NOT prime! NO perfect number is available.\n";
            continue;
        }

        bool flag = true;
        int p = pow(2, n) - 1;
        if (p < 46000) flag = binary_search(primes, primes + cnt, p);
        else
        {
            for (int i = 0; i < cnt; i++)
                if (p % primes[i] == 0)
                {
                    flag = false;
                    break;
                }
        }
        if (flag)
            cout << "Perfect: " << (long long)pow(2, n - 1) * (long long)p << "!\n";
        else
            cout << "Given number is prime. But, NO perfect number is available.\n";
    }

    return 0;
}
