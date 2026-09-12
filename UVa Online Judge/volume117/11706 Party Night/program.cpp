#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int> > adj;
vector<vector<int> > clqs;

vector<int> getInter(const vector<int> &a, const vector<int> &b) {
    vector<int> res;
    for (int x : a)
        if (adj[x][b[0]] || find(b.begin(), b.end(), x) != b.end())
            res.push_back(x);
    return res;
}

vector<int> getCommon(const vector<int> &a, int v) {
    vector<int> res;
    for (int x : a)
        if (adj[v][x])
            res.push_back(x);
    return res;
}

int getPivot(const vector<int> &p, const vector<int> &x) {
    int pivot = -1, best = -1;
    vector<int> all = p;
    for (int v : x)
        all.push_back(v);
    for (int u : all) {
        int cnt = 0;
        for (int v : p)
            if (adj[u][v])
                ++cnt;
        if (cnt > best) {
            best = cnt;
            pivot = u;
        }
    }
    return pivot;
}

void bronKerbosch(vector<int> r, vector<int> p, vector<int> x) {
    if (p.empty() && x.empty()) {
        clqs.push_back(r);
        return;
    }
    int pivot = getPivot(p, x);
    vector<int> cand;
    for (int v : p)
        if (pivot == -1 || !adj[pivot][v])
            cand.push_back(v);
    for (int v : cand) {
        vector<int> nr = r;
        nr.push_back(v);
        vector<int> np, nx;
        for (int u : p)
            if (adj[v][u])
                np.push_back(u);
        for (int u : x)
            if (adj[v][u])
                nx.push_back(u);
        bronKerbosch(nr, np, nx);
        p.erase(find(p.begin(), p.end(), v));
        x.push_back(v);
    }
}

bool check() {
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (adj[i][j]) {
                int cnt = 0;
                for (const vector<int> &c : clqs) {
                    bool hasI = find(c.begin(), c.end(), i) != c.end();
                    bool hasJ = find(c.begin(), c.end(), j) != c.end();
                    if (hasI && hasJ)
                        ++cnt;
                }
                if (cnt != 1)
                    return false;
            }
    vector<vector<int> > belong(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < (int)clqs.size(); ++j)
            if (find(clqs[j].begin(), clqs[j].end(), i) != clqs[j].end())
                belong[i].push_back(j);
    int nodeCnt = clqs.size();
    vector<vector<int> > graph(nodeCnt);
    for (int i = 0; i < n; ++i) {
        if (belong[i].empty()) {
            int a = nodeCnt++, b = nodeCnt++;
            graph.resize(nodeCnt);
            graph[a].push_back(b);
            graph[b].push_back(a);
        } else if (belong[i].size() == 1) {
            int a = belong[i][0], b = nodeCnt++;
            graph.resize(nodeCnt);
            graph[a].push_back(b);
            graph[b].push_back(a);
        } else if (belong[i].size() == 2) {
            int a = belong[i][0], b = belong[i][1];
            graph[a].push_back(b);
            graph[b].push_back(a);
        } else {
            return false;
        }
    }
    vector<int> color(nodeCnt, -1);
    for (int i = 0; i < nodeCnt; ++i) {
        if (color[i] != -1)
            continue;
        color[i] = 0;
        queue<int> que;
        que.push(i);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (int v : graph[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    que.push(v);
                } else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n) {
        if (n == 0)
            break;
        int m;
        cin >> m;
        adj.assign(n, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u][v] = adj[v][u] = 1;
        }
        clqs.clear();
        vector<int> r, p, x;
        for (int i = 0; i < n; ++i)
            p.push_back(i);
        bronKerbosch(r, p, x);
        cout << (check() ? "YES" : "NO") << '\n';
    }
    return 0;
}
