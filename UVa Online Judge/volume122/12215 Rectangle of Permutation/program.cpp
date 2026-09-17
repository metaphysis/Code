#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev;
    long long cap;
};

class Dinic {
public:
    vector<vector<Edge>> graph;
    vector<int> level, ptr;
    Dinic(int n) : graph(n), level(n), ptr(n) {}
    int addEdge(int u, int v, long long cap) {
        int id = graph[u].size();
        Edge a = {v, (int)graph[v].size(), cap};
        Edge b = {u, (int)graph[u].size(), 0};
        graph[u].push_back(a);
        graph[v].push_back(b);
        return id;
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (Edge &e : graph[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    que.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }
    long long dfs(int u, int t, long long flow) {
        if (u == t) return flow;
        for (int &i = ptr[u]; i < (int)graph[u].size(); i++) {
            Edge &e = graph[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                long long got = dfs(e.to, t, min(flow, e.cap));
                if (got > 0) {
                    e.cap -= got;
                    graph[e.to][e.rev].cap += got;
                    return got;
                }
            }
        }
        return 0;
    }
    long long maxFlow(int s, int t) {
        long long total = 0, pushed;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while ((pushed = dfs(s, t, (long long)1e18)) > 0)
                total += pushed;
        }
        return total;
    }
    long long edgeFlow(int u, int id) {
        Edge &e = graph[u][id];
        return graph[e.to][e.rev].cap;
    }
};

bool makeFlow(int n, const vector<int> &a, const vector<int> &b, const vector<vector<int>> &c, int r, vector<vector<int>> &d) {
    int s = 0, colStart = 1, olStart = colStart + n, orStart = olStart + n, valStart = orStart + n, t = valStart + n;
    int nodeCnt = t + 1, inf = 1000000000;
    Dinic din(nodeCnt);
    vector<vector<int>> directId(n, vector<int>(n)), overId(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        din.addEdge(s, colStart + i, r);
        din.addEdge(colStart + i, olStart + i, a[i]);
        din.addEdge(orStart + i, valStart + i, b[i]);
        din.addEdge(valStart + i, t, r);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            directId[i][j] = din.addEdge(colStart + i, valStart + j, c[i][j]);
            overId[i][j] = din.addEdge(olStart + i, orStart + j, inf);
        }
    }
    if (din.maxFlow(s, t) != 1LL * n * r) return false;
    d.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = din.edgeFlow(colStart + i, directId[i][j]) + din.edgeFlow(olStart + i, overId[i][j]);
        }
    }
    return true;
}

bool matchDfs(int u, int n, vector<vector<int>> &d, vector<int> &mt, vector<int> &vis) {
    for (int v = 0; v < n; v++) {
        if (d[u][v] == 0 || vis[v]) continue;
        vis[v] = 1;
        if (mt[v] == -1 || matchDfs(mt[v], n, d, mt, vis)) {
            mt[v] = u;
            return true;
        }
    }
    return false;
}

vector<int> getPermutation(int n, vector<vector<int>> &d) {
    vector<int> mt(n, -1), ans(n, -1);
    for (int i = 0; i < n; i++) {
        vector<int> vis(n, 0);
        matchDfs(i, n, d, mt, vis);
    }
    for (int j = 0; j < n; j++)
        ans[mt[j]] = j;
    for (int i = 0; i < n; i++)
        d[i][ans[i]]--;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCnt;
    cin >> testCnt;
    for (int tc = 1; tc <= testCnt; tc++) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        vector<vector<int>> c(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < n; i++)
            cin >> b[i];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cin >> c[i][j];
        }
        int hi = 1000000000, lo = 0;
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = 0; j < n; j++)
                sum += c[i][j];
            hi = min(hi, sum + a[i]);
        }
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int i = 0; i < n; i++)
                sum += c[i][j];
            hi = min(hi, sum + b[j]);
        }
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            vector<vector<int>> tmp;
            if (makeFlow(n, a, b, c, mid, tmp)) lo = mid;
            else hi = mid - 1;
        }
        vector<vector<int>> d;
        makeFlow(n, a, b, c, lo, d);
        cout << "Case " << tc << ": " << lo << '\n';
        for (int k = 0; k < lo; k++) {
            vector<int> row = getPermutation(n, d);
            for (int i = 0; i < n; i++) {
                if (i) cout << ' ';
                cout << row[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
