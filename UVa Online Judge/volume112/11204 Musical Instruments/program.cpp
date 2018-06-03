// Musical Instruments
// UVa ID: 11204
// Verdict: Accepted
// Submission Date: 2018-06-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int choices[36] = {};
    int cases, n, m, priority;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n >> m;
        memset(choices, 0, sizeof(choices));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
            {
                cin >> priority;
                if (priority == 1) choices[j]++;
            }
        int r = 1;
        for (int i = 1; i <= n; i++)
            if (choices[i] > 0)
                r *= choices[i];
        cout << r << '\n';
    }

    return 0;
}
