// Optimisation
// UVa ID: 781
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.360s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n) {
        // 读取邻接矩阵并构建前驱列表
        vector<vector<int>> pred(n + 1);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                int x;
                cin >> x;
                if (x == 1) pred[j].push_back(i); // i -> j，所以 j 的前驱包含 i
            }
        }
        // 初始化支配集合：Dom[1] = {1}，其余为全集
        vector<set<int>> dom(n + 1);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                dom[i].insert(j);
        dom[1].clear();
        dom[1].insert(1);
        // 迭代求解支配集合
        bool changed = true;
        while (changed) {
            changed = false;
            for (int v = 2; v <= n; ++v) {
                set<int> inter;
                bool first = true;
                for (int p : pred[v]) {
                    if (first) { inter = dom[p]; first = false; }
                    else {
                        set<int> tmp;
                        set_intersection(inter.begin(), inter.end(),
                                         dom[p].begin(), dom[p].end(),
                                         inserter(tmp, tmp.begin()));
                        inter = tmp;
                    }
                }
                inter.insert(v);
                if (inter != dom[v]) {
                    dom[v] = inter;
                    changed = true;
                }
            }
        }
        // 求每个结点的直接支配者
        vector<int> idom(n + 1, 0);
        for (int v = 2; v <= n; ++v) {
            int best = -1, bestSize = -1;
            for (int u : dom[v]) {
                if (u == v) continue;
                int sz = (int)dom[u].size();
                if (sz > bestSize) {
                    bestSize = sz;
                    best = u;
                }
            }
            idom[v] = best;
        }
        // 收集边并排序
        vector<pair<int, int>> edges;
        for (int v = 2; v <= n; ++v) edges.emplace_back(idom[v], v);
        sort(edges.begin(), edges.end());
        // 输出
        for (auto &e : edges) cout << e.first << ' ' << e.second << '\n';
    }
    return 0;
}
