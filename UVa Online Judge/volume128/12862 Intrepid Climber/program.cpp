// Intrepid Climber
// UVa ID: 12862
// Verdict: Accepted
// Submission Date: 2023-05-01
// UVa Run Time: 0.300s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
const int MAXN = 100010;
struct edge { int v, w, nxt; } g[MAXN];
int d[MAXN];
bool cmp(int a, int b) { return d[a] > d[b]; }
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int N, F;
    int c[MAXN], visited[MAXN], head[MAXN], cnt;
    pair<int, int> p[MAXN];
    while (cin >> N >> F) {
        memset(c, 0x3f, sizeof c);
        memset(head, -1, sizeof head);
        cnt = 0;
        for (int i = 1, u, v, w; i < N; i++) {
            cin >> u >> v >> w;
            g[cnt] = edge{v, w, head[u]};
            head[u] = cnt++;
        }
        queue<int> q;
        q.push(1);
        c[1] = 0, d[1] = 0;
        p[1] = make_pair(-1, -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = head[u]; ~i; i = g[i].nxt) {
                p[g[i].v] = make_pair(u, g[i].w);
                c[g[i].v] = c[u] + g[i].w;
                d[g[i].v] = d[u] + 1;
                q.push(g[i].v);
            }
        }
        memset(visited, 0, sizeof visited);
        int sum = 0, mc = 0;
        vector<int> nds;
        for (int i = 0, f; i < F; i++) {
            cin >> f;
            nds.push_back(f);
        }
        sort(nds.begin(), nds.end(), cmp);
        visited[1] = 1;
        for (auto f : nds) {
            mc = max(mc, c[f]);
            if (visited[f]) continue;
            while (true) {
                sum += p[f].second;
                visited[f] = 1;
                if (visited[p[f].first]) break;
                f = p[f].first;
            }
        }
        sum -= mc;
        cout << sum << '\n';
    }
    return 0;
}
