#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = (1LL << 60);

struct Edge {
    int to, rev;
    ll cap, flow, cost;
};

struct CirNet {
    int n;
    vector<vector<Edge> > g;

    CirNet(int n) : n(n), g(n) {}

    int addEdge(int u, int v, ll cap, ll low, ll cost) {
        int id = (int)g[u].size();
        int rid = (int)g[v].size();
        Edge e1 = {v, rid, cap, 0, cost};
        Edge e2 = {u, id, -low, 0, -cost};
        g[u].push_back(e1);
        g[v].push_back(e2);
        return id;
    }

    void addFlow(int u, int id, ll val) {
        Edge &e = g[u][id];
        e.flow += val;
        g[e.to][e.rev].flow -= val;
    }

    void negCycle() {
        while (true) {
            vector<ll> dis(n, 0);
            vector<int> preV(n, -1), preE(n, -1);
            int last = -1;
            for (int it = 0; it < n; it++) {
                last = -1;
                for (int u = 0; u < n; u++) {
                    for (int i = 0; i < (int)g[u].size(); i++) {
                        Edge &e = g[u][i];
                        if (e.flow >= e.cap)
                            continue;
                        if (dis[e.to] > dis[u] + e.cost) {
                            dis[e.to] = dis[u] + e.cost;
                            preV[e.to] = u;
                            preE[e.to] = i;
                            last = e.to;
                        }
                    }
                }
                if (last == -1)
                    break;
            }
            if (last == -1)
                break;
            int v = last;
            for (int i = 0; i < n; i++) {
                if (preV[v] == -1) {
                    v = -1;
                    break;
                }
                v = preV[v];
            }
            if (v == -1)
                break;
            int start = v;
            vector<pair<int, int> > cyc;
            do {
                int u = preV[v];
                int id = preE[v];
                if (u == -1 || id == -1) {
                    cyc.clear();
                    break;
                }
                cyc.push_back(make_pair(u, id));
                v = u;
            } while (v != start);
            if (cyc.empty())
                break;
            ll add = INF, cst = 0;
            for (size_t i = 0; i < cyc.size(); i++) {
                int u = cyc[i].first;
                int id = cyc[i].second;
                Edge &e = g[u][id];
                add = min(add, e.cap - e.flow);
                cst += e.cost;
            }
            if (add <= 0 || cst >= 0)
                break;
            for (size_t i = 0; i < cyc.size(); i++) {
                int u = cyc[i].first;
                int id = cyc[i].second;
                addFlow(u, id, add);
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc, jNum, cNum;
    cin >> tc;
    for (int cs = 1; cs <= tc; cs++) {
        cin >> jNum >> cNum;
        vector<ll> need(cNum + 1);
        for (int i = 1; i <= cNum; i++)
            cin >> need[i];
        vector<int> left(jNum + 1), right(jNum + 1);
        vector<ll> fee(jNum + 1);
        for (int i = 1; i <= jNum; i++)
            cin >> left[i] >> right[i] >> fee[i];
        vector<bool> dead(jNum + 1, false);
        for (int i = 1; i <= jNum; i++) {
            for (int j = 1; j <= jNum; j++) {
                if (i == j || dead[j])
                    continue;
                if (fee[i] <= fee[j] && left[i] <= left[j] && right[j] <= right[i])
                    dead[j] = true;
            }
        }
        CirNet net(cNum + 2);
        vector<int> scEdge(cNum + 1), juEdge(jNum + 1);
        for (int i = 1; i <= jNum; i++) {
            if (dead[i])
                continue;
            juEdge[i] = net.addEdge(right[i] + 1, left[i], INF, 0, fee[i]);
        }
        for (int i = 1; i <= cNum; i++)
            scEdge[i] = net.addEdge(i, i + 1, INF, need[i], 0);
        vector<ll> score(cNum + 1, 0);
        for (int i = 1; i <= jNum; i++) {
            if (dead[i])
                continue;
            ll add = 0;
            for (int k = left[i]; k <= right[i]; k++)
                add = max(add, need[k] - score[k]);
            if (add <= 0)
                continue;
            net.addFlow(right[i] + 1, juEdge[i], add);
            for (int k = left[i]; k <= right[i]; k++) {
                net.addFlow(k, scEdge[k], add);
                score[k] += add;
            }
        }
        net.negCycle();
        cout << "Case " << cs << ":";
        for (int i = 1; i <= jNum; i++) {
            if (dead[i]) {
                cout << " 0";
                continue;
            }
            cout << " " << net.g[right[i] + 1][juEdge[i]].flow;
        }
        cout << '\n';
    }
    return 0;
}
