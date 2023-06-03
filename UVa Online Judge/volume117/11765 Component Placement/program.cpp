// Component Placement
// UVa ID: 11765
// Verdict: Accepted
// Submission Date: 2023-06-03
// UVa Run Time: 0.060s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x7f7f7f7f;

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

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    int top[256], bottom[256], n, m;
    while (T--) {
        cin >> n >> m;
        int source = 0, sink = n + 1;
        Dinic dinic(256, 100000, source, sink);
        for (int i = 1; i <= n; i++) cin >> top[i];
        for (int i = 1; i <= n; i++) cin >> bottom[i];
        for (int i = 1, flag; i <= n; i++) {
            cin >> flag;
            if (flag == 0) {
                dinic.addArc(source, i, top[i]);
                dinic.addArc(i, sink, bottom[i]);
            } else if (flag == 1) {
                dinic.addArc(source, i, top[i]);
                dinic.addArc(i, sink, INF);
            } else {
                dinic.addArc(source, i, INF);
                dinic.addArc(i, sink, bottom[i]);
            }
        }
        for (int i = 1, p, q, r; i <= m; i++) {
            cin >> p >> q >> r;
            dinic.addArc(p, q, r);
            dinic.addArc(q, p, r);
        }
        
        cout << dinic.maxFlow() << '\n';
    }
    return 0;
}
