// Interstellar Travel
// UVa ID: 12948
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.020s

#include <bits/stdc++.h>
using namespace std;

struct Edge { int u, v, c, t; };
struct Query { int v, n; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int p, f, q;
    bool first = true;
    const int INF = 1e9;
    while (cin >> p >> f >> q) {
        if (!first) cout << "." << "\n";
        first = false;
        unordered_map<string, int> id;
        vector<string> names(p);
        for (int i = 0; i < p; ++i) { cin >> names[i]; id[names[i]] = i; }
        vector<Edge> edges;
        for (int i = 0; i < f; ++i) {
            string s0, sd;
            int c, t;
            cin >> s0 >> sd >> c >> t;
            edges.push_back({id[s0], id[sd], c, t});
        }
        string startName;
        cin >> startName;
        int start = id[startName];
        vector<Query> queries;
        for (int i = 0; i < q; ++i) {
            string target;
            int n;
            cin >> target >> n;
            queries.push_back({id[target], n});
        }
        int maxK = max(0, p - 1);
        vector<vector<int>> cost(maxK + 1, vector<int>(p, INF));
        vector<vector<int>> timeArr(maxK + 1, vector<int>(p, INF));
        cost[0][start] = 0;
        timeArr[0][start] = 0;
        for (int k = 0; k < maxK; ++k)
            for (const auto& e : edges) {
                if (cost[k][e.u] == INF) continue;
                int nc = cost[k][e.u] + e.c;
                int nt = timeArr[k][e.u] + e.t;
                if (nc < cost[k + 1][e.v] || (nc == cost[k + 1][e.v] && nt < timeArr[k + 1][e.v])) {
                    cost[k + 1][e.v] = nc;
                    timeArr[k + 1][e.v] = nt;
                }
            }
        for (const auto& query : queries) {
            int target = query.v;
            int limit = min(maxK, query.n + 1);
            int bestCost = INF, bestTime = INF;
            for (int k = 0; k <= limit; ++k)
                if (cost[k][target] != INF)
                    if (cost[k][target] < bestCost || (cost[k][target] == bestCost && timeArr[k][target] < bestTime)) {
                        bestCost = cost[k][target];
                        bestTime = timeArr[k][target];
                    }
            if (bestCost == INF) cout << "* *" << "\n";
            else cout << bestCost << " " << bestTime << "\n";
        }
    }
    return 0;
}
