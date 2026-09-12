#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    long long cap;
};

struct Dinic {
    int n;
    vector<vector<Edge>> g;
    vector<int> dep, cur;
    Dinic(int n) : n(n), g(n), dep(n), cur(n) {}
    void addEdge(int u, int v, long long cap) {
        Edge a = {v, (int)g[v].size(), cap};
        Edge b = {u, (int)g[u].size(), 0};
        g[u].push_back(a);
        g[v].push_back(b);
    }
    bool bfs(int s, int t) {
        fill(dep.begin(), dep.end(), -1);
        queue<int> q;
        dep[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (Edge &e : g[u]) {
                if (e.cap > 0 && dep[e.to] == -1) {
                    dep[e.to] = dep[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return dep[t] != -1;
    }
    long long dfs(int u, int t, long long f) {
        if (u == t) return f;
        for (int &i = cur[u]; i < (int)g[u].size(); i++) {
            Edge &e = g[u][i];
            if (e.cap > 0 && dep[e.to] == dep[u] + 1) {
                long long got = dfs(e.to, t, min(f, e.cap));
                if (got > 0) {
                    e.cap -= got;
                    g[e.to][e.rev].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }
    long long maxFlow(int s, int t) {
        long long ans = 0, inf = numeric_limits<long long>::max() / 4;
        while (bfs(s, t)) {
            fill(cur.begin(), cur.end(), 0);
            while (true) {
                long long got = dfs(s, t, inf);
                if (got == 0) break;
                ans += got;
            }
        }
        return ans;
    }
};

int m, n;
long long k, totalVip;
vector<long long> work, vip, reg;
vector<vector<int>> can;

bool check(long long time) {
    int s = 0, jobBeg = 1, workerBeg = jobBeg + m, t = workerBeg + n, ss = t + 1, tt = ss + 1;
    int nodes = tt + 1;
    long long inf = numeric_limits<long long>::max() / 4, need = 0;
    vector<long long> bal(nodes, 0);
    Dinic dinic(nodes);
    auto addBound = [&](int u, int v, long long low, long long high) {
        dinic.addEdge(u, v, high - low);
        bal[u] -= low;
        bal[v] += low;
    };
    for (int j = 0; j < m; j++) {
        addBound(s, jobBeg + j, vip[j], vip[j] + reg[j]);
        for (int id : can[j]) dinic.addEdge(jobBeg + j, workerBeg + id, inf);
    }
    for (int i = 0; i < n; i++) dinic.addEdge(workerBeg + i, t, time / work[i]);
    addBound(t, s, totalVip + k, totalVip + k);
    for (int i = 0; i <= t; i++) {
        if (bal[i] > 0) {
            dinic.addEdge(ss, i, bal[i]);
            need += bal[i];
        } else if (bal[i] < 0) dinic.addEdge(i, tt, -bal[i]);
    }
    return dinic.maxFlow(ss, tt) == need;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    for (int cs = 1; cs <= tc; cs++) {
        cin >> m >> n >> k;
        work.resize(n);
        for (int i = 0; i < n; i++) cin >> work[i];
        vip.resize(m);
        reg.resize(m);
        can.assign(m, {});
        totalVip = 0;
        for (int j = 0; j < m; j++) {
            int cnt;
            cin >> vip[j] >> reg[j] >> cnt;
            totalVip += vip[j];
            can[j].resize(cnt);
            for (int &id : can[j]) {
                cin >> id;
                id--;
            }
        }
        long long lo = -1, hi = 0, maxWork = *max_element(work.begin(), work.end());
        hi = (totalVip + k) * maxWork;
        while (lo + 1 < hi) {
            long long mid = (lo + hi) / 2;
            if (check(mid)) hi = mid;
            else lo = mid;
        }
        cout << "Case " << cs << ": " << hi << '\n';
    }
    return 0;
}
