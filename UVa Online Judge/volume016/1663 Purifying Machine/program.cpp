// Purifying Machine
// UVa ID: 1663
// Verdict: Accepted
// Submission Date: 2019-07-06
// UVa Run Time: 0.410s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1100;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], tx, ty;

int dfs(int u)
{
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v])
        {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))
            {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    return 0;
}

int hungarian()
{
    int matches = 0;
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    for (int i = 0; i < tx; i++)
        if (cx[i] == -1)
        {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N, M, cheeses[1100];
    while (cin >> N >> M)
    {
        if (N == 0) break;

        string bits;
        memset(cheeses, 0, sizeof(cheeses));
        for (int i = 0; i < M; i++)
        {
            cin >> bits;
            int c0 = 0, c1 = 0;
            for (int j = 0; j < bits.length(); j++)
            {
                if (bits[j] == '*')
                {
                    c0 = c0 * 2;
                    c1 = c1 * 2 + 1;
                }
                else
                {
                    c0 = c0 * 2 + (bits[j] - '0');
                    c1 = c1 * 2 + (bits[j] - '0');
                }
            }
            cheeses[c0] = cheeses[c1] = 1;
        }

        vector<int> infected;
        for (int i = 0; i < (1 << N); i++)
            if (cheeses[i])
                infected.push_back(i);
        
        tx = ty = infected.size();
        for (int i = 0; i < tx; i++)
            for (int j = 0; j < ty; j++)
                g[i][j] = __builtin_popcount(infected[i] ^ infected[j]) == 1;

        int matched = hungarian();
        cout << (infected.size() - matched / 2) << '\n';
    }

    return 0;
}
