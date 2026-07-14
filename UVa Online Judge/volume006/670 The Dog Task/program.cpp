// The Dog Task
// UVa ID: 670
// Verdict: Accepted
// Submission Date: 2016-11-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 110;
const double EPSILON = 1e-20;

struct point { int x, y; };

point bob[MAXV], dog[MAXV];
int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], L, N, M;

bool accessible(point a, point b, point c) {
    double distAB = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    double distAC = sqrt(pow(a.x - c.x, 2) + pow(a.y - c.y, 2));
    double distBC = sqrt(pow(b.x - c.x, 2) + pow(b.y - c.y, 2));
    return distAC + distBC < 2.0 * distAB - EPSILON;
}

int dfs(int u) {
    for (int v = 0; v < M; v++)
        if (g[u][v] && !visited[v]) {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v])) {
                cx[u] = v;
                cy[v] = u;
                return 1;
            }
        }
    return 0;
}

int hungarian() {
    int matches = 0;
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    for (int i = 0; i < N; i++)
        if (cx[i] == -1) {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}

int main() {
    cin >> L;
    for (int cases = 1; cases <= L; cases++) {
        if (cases > 1) cout << '\n';
        cin >> N >> M;
        for (int i = 0; i < N; i++) cin >> bob[i].x >> bob[i].y;
        for (int i = 0; i < M; i++) cin >> dog[i].x >> dog[i].y;
        memset(g, 0, sizeof(g));
        for (int i = 0; i < N - 1; i++)
            for (int j = 0; j < M; j++)
                if (accessible(bob[i], bob[i + 1], dog[j]))
                    g[i][j] = 1;
        cout << (N + hungarian()) << '\n';
        for (int i = 0; i < N - 1; i++) {
            cout << bob[i].x << ' ' << bob[i].y << ' ';
            if (cx[i] >= 0)
                cout << dog[cx[i]].x << ' ' << dog[cx[i]].y << ' ';
        }
        cout << bob[N - 1].x << ' ' << bob[N - 1].y << '\n';
    }
    return 0;
}
