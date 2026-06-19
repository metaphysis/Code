// Coloring the Map but Not Anyhow
// UVa ID: 11206
// Verdict: Accepted
// Submission Date: 2026-06-19
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int nn, nb;
int colorVal[5]; // 1-based
vector<int> adj[25];
int nodeOrder[25]; // 按度数排序后的节点顺序
int degree[25];
int bestAns;
int curColor[25]; // 0:未着色, 1~4:颜色编号

// 计算两个颜色编号的差值平方
inline int diffSq(int c1, int c2) {
    int d = colorVal[c1] - colorVal[c2];
    return d * d;
}

// 计算当前已着色部分的目标函数值（只针对已确定颜色的相邻边）
int calcPartial(int idx) {
    int sum = 0;
    for (int i = 0; i < idx; ++i) {
        int u = nodeOrder[i];
        for (int v : adj[u]) {
            if (curColor[v] != 0 && v < u) { // 只计算一次，且两端都已着色
                // 这里v可能还未着色，但u已经着色，所以只加u-v边当v已着色且v在已处理集合中
                // 简单方法：在DFS中动态累加
            }
        }
    }
    return sum;
}

// 计算当前已着色边贡献（在DFS过程中维护）
int currentSum;

void dfs(int idx) {
    if (idx == nn) {
        bestAns = max(bestAns, currentSum);
        return;
    }
    int u = nodeOrder[idx];
    // 剪枝：理论上界 = currentSum + 剩余边数 * maxDiffSq
    // 但需要知道剩余边数中尚未确定两端的数量，简化：剩余所有未处理节点间的边（包括与已着色节点的边）最多贡献 maxDiffSq
    // 简单剪枝：如果当前最优已经 >= currentSum + 剩余最大可能，则返回
    // 保守剪枝：剩余每个节点最多贡献 maxDiffSq * 度数，但可能高估
    // 这里使用简单剪枝：若 currentSum + (剩余边数) * maxDiffSq <= bestAns 则剪枝
    // 剩余边数估算：剩余节点度数总和 / 2，但为了简单，不进行复杂剪枝，以免出错
    
    // 尝试四种颜色
    for (int c = 1; c <= 4; ++c) {
        bool ok = true;
        int addSum = 0;
        for (int v : adj[u]) {
            if (curColor[v] != 0) {
                if (curColor[v] == c) {
                    ok = false;
                    break;
                }
                addSum += diffSq(c, curColor[v]);
            }
        }
        if (!ok) continue;
        curColor[u] = c;
        currentSum += addSum;
        dfs(idx + 1);
        currentSum -= addSum;
        curColor[u] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> nn) {
        if (nn == 0) break;
        cin >> nb;
        for (int i = 1; i <= 4; ++i) cin >> colorVal[i];
        for (int i = 1; i <= nn; ++i) {
            adj[i].clear();
            degree[i] = 0;
            curColor[i] = 0;
        }
        for (int i = 0; i < nb; ++i) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
            degree[a]++;
            degree[b]++;
        }
        // 按度数降序排列节点
        vector<int> nodes(nn);
        for (int i = 0; i < nn; ++i) nodes[i] = i + 1;
        sort(nodes.begin(), nodes.end(), [&](int a, int b) {
            if (degree[a] != degree[b]) return degree[a] > degree[b];
            return a < b;
        });
        for (int i = 0; i < nn; ++i) nodeOrder[i] = nodes[i];
        bestAns = 0;
        currentSum = 0;
        dfs(0);
        cout << bestAns << "\n";
    }
    return 0;
}
