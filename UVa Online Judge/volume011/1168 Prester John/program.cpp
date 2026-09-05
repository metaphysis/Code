#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, id;
};

struct Graph {
    int n, tar;
    vector<vector<Edge> > adj;
};

int getId(const string &str, map<string, int> &idMap, int &idCnt) {
    map<string, int>::iterator it = idMap.find(str);
    if (it != idMap.end()) return it->second;
    idMap[str] = idCnt;
    return idCnt++;
}

Graph readGraph(map<string, int> &idMap, int &idCnt) {
    Graph g;
    int p, u, v;
    string str;
    cin >> g.n >> g.tar >> p;
    g.adj.resize(g.n);
    for (int i = 0; i < p; i++) {
        cin >> u >> str >> v;
        int id = getId(str, idMap, idCnt);
        g.adj[u].push_back({v, id});
    }
    for (int i = 0; i < g.n; i++) {
        sort(g.adj[i].begin(), g.adj[i].end(), [](const Edge &a, const Edge &b) {
            return a.id < b.id;
        });
    }
    return g;
}

long long getKey(int u, int v) {
    return (static_cast<long long>(u) << 32) | static_cast<unsigned int>(v);
}

int bfs(const Graph &a, const Graph &b) {
    queue<pair<int, int> > que;
    unordered_set<long long> vis;
    que.push(make_pair(0, 0));
    vis.insert(getKey(0, 0));
    int dis = 0;
    while (!que.empty()) {
        int sz = que.size();
        while (sz--) {
            int u = que.front().first, v = que.front().second;
            que.pop();
            if (u == a.tar && v == b.tar) return dis;
            const vector<Edge> &ea = a.adj[u];
            const vector<Edge> &eb = b.adj[v];
            int i = 0, j = 0;
            while (i < static_cast<int>(ea.size()) && j < static_cast<int>(eb.size())) {
                if (ea[i].id < eb[j].id) {
                    i++;
                } else if (ea[i].id > eb[j].id) {
                    j++;
                } else {
                    int ni = i, nj = j, id = ea[i].id;
                    while (ni < static_cast<int>(ea.size()) && ea[ni].id == id) ni++;
                    while (nj < static_cast<int>(eb.size()) && eb[nj].id == id) nj++;
                    for (int x = i; x < ni; x++) {
                        for (int y = j; y < nj; y++) {
                            int nu = ea[x].to, nv = eb[y].to;
                            long long key = getKey(nu, nv);
                            if (vis.insert(key).second) que.push(make_pair(nu, nv));
                        }
                    }
                    i = ni;
                    j = nj;
                }
            }
        }
        dis++;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 0; tc < t; tc++) {
        map<string, int> idMap;
        int idCnt = 0;
        Graph a = readGraph(idMap, idCnt);
        Graph b = readGraph(idMap, idCnt);
        if (tc) cout << '\n';
        cout << bfs(a, b) << '\n';
    }
    return 0;
}
