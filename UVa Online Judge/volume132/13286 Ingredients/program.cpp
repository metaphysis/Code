// Ingredients
// UVa ID: 13286
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.070s

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to;
    int addCost;
    int addPrestige;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int B;
    while (cin >> B) {
        int N;
        cin >> N;
        unordered_map<string, int> id;
        vector<vector<Edge>> outEdges;
        vector<int> inDegree;
        auto getID = [&](const string& name) -> int {
            auto it = id.find(name);
            if (it != id.end()) return it->second;
            int newId = (int)id.size();
            id[name] = newId;
            inDegree.push_back(0);
            outEdges.push_back(vector<Edge>());
            return newId;
        };
        // 读入所有食谱，建图，统计入度
        for (int i = 0; i < N; ++i) {
            string derived, base, ingredient;
            int price, prestige;
            cin >> derived >> base >> ingredient >> price >> prestige;
            int baseId = getID(base);
            int derivedId = getID(derived);
            outEdges[baseId].push_back({derivedId, price, prestige});
            inDegree[derivedId]++;
        }
        int V = (int)id.size();
        vector<int> cost(V, INT_MAX);
        vector<int> prestigeVal(V, INT_MIN);
        queue<int> q;
        // 入度为0的为基本菜，成本0，声望0
        for (int i = 0; i < V; ++i)
            if (inDegree[i] == 0) {
                cost[i] = 0;
                prestigeVal[i] = 0;
                q.push(i);
            }
        // 拓扑排序，计算每个菜的最小总成本及对应最大总声望
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const Edge& e : outEdges[v]) {
                int to = e.to;
                int newCost = cost[v] + e.addCost;
                int newPrestige = prestigeVal[v] + e.addPrestige;
                if (newCost < cost[to] || (newCost == cost[to] && newPrestige > prestigeVal[to])) {
                    cost[to] = newCost;
                    prestigeVal[to] = newPrestige;
                }
                inDegree[to]--;
                if (inDegree[to] == 0) q.push(to);
            }
        }
        // 收集所有成本不超过预算、声望大于0的菜肴作为背包物品
        vector<pair<int, int>> items;
        for (int i = 0; i < V; ++i)
            if (cost[i] <= B && prestigeVal[i] > 0)
                items.push_back({cost[i], prestigeVal[i]});
        // 0/1背包，dp[j]表示总成本恰好为j时的最大声望
        vector<int> dp(B + 1, -1);
        dp[0] = 0;
        for (const auto& item : items) {
            int c = item.first;
            int p = item.second;
            for (int j = B; j >= c; --j)
                if (dp[j - c] != -1) {
                    int val = dp[j - c] + p;
                    if (val > dp[j]) dp[j] = val;
                }
        }
        // 找到最大声望，以及达到该声望的最小成本
        int maxPrestige = 0;
        for (int j = 0; j <= B; ++j)
            if (dp[j] > maxPrestige) maxPrestige = dp[j];
        int minCost = 0;
        for (int j = 0; j <= B; ++j)
            if (dp[j] == maxPrestige) { minCost = j; break; }
        cout << maxPrestige << '\n' << minCost << '\n';
    }
    return 0;
}
