// Benefit
// UVa ID: 11889
// Verdict: Accepted
// Submission Date: 2018-03-10
// UVa Run Time: 0.530s
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

    int primes[10000] = {0}, cnt = 0;
    for (int i = 2; i < 10000; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < 10000; j += i)
                primes[j] = 1;
        }

    int cases, A, C;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> A >> C;
        if (C % A != 0)
        {
            cout << "NO SOLUTION\n";
            continue;
        }

        map<int, int> divisorOfA, divisorOfC;
        for (int i = 0; i < cnt && A > 1; i++)
            while (A % primes[i] == 0)
            {
                divisorOfA[primes[i]]++;
                A /= primes[i];
            }
        if (A > 1) divisorOfA[A]++;
        for (int i = 0; i < cnt && C > 1; i++)
            while (C % primes[i] == 0)
            {
                divisorOfC[primes[i]]++;
                C /= primes[i];
            }
        if (C > 1) divisorOfC[C]++;
        
        map<int, int> divisorOfB;
        for (auto it = divisorOfC.begin(); it != divisorOfC.end(); it++)
        {
            int p = it->first, e = it->second;
            if (divisorOfA.find(p) == divisorOfA.end() || e > divisorOfA[p])
                divisorOfB[p] = e;
        }
        
        int B = 1;
        for (auto it = divisorOfB.begin(); it != divisorOfB.end(); it++)
            B *= (int)pow(it->first, it->second);
        cout << B << '\n';
    }

    return 0;
}
