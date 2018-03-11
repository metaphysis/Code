// A Different Kind of Sorting
// UVa ID: 11353
// Verdict: Accepted
// Submission Date: 2018-03-11
// UVa Run Time: 0.290s
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

int cntOfPrimes[2000010] = {0, 1}, number[2000000];

bool cmp(int a, int b)
{
    if (cntOfPrimes[a] != cntOfPrimes[b])
        return cntOfPrimes[a] < cntOfPrimes[b];
    return a < b;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i * i <= 2000000; i++)
        if (!cntOfPrimes[i])
        {
            for (int j = i * i; j <= 2000000; j += i)
                cntOfPrimes[j] = 1;
        }
    for (int i = 2; i <= 2000000; i++)
        if (!cntOfPrimes[i]) cntOfPrimes[i] = 1;
        else cntOfPrimes[i] = 0;

    int primes[1500] = {0}, cnt = 0;
    for (int i = 2; i * i < 1500; i++)
        if (!primes[i])
            for (int j = i * i; j < 1500; j += i)
                primes[j] = 1;
    for (int i = 2; i < 1500; i++)
        if (!primes[i])
            primes[cnt++] = i;
            
    for (int i = 2; i <= 2000000; i++)
        if (!cntOfPrimes[i])
        {
            int x = i;
            for (int j = 0; j < cnt && x > 1; j++)
                if (x % primes[j] == 0)
                {
                    cntOfPrimes[i] = 1 + cntOfPrimes[x / primes[j]];
                    break;
                }
        }

    for (int i = 0; i < 2000000; i++)
        number[i] = i + 1;
    sort(number, number + 2000000, cmp);

    int n, cases = 0;
    while (cin >> n, n > 0)
    {
        cout << "Case " << ++cases << ": " << number[n - 1] << '\n';
    }

    return 0;
}
