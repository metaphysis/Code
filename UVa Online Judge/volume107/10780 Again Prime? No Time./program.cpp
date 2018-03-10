// Again Prime? No Time.
// UVa ID: 10780
// Verdict: Accepted
// Submission Date: 2018-03-10
// UVa Run Time: 1.180s
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
    for (int i = 2; i * i < 10000; i++)
        if (!primes[i])
            for (int j = i * i; j < 10000; j += i)
                primes[j] = 1;
    for (int i = 2; i < 10000; i++)
        if (!primes[i])
            primes[cnt++] = i;
            
    int cases, m, n;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ":\n";

        cin >> m >> n;
        map<int, int> divisorOfM, divisorOfN;
        for (int i = 0; i < cnt; i++)
        {
            if (primes[i] > m) break;
            while (m % primes[i] == 0)
            {
                divisorOfM[primes[i]]++;
                m /= primes[i];
            }
        }
        
        for (int i = 2; i <= n; i++)
        {
            int x = i;
            for (int j = 0; j < cnt; j++)
            {
                if (primes[j] > x) break;
                while (x % primes[j] == 0)
                {
                    divisorOfN[primes[j]]++;
                    x /= primes[j];
                }
            }
        }
        
        bool divided = true;
        int maxE = 0x3f3f3f3f;
        for (auto it = divisorOfM.begin(); it != divisorOfM.end(); it++)
        {
            int p = it->first, e = it->second;
            if (divisorOfN.find(p) == divisorOfN.end() || divisorOfN[p] < e)
            {
                divided = false;
                break;
            }
            maxE = min(maxE, divisorOfN[p] / e);
        }
        if (!divided)
        {
            cout << "Impossible to divide\n";
        }
        else
        {
            cout << maxE << '\n';
        }
    }

    return 0;
}
