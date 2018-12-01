// Hic-Hac-Hoe
// UVa ID: 11967
// Verdict: Accepted
// Submission Date: 2018-12-01
// UVa Run Time: 0.180s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<int, map<int, int>> dots1, dots2;
list<int> edges1[200010], edges2[200010];
int offset[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};
int visited[200010], cnt = 0;

void dfs1(int u)
{
    visited[u] = 1, cnt++;
    for (auto v : edges1[u])
        if (!visited[v])
            dfs1(v);
}

void dfs2(int u)
{
    visited[u] = 1, cnt++;
    for (auto v : edges2[u])
        if (!visited[v])
            dfs2(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T, N, K;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> N >> K;

        int A = 4 * (N / 2 + 1);
        for (int i = 0; i < A; i++)
        {
            edges1[i].clear();
            edges2[i].clear();
        }
        dots1.clear();
        dots2.clear();

        int S1 = 0, S2 = 0;
        for (int i = 0, x, y; i < N; i++)
        {
            cin >> x >> y;
            if (i % 2 == 0)
            {
                S1 += 4;
                dots1[x][y] = i / 2;
                for (int k = 0; k < 8; k++)
                {
                    int xx = x + offset[k][0], yy = y + offset[k][1];
                    if (dots1.find(xx) != dots1.end())
                    {
                        if (dots1[xx].find(yy) != dots1[xx].end())
                        {
                            int id = dots1[xx][yy];
                            edges1[4 * (i / 2) + k / 2].push_back(4 * id + k / 2);
                            edges1[4 * id + k / 2].push_back(4 * (i / 2) + k / 2);
                        }
                    }
                }
            }
            else
            {
                S2 += 4;
                dots2[x][y] = i / 2;
                for (int k = 0; k < 8; k++)
                {
                    int xx = x + offset[k][0], yy = y + offset[k][1];
                    if (dots2.find(xx) != dots2.end())
                    {
                        if (dots2[xx].find(yy) != dots2[xx].end())
                        {
                            int id = dots2[xx][yy];
                            edges2[4 * (i / 2) + k / 2].push_back(4 * id + k / 2);
                            edges2[4 * id + k / 2].push_back(4 * (i / 2) + k / 2);
                        }
                    }
                }
            }
        }
        
        bool crosses_win = false;
        memset(visited, 0, S1 * sizeof(int));
        for (int i = 0; i < S1; i++)
            if (!visited[i])
            {
                cnt = 0;
                dfs1(i);
                if (cnt >= K)
                {
                    crosses_win = true;
                    break;
                }
            }
        bool noughts_win = false;
        memset(visited, 0, S2 * sizeof(int));
        for (int i = 0; i < S2; i++)
            if (!visited[i])
            {
                cnt = 0;
                dfs2(i);
                if (cnt >= K)
                {
                    noughts_win = true;
                    break;
                }
            }

        cout << "Case " << t << ": ";
        if (crosses_win && noughts_win) cout << "error\n";
        else if (crosses_win) cout << "crosses\n";
        else if (noughts_win) cout << "noughts\n";
        else cout << "none\n";
    }

    return 0;
}
