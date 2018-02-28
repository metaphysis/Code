// Super Number
// UVa ID: 10624
// Verdict: Accepted
// Submission Date: 2018-02-28
// UVa Run Time: 0.420s
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

int number[32], n, m, finished, lastDigit[32][10];

void dfs(int d)
{
    if (finished) return;
    if (d == m)
    {
        finished = 1;
        return;
    }

    for (int i = (d ? 0 : 1); i < 10; i++)
    {
        if (((d + 1) >= n) && !lastDigit[d + 1][i]) continue;
        number[d] = i;
        long long r = 0;
        if ((d + 1) >= n)
        {
            for (int j = 0, cnt = 1; j <= d; j++, cnt++)
            {
                
                r = (r << 3) + (r << 1) + number[j];
                if (cnt >= 18) cnt = 1, r %= (d + 1);
            }
            r %= (d + 1);
        }
        if (r == 0) dfs(d + 1);
        if (finished) break;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    memset(lastDigit, 0, sizeof(lastDigit));
    for (int i = 1; i < 32; i++)
        for (int j = 0; j < 10; j++)
            lastDigit[i][(i * j) % 10] = 1;

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case " << c << ": ";

        cin >> n >> m;

        memset(number, 0, sizeof(number));
        finished = 0;
        dfs(0);

        if (finished)
        {
            for (int i = 0; i < m; i++)
                cout << number[i];
            cout << '\n';
        }
        else cout << "-1\n";
    }

    return 0;
}
