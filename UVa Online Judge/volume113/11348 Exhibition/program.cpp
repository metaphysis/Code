// Exhibition
// UVa ID: 11348
// Verdict: Accepted
// Submission Date: 2018-01-13
// UVa Run Time: 0.020s
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

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        int n, m, a;        

        map<int, int> types;
        set<int> stamp[50];
        
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> m;
            for (int j = 1; j <= m; j++)
            {
                cin >> a;
                stamp[i].insert(a);
            }
            for (auto s : stamp[i])
                types[s]++;
        }
        cout << "Case " << c << ":";

        double uniques = 0;
        for (auto t : types)
            if (t.second == 1)
                uniques++;

        for (int i = 0; i < n; i++)
        {
            double inhand = 0;
            for (auto s : stamp[i])
                if (types[s] == 1)
                    inhand++;
            cout << ' ';
            cout << fixed << setprecision(6) << (inhand * 100.0 / uniques) << '%';
        }
        cout << '\n';
    }

    return 0;
}
