// Cycle Game
// UVa ID: 1561
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<int, set<int>> cache[21];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, ai;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cache[n].clear();
            cin >> ai;
        }
    }

    return 0;
}
