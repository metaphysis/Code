// Inviting Politicians
// UVa ID: 10052
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.010s
// https://blog.csdn.net/metaphysis/article/details/163173636

#include <bits/stdc++.h>
using namespace std;

// DSATUR 着色器
class GraphColorer {
public:
    int n;                              // 顶点数
    vector<vector<int>> adj;            // 邻接表
    vector<string> name;                // 名字
    vector<int> color;                  // 当前颜色 (-1 表示未着色)
    vector<int> degree;                 // 度数

    GraphColorer(int n, const vector<string>& names, const vector<vector<int>>& adjList)
        : n(n), adj(adjList), name(names), color(n, -1), degree(n) {
        for (int i = 0; i < n; ++i) degree[i] = adj[i].size();
    }

    // 判断顶点 v 能否赋予颜色 c
    bool canColor(int v, int c) {
        for (int u : adj[v])
            if (color[u] == c) return false;
        return true;
    }

    // 选择下一个待着色顶点（DSATUR 规则）
    int selectVertex() {
        int best = -1, bestSat = -1, bestDeg = -1;
        for (int v = 0; v < n; ++v) {
            if (color[v] != -1) continue;
            // 计算饱和度：邻居中不同颜色的个数
            bool seen[4] = {false};
            int sat = 0;
            for (int u : adj[v]) {
                if (color[u] != -1) {
                    int c = color[u];
                    if (!seen[c]) {
                        seen[c] = true;
                        ++sat;
                    }
                }
            }
            // 饱和度优先，其次度数
            if (sat > bestSat || (sat == bestSat && degree[v] > bestDeg)) {
                bestSat = sat;
                bestDeg = degree[v];
                best = v;
            }
        }
        return best;
    }

    // 递归回溯着色
    bool dfs(int cnt) {
        if (cnt == n) return true;
        int v = selectVertex();
        // 尝试 4 种颜色
        for (int c = 0; c < 4; ++c) {
            if (canColor(v, c)) {
                color[v] = c;
                if (dfs(cnt + 1)) return true;
                color[v] = -1;          // 回溯
            }
        }
        return false;
    }

    // 执行着色，返回是否成功（一定成功）
    bool colorGraph() {
        // 初始选度数最大的顶点，赋颜色 0
        int start = 0;
        for (int i = 1; i < n; ++i)
            if (degree[i] > degree[start]) start = i;
        color[start] = 0;
        return dfs(1);
    }

    // 获取颜色分组
    vector<vector<int>> getGroups() {
        vector<vector<int>> groups(4);
        for (int i = 0; i < n; ++i)
            groups[color[i]].push_back(i);
        return groups;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N, M;
        cin >> N >> M;
        vector<string> names(N);
        unordered_map<string, int> id;
        for (int i = 0; i < N; ++i) {
            cin >> names[i];
            id[names[i]] = i;
        }

        vector<vector<int>> adj(N);
        for (int i = 0; i < M; ++i) {
            string a, b;
            cin >> a >> b;
            int u = id[a], v = id[b];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        GraphColorer gc(N, names, adj);
        gc.colorGraph();                    // 一定成功
        auto groups = gc.getGroups();

        // 输出 Case 编号
        cout << "Case #" << tc << "\n";
        for (int i = 0; i < 4; ++i) {
            cout << groups[i].size() << "\n";
            for (int j = 0; j < (int)groups[i].size(); ++j) {
                if (j) cout << " ";
                cout << names[groups[i][j]];
            }
            cout << "\n";
        }

        // 两个测试用例之间空行
        if (tc != T) cout << "\n";
    }

    return 0;
}
