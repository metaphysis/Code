// Determinate Prime
// UVa ID: 10650
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

    int primes[32000] = {}, cnt = 0;
    for (int i = 2; i * i < 32000; i++)
        if (!primes[i])
            for (int j = i * i; j < 32000; j += i)
                primes[j] = 1;
    for (int i = 2; i < 32000; i++)
        if (!primes[i])
            primes[cnt++] = i;

    vector<pair<int, int>> sets;
    for (int i = 1; i < cnt; )
    {
        int last = i;
        for (int j = i + 1; j < cnt; j++)
            if ((primes[j] - primes[j - 1]) == (primes[i] - primes[i - 1]))
                last = j;
            else
                break;
        if (last > i)
           sets.push_back(make_pair(i - 1, last));
        i = last + 1;
    }

    int x, y;
    while (cin >> x >> y)
    {
        if (x == 0 && y == 0) break;
        if (x > y) swap(x, y);
        for (int i = 0; i < sets.size(); i++)
        {
            if (primes[sets[i].first] > y) break;
            if (primes[sets[i].second] < x) continue;
            if (primes[sets[i].first] >= x && primes[sets[i].second] <= y)
            {
                cout << primes[sets[i].first];
                for (int j = sets[i].first + 1; j <= sets[i].second; j++)
                    cout << ' ' << primes[j];
                cout << '\n';
            }   
        }                 
    }

    return 0;
}
