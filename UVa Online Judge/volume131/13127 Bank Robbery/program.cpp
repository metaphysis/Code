// Bank Robbery
// UVa ID: 13127
// Verdict: Accepted
// Submission Date: 2023-04-05
// UVa Run Time: 0.780s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010, MAXE = 1000010, INF = 0x3f3f3f3f;

struct edge {
    int v, w, nxt;
} g[MAXE];

int N, M, B, P, D[MAXN][MAXN], C;

struct block {
    int v, w;
    bool operator<(const block &b) const { return w > b.w; }
};

int head[MAXN];

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> N >> M >> B >> P) {
        C = 0;
        for (int i = 0; i < N; i++) head[i] = -1;
        for (int i = 1, u, v, w; i <= M; i++) {
            cin >> u >> v >> w;
            g[C] = edge{v, w, head[u]};
            head[u] = C++;
            g[C] = edge{u, w, head[v]};
            head[v] = C++;
        }
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                D[i][j] = INF;
        vector<int> BB;
        for (int x = 1, u; x <= B; x++) {
            cin >> u;
            BB.push_back(u);
            D[u][u] = 0;
            priority_queue<block> q;
            q.push(block{u, 0});
            while (!q.empty()) {
                block b = q.top(); q.pop();
                if (D[u][b.v] < b.w) continue;
                for (int i = head[b.v]; ~i; i = g[i].nxt) {
                    if (D[u][g[i].v] > D[u][b.v] + g[i].w) {
                        D[u][g[i].v] = D[u][b.v] + g[i].w;
                        q.push(block{g[i].v, D[u][g[i].v]});
                    }
                }
            }
        }
        vector<int> PP;
        for (int i = 1, u; i <= P; i++) {
            cin >> u;
            PP.push_back(u);
        }
        vector<int> R;
        int E = 0;
        for (auto u : BB) {
            int r = INF;
            for (auto v : PP)
                r = min(r, D[u][v]);
            if (r >= E) {
                if (r > E) R.clear();
                E = r;
                R.push_back(u);
            }
        }
        cout << R.size() << ' ';
        if (E == INF) cout << '*';
        else cout << E;
        cout << '\n';
        sort(R.begin(), R.end());
        for (int i = 0; i < R.size(); i++)
            cout << R[i] << " \n"[i == R.size() - 1];
    }
    return 0;
}
