// Corporative Network
// UVa ID: 1329
// Verdict: Accepted
// Submission Date: 2022-01-06
// UVa Run Time: 1.220s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20010;

int n, parent[MAXN];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, e1, e2;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++) parent[i] = i;
        char cmd;
        while (cin >> cmd)
        {
            if (cmd == 'O') break;
            if (cmd == 'E')
            {
                cin >> e1;
                int L = 0;
                while (parent[e1] != e1)
                {
                    L += abs(e1 - parent[e1]) % 1000;
                    e1 = parent[e1];
                }
                cout << L << '\n';
            }
            if (cmd == 'I')
            {
                cin >> e1 >> e2;
                parent[e1] = e2;
            }
        }
    }
    return 0;
}
