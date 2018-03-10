// Multifactorials
// UVa ID: 11347
// Verdict: Accepted
// Submission Date: 2018-03-10
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

    int primes[1000] = {0}, cnt = 0;
    for (int i = 2; i < 1000; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j < 1000; j += i)
                primes[j] = 1;
        }
        
    int cases;
    string line;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> line;
        
        int k = 0;
        while (line.back() == '!') k++, line.pop_back();
        int n = stoi(line);
        map<int, int> divisor;
        while (true)
        {
            int x = n;
            for (int j = 0; j < cnt && x > 1; j++)
            {
                while (x % primes[j] == 0)
                {
                    divisor[primes[j]]++;
                    x /= primes[j];
                }
            }
            n -= k;
            if (n <= 0) break;
        }
        unsigned long long dividers = 1, maxD = 1000000000000000000LL;
        for (auto it = divisor.begin(); it != divisor.end(); it++)
        {
            dividers *= (it->second + 1);
            if (dividers > maxD) break;
        }
        
        cout << "Case " << c << ": ";
        if (dividers <= maxD) cout << dividers << '\n';
        else cout << "Infinity\n";
    }

    return 0;
}
