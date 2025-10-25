// Knights of the Round Table
// UVa ID: 1364
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

bool hate[MAXN][MAXN]; // 原图的憎恨关系矩阵
vector<int> graph[MAXN]; // 补图的邻接表
int n, m;

// Tarjan 算法相关变量
int dfn[MAXN], low[MAXN], dfsClock;
stack<int> stk;
vector<vector<int>> bccList; // 存储所有点双连通分量
bool isCut[MAXN]; // 标记割点

// 二分图染色检查
bool checkBipartite(int start, const vector<int>& component, int color[]) {
    queue<int> q;
    q.push(start);
    color[start] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : graph[u]) {
            // 检查 v 是否在当前分量中
            bool inComponent = false;
            for (int x : component) {
                if (x == v) {
                    inComponent = true;
                    break;
                }
            }
            if (!inComponent) continue;

            if (color[v] == -1) {
                color[v] = color[u] ^ 1;
                q.push(v);
            } else if (color[v] == color[u]) {
                return false; // 发现奇环
            }
        }
    }
    return true;
}

void tarjan(int u, int parent) {
    dfn[u] = low[u] = ++dfsClock;
    stk.push(u);
    int childCount = 0;
    
    for (int v = 1; v <= n; v++) {
        if (!hate[u][v] && u != v) { // 补图中的边
            if (!dfn[v]) {
                childCount++;
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    if (parent != -1 || childCount > 1) isCut[u] = true;
                    vector<int> component;
                    component.push_back(u);
                    while (true) {
                        int x = stk.top(); stk.pop();
                        component.push_back(x);
                        if (x == v) break;
                    }
                    bccList.push_back(component);
                }
            } else if (v != parent && dfn[v] < dfn[u]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while (cin >> n >> m, n || m) {
        // 初始化
        memset(hate, 0, sizeof(hate));
        for (int i = 1; i <= n; i++) graph[i].clear();
        bccList.clear();
        while (!stk.empty()) stk.pop();
        dfsClock = 0;
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(isCut, 0, sizeof(isCut));

        // 读入憎恨关系
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            hate[a][b] = hate[b][a] = true;
        }

        // 构建补图
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (!hate[i][j]) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }

        // 使用 Tarjan 算法找点双连通分量
        for (int i = 1; i <= n; i++) {
            if (!dfn[i]) {
                tarjan(i, -1);
                // 处理栈中剩余的点
                if (!stk.empty()) {
                    vector<int> component;
                    while (!stk.empty()) {
                        component.push_back(stk.top());
                        stk.pop();
                    }
                    bccList.push_back(component);
                }
            }
        }

        // 标记能留下的骑士
        bool safe[MAXN] = {false};
        for (const auto& component : bccList) {
            if (component.size() < 3) continue; // 奇环至少需要 3 个点
            int color[MAXN];
            memset(color, -1, sizeof(color));
            // 检查是否为二分图
            if (!checkBipartite(component[0], component, color)) {
                // 不是二分图，包含奇环，标记所有顶点
                for (int u : component) safe[u] = true;
            }
        }

        // 统计必须开除的人数
        int expelledCount = 0;
        for (int i = 1; i <= n; i++) {
            if (!safe[i]) expelledCount++;
        }
        cout << expelledCount << "\n";
    }

    return 0;
}
