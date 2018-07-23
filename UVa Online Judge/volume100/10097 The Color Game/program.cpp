// The Color Game
// UVa ID: 10097
// Verdict: Accepted
// Submission Date: 2018-07-11
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int to, color;
    edge (int to = 0, int color = 0): to(to), color(color) {}
};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n, to, n1, n2, n3;
    vector<edge> edges[110];

    while (cin >> n, n > 0)
    {
        for (int i = 1; i <= n; i++)
        {
            edges[i].clear();
            for (int j = 1; j <= n; j++)
            {
                cin >> to;
                if (to) edges[i].push_back(edge(to, j));
            }
        }
        cin >> n1 >> n2 >> n3;

        int moves[n + 1][n + 1] = {}, best = -1;
        pair<int, int> pr;
        queue<pair<int, int>> q;
        q.push(make_pair(n1, n2));
        moves[n1][n2] = 1;

        while (!q.empty())
        {
            pr = q.front(); q.pop();
            if (pr.first == n3 || pr.second == n3)
            {
                best = moves[pr.first][pr.second];
                break;
            }
            for (auto e : edges[pr.first])
            {
                if (e.color == pr.second)
                {
                    if (moves[e.to][pr.second] == 0)
                    {
                        moves[e.to][pr.second] = moves[pr.first][pr.second] + 1;
                        q.push(make_pair(e.to, pr.second));
                    }
                }
            }
            for (auto e : edges[pr.second])
            {
                if (e.color == pr.first)
                {
                    if (moves[pr.first][e.to] == 0)
                    {
                        moves[pr.first][e.to] = moves[pr.first][pr.second] + 1;
                        q.push(make_pair(pr.first, e.to));
                    }
                }
            }
        }

        cout << "Game #" << ++cases << '\n';
        if (best == -1) cout << "Destination is Not Reachable !\n";
        else cout << "Minimum Number of Moves = " << (best - 1) << '\n';
        cout << '\n';
    }

    return 0;
}
