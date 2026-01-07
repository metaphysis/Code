// Equipment
// UVa ID: 1508
// Verdict: Accepted
// Submission Date: 2025-12-31
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 深度优先搜索枚举所有大小为k的组合
void dfs(const vector<vector<int>>& candidates, int start, int k, vector<int>& current, int& bestScore) {
    if (k == 0) {
        // 计算当前组合的目标分数：五个维度的最大值之和
        vector<int> maxVals(5, 0);
        for (int idx : current) {
            for (int j = 0; j < 5; ++j) {
                if (candidates[idx][j] > maxVals[j]) maxVals[j] = candidates[idx][j];
            }
        }
        int score = 0;
        for (int v : maxVals) score += v;
        if (score > bestScore) bestScore = score;
        return;
    }
    // 组合枚举
    for (int i = start; i <= (int)candidates.size() - k; ++i) {
        current.push_back(i);
        dfs(candidates, i + 1, k - 1, current, bestScore);
        current.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<vector<int>> equipment(N, vector<int>(5));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < 5; ++j)
                cin >> equipment[i][j];

        // 情况1: K >= 5，直接取每个维度的全局最大值
        if (K >= 5) {
            vector<int> maxPerCategory(5, 0);
            for (int j = 0; j < 5; ++j) {
                for (int i = 0; i < N; ++i) {
                    if (equipment[i][j] > maxPerCategory[j]) maxPerCategory[j] = equipment[i][j];
                }
            }
            int total = 0;
            for (int v : maxPerCategory) total += v;
            cout << total << '\n';
            continue;
        }

        // 情况2: K < 5，构建候选装备集合
        vector<int> candidateIndices;
        int candidatesPerCategory = min(10, N); // 每个维度取前10名
        
        for (int j = 0; j < 5; ++j) {
            // 按第j维评分排序装备索引
            vector<pair<int, int>> sortedByCategory;
            for (int i = 0; i < N; ++i) sortedByCategory.emplace_back(equipment[i][j], i);
            // 降序排序
            sort(sortedByCategory.begin(), sortedByCategory.end(), 
                 [](const pair<int, int>& a, const pair<int, int>& b) {
                     return a.first > b.first;
                 });
            // 取前candidatesPerCategory个
            for (int t = 0; t < candidatesPerCategory && t < (int)sortedByCategory.size(); ++t) {
                candidateIndices.push_back(sortedByCategory[t].second);
            }
        }
        
        // 去重
        sort(candidateIndices.begin(), candidateIndices.end());
        candidateIndices.erase(unique(candidateIndices.begin(), candidateIndices.end()), candidateIndices.end());
        
        // 构建候选装备列表
        vector<vector<int>> candidates;
        for (int idx : candidateIndices) candidates.push_back(equipment[idx]);
        
        // 计算最佳分数
        int bestScore = 0;
        if ((int)candidates.size() <= K) {
            // 候选装备数量不足K个，直接计算
            vector<int> maxVals(5, 0);
            for (const auto& eq : candidates) {
                for (int j = 0; j < 5; ++j) {
                    if (eq[j] > maxVals[j]) maxVals[j] = eq[j];
                }
            }
            for (int v : maxVals) bestScore += v;
        } else {
            // 枚举所有大小为K的组合
            vector<int> current;
            dfs(candidates, 0, K, current, bestScore);
        }
        
        cout << bestScore << "\n";
    }

    return 0;
}
