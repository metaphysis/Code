// Duopoly
// UVa ID: 1212
// Verdict: Accepted
// Submission Date: 2023-01-22
// UVa Run Time: 0.030s
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
    int T, N, M;
    string line;
    cin >> T;
    int used[300100];
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case " << cs << ":\n";
        memset(used, 0, sizeof used);
        Dinic dinic(6100, 1000010, 0, 6001);
        int s = 0, p, c;
        cin >> N;
        cin.ignore(256, '\n');
        for (int i = 1; i <= N; i++) {
            getline(cin, line);
            istringstream iss(line);
            iss >> p; s += p;
            dinic.addArc(0, i, p);
            while (iss >> c) used[c] = i;
        }
        cin >> M;
        cin.ignore(256, '\n');
        for (int i = 1; i <= M; i++) {
            getline(cin, line);
            istringstream iss(line);
            iss >> p; s += p;
            dinic.addArc(N + i, 6001, p);
            while (iss >> c) {
                if (used[c]) dinic.addArc(used[c], N + i, INF);
            }
        }
        cout << s - dinic.maxFlow() << '\n';
        if (cs < T) cout << '\n';
    }
    return 0;
}
