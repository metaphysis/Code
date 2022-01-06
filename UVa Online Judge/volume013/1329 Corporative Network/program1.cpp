// Corporative Network
// UVa ID: 1329
// Verdict: Accepted
// Submission Date: 2022-01-06
// UVa Run Time: 0.020s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 20010;

int n, parent[MAXN], length[MAXN];

int update(int x)
{
    if (x == parent[x]) return x;
    int y = update(parent[x]);
    length[x] += length[parent[x]];
    return parent[x] = y;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, e1, e2;
    cin >> T;
    for (int cs = 1; cs <= T; cs++)
    {
        cin >> n;
        for (int i = 1; i <= n; i++) parent[i] = i, length[i] = 0;
        char cmd;
        while (cin >> cmd)
        {
            if (cmd == 'O') break;
            if (cmd == 'E')
            {
                cin >> e1;
                update(e1);
                cout << length[e1] << '\n';
            }
            if (cmd == 'I')
            {
                cin >> e1 >> e2;
                parent[e1] = e2;
                length[e1] = abs(e1 - e2) % 1000;
            }
        }
    }
    return 0;
}
