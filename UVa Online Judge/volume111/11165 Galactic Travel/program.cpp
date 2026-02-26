// Galactic Travel
// UVa ID: 11165
// Verdict: Accepted
// Submission Date: 2026-02-25
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int solve(int n, int k, vector<vector<pair<int, int>>> &forbidden, int S, int T) {
    // 初始化未访问集合
    set<int> unvisited;
    for (int i = 0; i < n; ++i) unvisited.insert(i);

    // BFS 队列
    queue<pair<int, int>> q; // (node, dist)
    q.push({S, 0});
    unvisited.erase(S);

    while (!q.empty()) {
        int u = q.front().first;
        int dist = q.front().second;
        q.pop();

        if (u == T) return dist;

        // 获取当前节点 u 的禁止区间列表
        auto &ban = forbidden[u];
        vector<int> toVisit;

        // 遍历 unvisited 集合，跳过禁止区间
        auto it = unvisited.begin();
        for (auto &interval : ban) {
            int l = interval.first, r = interval.second;
            // 找到第一个 >= l 的节点
            auto endIt = unvisited.upper_bound(r);
            // 收集 [it, 第一个禁止节点) 区间内的节点
            while (it != unvisited.end() && *it < l) {
                toVisit.push_back(*it);
                ++it;
            }
            // 跳过整个禁止区间 [l, r]
            it = endIt;
        }
        // 收集剩余的节点
        while (it != unvisited.end()) {
            toVisit.push_back(*it);
            ++it;
        }

        // 将这些节点加入队列并从 unvisited 中删除
        for (int v : toVisit) {
            unvisited.erase(v);
            q.push({v, dist + 1});
        }
    }

    return -1; // 不可达
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    for (int caseNum = 1; caseNum <= N; ++caseNum) {
        int n, k;
        cin >> n >> k;

        // 禁止区间列表，forbidden[u] 存储 u 的所有禁止区间 [l, r]
        vector<vector<pair<int, int>>> forbidden(n);
        for (int i = 0; i < k; ++i) {
            int u, v1, v2;
            char dash;
            cin >> u >> v1 >> dash >> v2; // 格式 "U V1-V2"
            forbidden[u].emplace_back(v1, v2);
        }

        int S, T;
        cin >> S >> T;

        int ans = solve(n, k, forbidden, S, T);
        cout << "Case #" << caseNum << ": ";
        if (ans == -1) cout << "Impossible\n";
        else cout << ans << "\n";
    }

    return 0;
}
