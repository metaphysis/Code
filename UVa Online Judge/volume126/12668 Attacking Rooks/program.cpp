// Attacking Rooks
// UVa ID: 12668
// Verdict: Accepted
// Submission Date: 2023-04-23
// UVa Run Time: 0.040s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10100, INF = 0x7f7f7f7f;

struct edge { int v, nxt; } g[100010];

int cnt, head[MAXV];
int xs[110][110], ys[110][110];
int visited[MAXV], cx[MAXV], cy[MAXV], dx[MAXV], dy[MAXV];
int tx, ty;

int bfs() {
    int dist = INF;
    memset(dx, -1, sizeof(dx));
    memset(dy, -1, sizeof(dy));
    queue<int> q;
    for (int i = 1; i <= tx; i++)
        if (cx[i] == -1) {
            q.push(i);
            dx[i] = 0;
        }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dx[u] > dist) break;
        for (int i = head[u]; ~i; i = g[i].nxt) {
            int v = g[i].v;
            if (dy[v] == -1) {
                dy[v] = dx[u] + 1;
                if (cy[v] == -1) dist = dy[v];
                else {
                    dx[cy[v]] = dy[v] + 1;
                    q.push(cy[v]);
                }
            }
        }
    }
    return dist != INF;
}

int dfs(int u) {
    int dist = INF;
    for (int i = head[u]; ~i; i = g[i].nxt) {
        int v = g[i].v;
        if (!visited[v] && dy[v] == (dx[u] + 1)) {
            visited[v] = 1;
            if (cy[v] != -1 && dy[v] == dist) continue;
            if (cy[v] == -1 || dfs(cy[v])) {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int hopcroftKarp() {
    int matches = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    while (bfs()) {
        memset(visited, 0, sizeof(visited));
        for (int i = 1; i <= tx; i++)
            if (cx[i] == -1)
                matches += dfs(i);
    }
    return matches;
}

char board[110][110];
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> board[i][j];
        int counter = 0;
        memset(xs, 0, sizeof xs);
        memset(ys, 0, sizeof ys);
        for (int i = 0; i < n; i++) {
            int block = 0;
            for (int j = 0; j < n; j++) {
                if (board[i][j] == '.') {
                    if (!block) counter++;
                    xs[i][j] = counter;
                    block = 1;
                } else block = 0;
            }
        }
        tx = counter;
        for (int j = 0; j < n; j++) {
            int block = 0;
            for (int i = 0; i < n; i++) {
                if (board[i][j] == '.') {
                    if (!block) counter++;
                    ys[i][j] = counter;
                    block = 1;
                } else block = 0;
            }
        }
        cnt = 0;
        memset(head, -1, sizeof head);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (xs[i][j]) {
                    g[cnt] = edge{ys[i][j], head[xs[i][j]]};
                    head[xs[i][j]] = cnt++;
                }
        cout << hopcroftKarp() << '\n';
    }
    return 0;
}
