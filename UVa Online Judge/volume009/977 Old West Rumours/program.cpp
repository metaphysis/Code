// Old West Rumours
// UVa ID: 977
// Verdict: Accepted
// Submission Date: 2026-10-09
// UVa Run Time: 0.180s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

const int INF = 1000000000;

struct Edge {
    int to, time;
};

struct Label {
    ull mask;
    int time;
};

int townCnt, routeCnt, ans, reachCnt;

vector<int> stopTime, rumorTime;
vector<vector<int>> rumorDist, billyDist;
vector<vector<Edge>> graph;
vector<vector<Label>> labels;

bool isSuper(ull a, ull b) {
    return (a | b) == a;
}

void floyd(vector<vector<int>> &dist) {
    for (int k = 0; k < townCnt; ++k) {
        for (int i = 0; i < townCnt; ++i) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < townCnt; ++j) {
                if (dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

bool addLabel(ull mask, int town, int time) {
    vector<Label> &cur = labels[town];
    for (const Label &lb : cur) {
        if (isSuper(lb.mask, mask) && lb.time <= time) return false;
    }
    vector<Label> kept;
    kept.reserve(cur.size() + 1);
    for (const Label &lb : cur) {
        bool dom = isSuper(mask, lb.mask) && time <= lb.time;
        if (!dom) kept.push_back(lb);
    }
    kept.push_back({mask, time});
    cur.swap(kept);
    return true;
}

int upperBound(ull mask, int town, int time) {
    int bd = __builtin_popcountll(mask);
    for (int v = 0; v < townCnt; ++v) {
        ull bit = 1ULL << v;
        if (mask & bit) continue;
        if (rumorTime[v] == INF) continue;
        if (billyDist[town][v] == INF) continue;
        if (time + billyDist[town][v] <= rumorTime[v]) ++bd;
    }
    return bd;
}

void search(ull mask, int town, int time) {
    if (ans == reachCnt) return;
    if (!addLabel(mask, town, time)) return;
    ans = max(ans, __builtin_popcountll(mask));
    if (upperBound(mask, town, time) <= ans) return;
    vector<Edge> edges = graph[town];
    sort(edges.begin(), edges.end(), [&](const Edge &a, const Edge &b) {
        int arA = time + a.time, arB = time + b.time;
        ull bitA = 1ULL << a.to, bitB = 1ULL << b.to;
        bool svA = rumorTime[a.to] != INF && !(mask & bitA) && arA <= rumorTime[a.to];
        bool svB = rumorTime[b.to] != INF && !(mask & bitB) && arB <= rumorTime[b.to];
        if (svA != svB) return svA > svB;
        if (a.time != b.time) return a.time < b.time;
        return a.to < b.to;
    });
    for (const Edge &e : edges) {
        int ar = time + e.time;
        ull bit = 1ULL << e.to;
        bool sv = rumorTime[e.to] != INF && !(mask & bit) && ar <= rumorTime[e.to];
        if (sv) {
            search(mask | bit, e.to, ar + stopTime[e.to]);
            if (ans == reachCnt) return;
        }
        search(mask, e.to, ar);
        if (ans == reachCnt) return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> townCnt >> routeCnt) {
        if (townCnt == 0 && routeCnt == 0) break;
        stopTime.assign(townCnt, 0);
        rumorDist.assign(townCnt, vector<int>(townCnt, INF));
        billyDist.assign(townCnt, vector<int>(townCnt, INF));
        graph.assign(townCnt, vector<Edge>());
        labels.assign(townCnt, vector<Label>());
        for (int i = 0; i < townCnt; ++i) {
            cin >> stopTime[i];
            rumorDist[i][i] = 0;
            billyDist[i][i] = 0;
        }
        for (int i = 0; i < routeCnt; ++i) {
            int u, v, t;
            cin >> u >> v >> t;
            int bt = t / 2;
            graph[u].push_back({v, bt});
            graph[v].push_back({u, bt});
            rumorDist[u][v] = min(rumorDist[u][v], t);
            rumorDist[v][u] = min(rumorDist[v][u], t);
            billyDist[u][v] = min(billyDist[u][v], bt);
            billyDist[v][u] = min(billyDist[v][u], bt);
        }
        for (int u = 0; u < townCnt; ++u) {
            vector<int> best(townCnt, INF);
            for (const Edge &e : graph[u]) best[e.to] = min(best[e.to], e.time);
            graph[u].clear();
            for (int v = 0; v < townCnt; ++v) {
                if (best[v] != INF) graph[u].push_back({v, best[v]});
            }
        }
        floyd(rumorDist);
        floyd(billyDist);
        rumorTime = rumorDist[0];
        reachCnt = 0;
        for (int i = 0; i < townCnt; ++i) {
            if (rumorTime[i] != INF) ++reachCnt;
        }
        ans = 0;
        search(0ULL, 0, 0);
        search(1ULL, 0, stopTime[0]);
        cout << ans << '\n';
    }
    return 0;
}
