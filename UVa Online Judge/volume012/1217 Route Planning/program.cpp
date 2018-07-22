// Route Planning
// UVa ID: 1217
// Verdict: Accepted
// Submission Date: 2018-07-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, r, INF = 0x3f3f3f3f;
int dist[110][110], spot[32], used[32], shorest, cnt;
int path[32], firstSpot, lastSpot;

void dfs(int depth, int length)
{
    if (depth == cnt - 2)
    {
        if (dist[spot[path[depth - 1]]][lastSpot])
        {
            shorest = min(shorest, length + dist[spot[path[depth - 1]]][lastSpot]);
        }
        return;
    }
    if (length + (cnt - 1 - depth) >= shorest) return;
    for (int i = 1; i < cnt - 1; i++)
    {
        if (used[i]) continue;
        if (!depth && !dist[firstSpot][spot[i]]) continue;
        if (depth && !dist[spot[path[depth - 1]]][spot[i]]) continue;
        used[i] = 1, path[depth] = i;
        if (!depth)
            dfs(depth + 1, dist[firstSpot][spot[i]]);
        else
            dfs(depth + 1, length + dist[spot[path[depth - 1]]][spot[i]]);
        used[i] = 0;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string line;
    while (cin >> n >> r)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> dist[i][j];
        cin.ignore(256, '\n');
        for (int i = 1; i <= r; i++)
        {
            getline(cin, line);
            istringstream iss(line);
            cnt = 0;
            while (iss >> spot[cnt]) cnt++;
            if (cnt == 2)
            {
                cout << dist[spot[0]][spot[1]] << '\n';
                continue;
            }
            firstSpot = spot[0], lastSpot = spot[cnt - 1];
            memset(used, 0, sizeof(used));
            used[0] = used[cnt - 1] = 1;
            shorest = INF;
            dfs(0, 0);
            if (shorest != INF) cout << shorest << '\n';
            else cout << "0\n";
        }
    }

    return 0;
}
