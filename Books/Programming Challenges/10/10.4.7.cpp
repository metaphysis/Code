const int MAXV = 1010, MAXE = 100010, INF = 0x3f3f3f3f;

int n, m;
int cnt, head[MAXV];
int dist[MAXV], visited[MAXV];

struct edge { int v, w, next; } g[MAXE];
struct state {
    int u, fx;
    bool operator < (const state &s) const { return fx > s.fx; }
};

void clearEdge() {
    cnt = 0;
    memset(head, -1, sizeof head);
}

void addEdge(int u, int v, int w) {
    g[cnt] = edge{v, w, head[u]};
    head[u] = cnt++;
}

int ksp(vector<tuple<int, int, int>> &data, int s, int t, int k) {
    clearEdge();
    for (auto d : data) addEdge(get<1>(d), get<0>(d), get<2>(d));

    for (int i = 0; i < n; i++) dist[i] = INF, visited[i] = 0;
    int u = t;
    dist[u] = 0;
    while (!visited[u]) {
        visited[u] = 1;
        for (int i = head[u]; ~i; i = g[i].next)
            if (!visited[g[i].v] && dist[g[i].v] > dist[u] + g[i].w)
                dist[g[i].v] = dist[u] + g[i].w;
        int least = INF;
        for (int i = 0; i < n; i++)
            if (!visited[i] && dist[i] < least)
                least = dist[i], u = i;
            
    }
    if (dist[s] == INF) return -1;

    clearEdge();
    for (auto d : data) addEdge(get<0>(d), get<1>(d), get<2>(d));

    int lastPathLength = -INF;
    priority_queue<state> q;
    q.push(state{s, dist[s]});
    while (!q.empty()) {
        state ste = q.top(); q.pop();
        int walked = ste.fx - dist[ste.u];
        if (ste.u == t && walked > lastPathLength) {
            lastPathLength = walked;
            if (!(--k)) return walked;
        }
        for (int i = head[ste.u]; ~i; i = g[i].next)
            q.push(state{g[i].v, walked + g[i].w + dist[g[i].v]});
    }
    return -1;
}
