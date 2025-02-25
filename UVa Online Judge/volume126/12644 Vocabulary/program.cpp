// Vocabulary
// UVa ID: 12644
// Verdict: Accepted
// Submission Date: 2023-04-23
// UVa Run Time: 0.110s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge { int v, nxt; } g[260000];
int V, C, cnt, cx[1010], cy[1010], head[1010], visited[1010];
string w;
int dx[510][32], dy[510][32];
bool matched(int i, int j) {
    for (int k = 0; k < 26; k++)
        if (dx[i][k] < dy[j][k])
            return false;
    return true;
}
int dfs(int u) {
    for (int i = head[u], v; ~i; i = g[i].nxt) {
        v = g[i].v;
        if (!visited[v]) {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v])) {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    }
    return 0;
}
int hungarian() {
    memset(cx, -1, sizeof cx);
    memset(cy, -1, sizeof cy);
    int matches = 0;
    for (int i = 0; i < V; i++)
        if (cx[i] == -1) {
            memset(visited, 0, sizeof visited);
            matches += dfs(i);
        }
    return matches;
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> V >> C) {
        cnt = 0;
        memset(head, -1, sizeof head);
        memset(dx, 0, sizeof dx);
        memset(dy, 0, sizeof dy);
        for (int i = 0; i < V; i++) {
            cin >> w;
            for (auto c : w) dx[i][c - 'a']++;
        }
        for (int i = 0; i < C; i++) {
            cin >> w;
            for (auto c : w) dy[i][c - 'a']++;
        }
        for (int i = 0; i < V; i++)
            for (int j = 0; j < C; j++)
                if (matched(i, j)) {
                    g[cnt] = edge{V + j, head[i]};
                    head[i] = cnt++;
                    g[cnt] = edge{i, head[V + j]};
                    head[V + j] = cnt++;
                }
        cout << hungarian() << '\n';    
    }
    return 0;
}
