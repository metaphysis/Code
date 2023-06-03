// Matrix Decompressing
// UVa ID: 11082
// Verdict: Accepted
// Submission Date: 2023-05-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
struct arc { int u, v, capacity, residual, next; };
class Dinic {
private:
    arc *arcs;
    int vertices, source, sink, idx, *head, *dist, *current;
    bool bfs() {
        memset(dist, -1, sizeof(int) * vertices);
        queue<int> q;
        q.push(source);
        dist[source] = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == sink) break;
            for (int i = head[u]; ~i; i = arcs[i].next)
                if (arcs[i].residual > 0 && dist[arcs[i].v] < 0) {
                    dist[arcs[i].v] = dist[u] + 1;
                    q.push(arcs[i].v);
                }
        }
        return dist[sink] > 0;
    }
    int dfs(int u, int flow) {
        if (u == sink) return flow;
        for (int &i = current[u]; ~i; i = arcs[i].next) {
            int v = arcs[i].v, r = arcs[i].residual;
            if (dist[v] == (dist[u] + 1) && r > 0) {
                int volume = dfs(v, min(r, flow));
                if (volume > 0) {
                    arcs[i].residual -= volume;
                    arcs[i ^ 1].residual += volume;
                    return volume;
                }
            }
        }
        return 0;
    }
public:
    Dinic(int v, int e, int s, int t) {
        arcs = new arc[e];
        vertices = v;
        source = s, sink = t;
        idx = 0, head = new int[v], dist = new int[v], current = new int[v];
        memset(head, -1, sizeof(int) * v);
    }
    ~Dinic() { delete [] arcs, head, dist, current; }
    void addArc(int u, int v, int capacity) {
        arcs[idx] = (arc){u, v, capacity, capacity, head[u]};
        head[u] = idx++;
        arcs[idx] = (arc){v, u, capacity, 0, head[v]};
        head[v] = idx++;
    }
    int maxFlow(int r, int c) {
        int flow = 0;
        while (bfs()) {
            for (int i = 0; i < vertices; i++) current[i] = head[i];
            while (int delta = dfs(source, INF))
                flow += delta;
        }
        int matrix[32][32] = {};
        for (int i = 0; i < idx; i++) 
            if (1 <= arcs[i].u && arcs[i].u <= r && r + 1 <= arcs[i].v && arcs[i].v <= r + c)
                matrix[arcs[i].u - 1][arcs[i].v - 1 - r] = arcs[i].capacity - arcs[i].residual + 1;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (j) cout << ' ';
                cout << matrix[i][j];
            }
            cout << '\n';
        }
        return flow;
    }
};
int crs[32], ccs[32];
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    for (int cs = 0; cs < T; cs++) {
        int R, C;
        cin >> R >> C;
        int source = 0, sink = R + C + 1;
        Dinic dinic(50, 10000, source, sink);
        for (int i = 1; i <= R; i++) cin >> crs[i];
        for (int i = 1; i <= C; i++) cin >> ccs[i];
        for (int i = R; i >= 1; i--) crs[i] -= crs[i - 1];
        for (int i = C; i >= 1; i--) ccs[i] -= ccs[i - 1];
        for (int i = 1; i <= R; i++) dinic.addArc(source, i, crs[i]);
        for (int i = 1; i <= C; i++) dinic.addArc(R + i, sink, ccs[i]);
        for (int i = 1; i <= R; i++) dinic.addArc(i, sink, C);
        for (int i = 1; i <= C; i++) dinic.addArc(source, R + i, R);
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                dinic.addArc(i, R + j, min(19, crs[i] - C));
        if (cs) cout << '\n';
        cout << "Matrix " << cs + 1 << '\n';
        dinic.maxFlow(R, C);
    }
    return 0;
}
