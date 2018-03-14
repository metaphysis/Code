// Unlock the Lock
// UVa ID: 12160
// Verdict: Accepted
// Submission Date: 2018-02-08
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int L, U, R, added[16], visited[10010], steps[10010];
    int cases = 0;

    while (cin >> L >> U >> R, R > 0)
    {
        cout << "Case " << ++cases << ": ";

        for (int i = 0; i < R; i++)
            cin >> added[i];

        memset(visited, 0, sizeof(visited));
        queue<int> q;
        q.push(L);
        visited[L] = 1;
        steps[L] = 0;

        while (!q.empty())
        {
            int u = q.front(); q.pop();
            if (u == U)
            {
                cout << steps[u] << '\n';
                break;
            }
            for (int k = 0; k < R; k++)
            {
                int next = (u + added[k]) % 10000;
                if (!visited[next])
                {
                    visited[next] = 1;
                    q.push(next);
                    steps[next] = steps[u] + 1;
                }
            }
        }
        
        if (!visited[U]) cout << "Permanently Locked\n";
    }
    return 0;
}
