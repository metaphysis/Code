// Ferry Loading II
// UVa ID: 10440
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int n, t, m, arrived[1440];
        cin >> n >> t >> m;
        
        for (int i = 1; i <= m; i++)
            cin >> arrived[i];
        int trips = (m / n) + (m % n != 0);
        
        int cars = 0, times = 0;
        if (m % n != 0)
        {
            cars = m % n;
            times = arrived[cars] + t;
        }
        while (cars < m)
        {
            cars += n;
            times = max(times, arrived[cars]) + t;
        }
        cout << times << ' ' << trips << '\n';
    }

    return 0;
}
