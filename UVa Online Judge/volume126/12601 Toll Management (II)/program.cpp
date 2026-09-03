#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);

struct Edge {
    int u, v;
    long long cost;
};

struct Dsu {
    vector<int> parent, rankVal;
    Dsu(int n) {
        parent.resize(n);
        rankVal.assign(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    void reset(int x) {
        parent[x] = x;
        rankVal[x] = 0;
    }
    int findRoot(int x) {
        if (parent[x] == x)
            return x;
        return parent[x] = findRoot(parent[x]);
    }
    bool unite(int x, int y) {
        x = findRoot(x);
        y = findRoot(y);
        if (x == y)
            return false;
        if (rankVal[x] < rankVal[y])
            swap(x, y);
        parent[y] = x;
        if (rankVal[x] == rankVal[y])
            rankVal[x]++;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        int n, m;
        cin >> n >> m;
        vector<int> p(n);
        for (int i = 0; i < n; i++)
            cin >> p[i];
        cout << "Case " << caseId << ": ";
        if (p[0] != 0) {
            for (int i = 0; i < m; i++) {
                int u, v, w;
                cin >> u >> v >> w;
            }
            cout << "Bad King\n";
            continue;
        }
        vector<pair<int, int>> order;
        for (int i = 0; i < n; i++)
            order.push_back({p[i], i});
        sort(order.begin(), order.end());
        vector<int> groupId(n);
        vector<vector<int>> groups;
        for (int i = 0; i < n; i++) {
            if (i == 0 || order[i].first != order[i - 1].first)
                groups.push_back(vector<int>());
            int id = static_cast<int>(groups.size()) - 1;
            groupId[order[i].second] = id;
            groups[id].push_back(order[i].second);
        }
        vector<vector<Edge>> groupEdges(groups.size());
        vector<long long> rootCost(n, inf);
        long long answer = 0;
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            long long diff = llabs(static_cast<long long>(p[u]) - p[v]);
            answer += max(0LL, diff - w);
            long long extra = max(0LL, static_cast<long long>(w) - diff);
            if (p[u] == p[v]) {
                groupEdges[groupId[u]].push_back({u, v, extra});
            } else {
                if (p[u] > p[v])
                    swap(u, v);
                rootCost[v] = min(rootCost[v], extra);
            }
        }
        bool possible = true;
        Dsu dsu(n + 1);
        int superNode = n;
        for (int group = 0; group < static_cast<int>(groups.size()); group++) {
            vector<Edge> edges = groupEdges[group];
            for (int vertex : groups[group]) {
                if (rootCost[vertex] < inf)
                    edges.push_back({vertex, superNode, rootCost[vertex]});
                if (vertex == 0)
                    edges.push_back({vertex, superNode, 0});
                dsu.reset(vertex);
            }
            dsu.reset(superNode);
            sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
                return a.cost < b.cost;
            });
            long long groupAnswer = 0;
            int used = 0;
            for (const Edge &edge : edges) {
                if (dsu.unite(edge.u, edge.v)) {
                    groupAnswer += edge.cost;
                    used++;
                    if (used == static_cast<int>(groups[group].size()))
                        break;
                }
            }
            if (used != static_cast<int>(groups[group].size())) {
                possible = false;
                break;
            }
            answer += groupAnswer;
        }
        if (possible)
            cout << answer << '\n';
        else
            cout << "Bad King\n";
    }
    return 0;
}
