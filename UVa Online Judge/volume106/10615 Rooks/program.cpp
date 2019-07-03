// Rooks
// UVa ID: 10615
// Verdict: Wrong Answer
// Submission Date: 2019-07-02
// UVa Run Time: 0.120s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;

int tx, ty;
int g[MAXN][MAXN], visited[MAXN], cx[MAXN], cy[MAXN];

int dfs(int u)
{
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v]) {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v])) {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    return 0;
}

int hungarian()
{
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    int matches = 0;
    for (int i = 0; i < tx; i++)
        if (cx[i] == -1) {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n, cases, board[MAXN][MAXN];

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        cin >> n;

        tx = ty = n;
        memset(g, 0, sizeof(g));

        char c;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                cin >> c;
                board[i][j] = 0;
                if (c == '*') g[i][j]++;
            }

        int colors = 0;
        while (hungarian()) {
            colors++;
            for (int i = 0; i < n; i++)
                if (cx[i] != -1) {
                    board[i][cx[i]] = colors;
                    g[i][cx[i]]--;
                }
        }

        cout << colors << '\n';
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j) cout << ' ';
                cout << board[i][j];
            }
            cout << '\n';
        }
    }

    return 0;
}
