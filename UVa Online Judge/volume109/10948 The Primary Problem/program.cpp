// The Primary Problem
// UVa ID: 10948
// Verdict: Accepted
// Submission Date: 2018-03-08
// UVa Run Time: 0.580s
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

    int primes[1000010] = {0}, cnt = 0;
    for (int i = 2; i * i < 1000010; i++)
        if (!primes[i])
            for (int j = i * i; j < 1000010; j += i)
                primes[j] = 1;
    for (int i = 2; i < 1000010; i++)
        if (!primes[i])
            primes[cnt++] = i;
            
    int n;
    while (cin >> n, n > 0)
    {
        cout << n << ":\n";
        bool found = false;
        for (int i = 0; i < cnt; i++)
        {
            if (primes[i] >= n) break;
            if (binary_search(primes, primes + cnt, n - primes[i]))
            {
                cout << primes[i] << '+' << n - primes[i] << '\n';
                found = true;
                break;
            }
        }
        if (!found) cout << "NO WAY!\n";
    }

    return 0;
}
