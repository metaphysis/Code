// King's Quest
// UVa ID: 1327
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.330s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 4005; // 最多 2N 个节点

vector<int> G[MAXN];   // 邻接表
int idx[MAXN], low[MAXN], scc_id[MAXN], scc_cnt, ts; // Tarjan 算法相关数组
int stk[MAXN], top;    // 栈
bool in_stk[MAXN];     // 标记节点是否在栈中

// Tarjan 算法求强连通分量
void tarjan(int u) {
    idx[u] = low[u] = ++ts;
    stk[top++] = u;
    in_stk[u] = true;
    for (int v : G[u]) {
        if (!idx[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_stk[v]) {
            low[u] = min(low[u], idx[v]);
        }
    }
    if (low[u] == idx[u]) {
        int x;
        do {
            x = stk[--top];
            in_stk[x] = false;
            scc_id[x] = scc_cnt;
        } while (x != u);
        scc_cnt++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    while (cin >> N) {
        // 初始化图和相关数组
        for (int i = 0; i < 2 * N; i++) {
            G[i].clear();
            idx[i] = low[i] = scc_id[i] = 0;
            in_stk[i] = false;
        }
        scc_cnt = ts = top = 0;

        // 读入每个王子的喜好
        vector<vector<int>> like(N);
        for (int i = 0; i < N; i++) {
            int k;
            cin >> k;
            like[i].resize(k);
            for (int j = 0; j < k; j++) {
                cin >> like[i][j];
            }
        }

        // 读入初始匹配
        vector<int> match(N);
        for (int i = 0; i < N; i++) {
            cin >> match[i];
        }

        // 构建有向图
        for (int i = 0; i < N; i++) {
            for (int g : like[i]) {
                if (g == match[i]) continue; // 初始匹配不建边
                // 王子 i -> 女孩 g
                G[i].push_back(N + g - 1);
            }
        }
        for (int i = 0; i < N; i++) {
            // 女孩 match[i] -> 王子 i（初始匹配的反向边）
            G[N + match[i] - 1].push_back(i);
        }

        // 求强连通分量
        for (int i = 0; i < 2 * N; i++) {
            if (!idx[i]) tarjan(i);
        }

        // 输出答案
        for (int i = 0; i < N; i++) {
            vector<int> ans;
            for (int g : like[i]) {
                // 可以选的女孩：初始匹配的女孩 或 在同一个 SCC 中的女孩
                if (g == match[i] || scc_id[i] == scc_id[N + g - 1]) {
                    ans.push_back(g);
                }
            }
            sort(ans.begin(), ans.end());
            cout << ans.size();
            for (int g : ans) {
                cout << " " << g;
            }
            cout << "\n";
        }
    }

    return 0;
}
