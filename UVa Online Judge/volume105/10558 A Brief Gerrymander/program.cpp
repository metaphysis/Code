// A Brief Gerrymander
// UVa ID: 10558
// Verdict: Accepted
// Submission Date: 2025-11-24
// UVa Run Time: 0.100s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n, n != -1) {
        vector<pair<int, int>> neighborhoods(n);
        for (int i = 0; i < n; i++) {
            cin >> neighborhoods[i].first >> neighborhoods[i].second;
        }
        
        int s;
        cin >> s;
        vector<int> streets(s);
        for (int i = 0; i < s; i++) cin >> streets[i];
        
        int a;
        cin >> a;

        // 收集候选大道：有社区的大道（排除1和100）
        set<int> candidateSet;
        for (auto& nb : neighborhoods) {
            if (nb.second != 1 && nb.second != 100) {
                candidateSet.insert(nb.second);
            }
        }
        // 添加1和100用于预计算，但选择时排除
        candidateSet.insert(1);
        candidateSet.insert(100);
        vector<int> allAvenues(candidateSet.begin(), candidateSet.end());
        int totalAvenues = allAvenues.size();
        
        // 找到1和100在allAvenues中的位置
        int idx1 = find(allAvenues.begin(), allAvenues.end(), 1) - allAvenues.begin();
        int idx100 = find(allAvenues.begin(), allAvenues.end(), 100) - allAvenues.begin();
        
        // 构建候选大道（排除1和100）
        vector<int> candidates;
        for (int i = 0; i < totalAvenues; i++) {
            if (allAvenues[i] != 1 && allAvenues[i] != 100) {
                candidates.push_back(i);  // 存储索引而不是值
            }
        }
        int m = candidates.size();

        // 预计算：hasCommunity[st][av] 表示街道区间st在大道区间av是否有社区
        vector<vector<bool>> hasCommunity(s - 1, vector<bool>(totalAvenues - 1, false));
        for (auto& nb : neighborhoods) {
            int streetIdx = upper_bound(streets.begin(), streets.end(), nb.first) - streets.begin() - 1;
            if (streetIdx < 0 || streetIdx >= s - 1) continue;
            
            int avenueIdx = upper_bound(allAvenues.begin(), allAvenues.end(), nb.second) - allAvenues.begin() - 1;
            if (avenueIdx >= 0 && avenueIdx < totalAvenues - 1) {
                hasCommunity[streetIdx][avenueIdx] = true;
            }
        }

        // 预计算区间价值矩阵
        vector<vector<int>> intervalValue(totalAvenues, vector<int>(totalAvenues, 0));
        for (int i = 0; i < totalAvenues; i++) {
            for (int j = i + 1; j < totalAvenues; j++) {
                int value = 0;
                for (int st = 0; st < s - 1; st++) {
                    bool covered = false;
                    for (int av = i; av < j; av++) {
                        if (hasCommunity[st][av]) {
                            covered = true;
                            break;
                        }
                    }
                    if (covered) value++;
                }
                intervalValue[i][j] = value;
            }
        }

        // 动态规划：选择A-2条大道
        int selectCount = min(a - 2, m);
        
        vector<vector<int>> dp(selectCount + 1, vector<int>(m, -1));
        vector<vector<int>> prev(selectCount + 1, vector<int>(m, -1));
        
        // 初始化：选择第一条大道（与大道1形成区间）
        for (int j = 0; j < m; j++) {
            dp[1][j] = intervalValue[idx1][candidates[j]];
        }
        
        // DP转移
        for (int k = 2; k <= selectCount; k++) {
            for (int j = k - 1; j < m; j++) {
                for (int i = k - 2; i < j; i++) {
                    if (dp[k - 1][i] != -1) {
                        int newVal = dp[k - 1][i] + intervalValue[candidates[i]][candidates[j]];
                        if (newVal > dp[k][j]) {
                            dp[k][j] = newVal;
                            prev[k][j] = i;
                        }
                    }
                }
            }
        }

        // 找到最优解（考虑最后区间）
        int bestVal = -1, bestIdx = -1;
        if (selectCount == 0) {
            // 如果不需要选择额外大道，只有[1,100)区间
            bestVal = intervalValue[idx1][idx100];
            bestIdx = -1;
        } else {
            for (int j = 0; j < m; j++) {
                if (dp[selectCount][j] != -1) {
                    int totalVal = dp[selectCount][j] + intervalValue[candidates[j]][idx100];
                    if (totalVal > bestVal) {
                        bestVal = totalVal;
                        bestIdx = j;
                    }
                }
            }
        }

        // 构造解
        vector<int> selected;
        if (selectCount > 0 && bestIdx != -1) {
            int k = selectCount;
            int idx = bestIdx;
            while (k > 0) {
                selected.push_back(allAvenues[candidates[idx]]);  // 转换为实际大道值
                idx = prev[k][idx];
                k--;
            }
            reverse(selected.begin(), selected.end());
        }
        
        // 添加固定边界
        vector<int> result;
        result.push_back(1);
        result.insert(result.end(), selected.begin(), selected.end());
        result.push_back(100);
        
        // 确保数量正确
        while (result.size() < a) {
            for (int i = 2; i < 100 && result.size() < a; i++) {
                if (find(result.begin(), result.end(), i) == result.end()) {
                    result.push_back(i);
                }
            }
        }
        
        sort(result.begin(), result.end());

        // 输出
        cout << a;
        for (int av : result) cout << " " << av;
        cout << endl;
    }
    return 0;
}
