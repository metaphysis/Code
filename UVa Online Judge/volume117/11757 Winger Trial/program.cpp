// Winger Trial
// UVa ID: 11757
// Verdict: Accepted
// Submission Date: 2023-06-03
// UVa Run Time: 0.010s
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
    int maxFlow() {
        int flow = 0;
        while (bfs()) {
            for (int i = 0; i < vertices; i++) current[i] = head[i];
            while (int delta = dfs(source, INF))
                flow += delta;
        }
        return flow;
    }
};
int crs[32], ccs[32];
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int L, W, N, d;
    int xi[128], yi[128];
    int cases = 1;
    while (cin >> L >> W >> N >> d, L) {
        int source = 0, sink = 2 * N + 1;
        Dinic dinic(256, 10000, source, sink);
        for (int i = 1; i <= N; i++) cin >> xi[i] >> yi[i];
        for (int i = 1; i <= N; i++) {
            dinic.addArc(i, i + N, 1);
            if (yi[i] <= d) dinic.addArc(source, i, 1);
            if (yi[i] + d >= W) dinic.addArc(i + N, sink, 1);
            for (int j = i + 1; j <= N; j++)
                if ((xi[i] - xi[j]) * (xi[i] - xi[j]) + (yi[i] - yi[j]) * (yi[i] - yi[j]) <= 4 * d * d) {
                    dinic.addArc(i + N, j, 1);
                    dinic.addArc(j + N, i, 1);
                }
        }
        cout << "Case " << cases++ << ": ";
        cout << dinic.maxFlow() << '\n';
    }
    return 0;
}
