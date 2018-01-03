// Pole Position
// UVa ID: 12150
// Verdict: Accepted
// Submission Date: 2018-01-01
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

    int n, pole[1010], c, p;
    
    while (cin >> n, n > 0)
    {
        memset(pole, 0, sizeof(pole));
        bool broken = false;
        for (int i = 1; i <= n; i++)
        {
            cin >> c >> p;
            if (broken) continue;
            p = i + p;
            if (p < 1 || p > n) { broken = true; continue; }
            if (pole[p]) { broken = true; continue; }
            pole[p] = c;
        }
        if (broken) cout << -1 << '\n';
        else
        {
            for (int i = 1; i <= n; i++)
            {
                if (i > 1) cout << ' ';
                cout << pole[i];
            }
            cout << '\n';
        }
    }

    return 0;
}
