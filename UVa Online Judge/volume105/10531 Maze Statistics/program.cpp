// Maze Statistics
// UVa ID: 10531
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.710s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 将轮廓线连通状态编码为一个整数（7进制）
int encodeState(const vector<int>& comp, int startComp, int n) {
    int code = 0;
    for (int j = 0; j < n; ++j) code = code * 7 + comp[j];
    code = code * 7 + startComp;
    return code;
}

// 从整数解码出轮廓线连通状态
void decodeState(int code, vector<int>& comp, int& startComp, int n) {
    startComp = code % 7;
    code /= 7;
    for (int j = n - 1; j >= 0; --j) {
        comp[j] = code % 7;
        code /= 7;
    }
}

// 计算在指定格子强制为障碍时的可解概率
// fixR == -1 表示不强制任何格子
double calcProb(const vector<vector<double>>& p, int m, int n, int fixR, int fixC) {
    unordered_map<int, double> dpPrev;
    vector<int> initComp(n, 0);
    dpPrev[encodeState(initComp, 0, n)] = 1.0;

    for (int i = 0; i < m; ++i) {
        unordered_map<int, double> dpCur;
        for (auto& entry : dpPrev) {
            int state = entry.first;
            double prob = entry.second;
            vector<int> compPrev(n);
            int startCompPrev;
            decodeState(state, compPrev, startCompPrev, n);

            int maxMask = 1 << n;
            for (int mask = 0; mask < maxMask; ++mask) {
                // 如果当前行有固定障碍格子，跳过不符合的配置
                if (fixR == i && fixC != -1 && !((mask >> fixC) & 1)) continue;

                // 计算当前行配置的概率
                double maskProb = 1.0;
                for (int j = 0; j < n; ++j) {
                    if ((mask >> j) & 1) maskProb *= p[i][j];
                    else {
                        // 固定为障碍的格子不允许是空地
                        if (i == fixR && j == fixC) { maskProb = 0.0; break; }
                        maskProb *= 1.0 - p[i][j];
                    }
                }
                if (maskProb == 0.0) continue;

                // 建立并查集：上一行连通块 + 当前行空地
                int maxIdPrev = 0;
                for (int j = 0; j < n; ++j) if (compPrev[j] > maxIdPrev) maxIdPrev = compPrev[j];
                int totalNodes = maxIdPrev + n;
                vector<int> parent(totalNodes);
                for (int k = 0; k < totalNodes; ++k) parent[k] = k;

                auto find = [&](int x) {
                    while (parent[x] != x) {
                        parent[x] = parent[parent[x]];
                        x = parent[x];
                    }
                    return x;
                };
                auto unite = [&](int a, int b) {
                    a = find(a); b = find(b);
                    if (a != b) parent[a] = b;
                };

                // 标记当前行哪些是空地
                vector<bool> isCurEmpty(n, false);
                for (int j = 0; j < n; ++j) if (!((mask >> j) & 1)) isCurEmpty[j] = true;

                // 合并上下连通
                for (int j = 0; j < n; ++j)
                    if (isCurEmpty[j] && compPrev[j] > 0)
                        unite(maxIdPrev + j, compPrev[j] - 1);

                // 合并当前行左右连通
                for (int j = 1; j < n; ++j)
                    if (isCurEmpty[j] && isCurEmpty[j - 1])
                        unite(maxIdPrev + j, maxIdPrev + j - 1);

                // 检查包含起点的连通块是否延续到当前行
                int newStartComp = 0;
                if (startCompPrev > 0) {
                    int rootStart = find(startCompPrev - 1);
                    bool found = false;
                    for (int j = 0; j < n; ++j)
                        if (isCurEmpty[j] && find(maxIdPrev + j) == rootStart) { found = true; break; }
                    if (!found) continue; // 起点断开，该状态无效
                }

                // 对当前行连通块进行最小表示重编号
                vector<int> compCur(n, 0);
                int newIdCounter = 0;
                vector<int> rootToNewId(totalNodes, 0);
                for (int j = 0; j < n; ++j) {
                    if (isCurEmpty[j]) {
                        int root = find(maxIdPrev + j);
                        if (rootToNewId[root] == 0) rootToNewId[root] = ++newIdCounter;
                        compCur[j] = rootToNewId[root];
                    }
                }

                // 确定当前行包含起点的连通块
                if (startCompPrev > 0) {
                    int rootStart = find(startCompPrev - 1);
                    newStartComp = rootToNewId[rootStart];
                } else if (i == 0 && isCurEmpty[0]) {
                    int rootStart = find(maxIdPrev + 0);
                    newStartComp = rootToNewId[rootStart];
                } else newStartComp = 0;

                int newState = encodeState(compCur, newStartComp, n);
                dpCur[newState] += prob * maskProb;
            }
        }
        dpPrev = move(dpCur);
    }

    // 统计终点与起点连通的配置总概率
    double total = 0.0;
    for (auto& entry : dpPrev) {
        int state = entry.first;
        double prob = entry.second;
        vector<int> comp(n);
        int startComp;
        decodeState(state, comp, startComp, n);
        if (comp[n - 1] > 0 && startComp == comp[n - 1]) total += prob;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(6);

    int T;
    cin >> T;
    for (int tc = 0; tc < T; ++tc) {
        int m, n;
        cin >> m >> n;
        vector<vector<double>> p(m, vector<double>(n));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                cin >> p[i][j];

        double denom = calcProb(p, m, n, -1, -1); // 分母：无条件可解概率
        vector<vector<double>> ans(m, vector<double>(n, 0.0));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j) {
                if (p[i][j] == 0.0) ans[i][j] = 0.0;
                else {
                    double num = calcProb(p, m, n, i, j); // 分子：该格障碍且可解的联合概率
                    ans[i][j] = num / denom;
                }
            }

        // 输出答案
        if (tc > 0) cout << "\n";
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                cout << ans[i][j] << (j == n - 1 ? "\n" : " ");
    }
    return 0;
}
