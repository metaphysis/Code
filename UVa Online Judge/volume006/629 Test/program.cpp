// Test
// UVa ID: 629
// Verdict: Accepted
// Submission Date: 2026-01-13
// UVa Run Time: 0.590s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 检查子集是否为团（所有顶点间都无差异）
bool isClique(const vector<vector<bool>>& noDiff, const vector<int>& subset) {
    for (int i = 0; i < subset.size(); ++i)
        for (int j = i + 1; j < subset.size(); ++j)
            if (!noDiff[subset[i]][subset[j]]) return false;
    return true;
}

// 检查团是否为极大团
bool isMaximalClique(const vector<vector<bool>>& noDiff, const vector<int>& clique, int n) {
    vector<bool> inClique(n, false);
    for (int v : clique) inClique[v] = true;
    for (int v = 0; v < n; ++v) {
        if (inClique[v]) continue;
        // 尝试将 v 加入团中
        bool canAdd = true;
        for (int u : clique)
            if (!noDiff[u][v]) {
                canAdd = false;
                break;
            }
        if (canAdd) return false; // 可以加入，说明不是极大团
    }
    return true;
}

int main() {
    int n;
    bool firstMatrix = true;
    while (cin >> n) {
        vector<string> mat(n);
        for (int i = 0; i < n; ++i) cin >> mat[i];
        // 构建无差异图
        vector<vector<bool>> noDiff(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            noDiff[i][i] = true; // 自己和自己无差异
            for (int j = i + 1; j < n; ++j)
                if (mat[i][j] == '-') noDiff[i][j] = noDiff[j][i] = true;
        }
        // 找出所有极大团
        vector<vector<int>> maximalCliques;
        int totalSubsets = 1 << n;
        for (int mask = 1; mask < totalSubsets; ++mask) {
            vector<int> subset;
            for (int i = 0; i < n; ++i)
                if (mask & (1 << i)) subset.push_back(i);
            if (isClique(noDiff, subset) && isMaximalClique(noDiff, subset, n))
                maximalCliques.push_back(subset);
        }
        // 排序极大团：大小降序，大小相同则按最小元素升序
        sort(maximalCliques.begin(), maximalCliques.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a.size() != b.size()) return a.size() > b.size();
                 return a < b; // vector 的字典序比较
             });
        // 为每个极大团分配字母标识符
        map<vector<int>, char> cliqueToChar;
        char currentChar = 'a';
        for (const auto& clique : maximalCliques)
            cliqueToChar[clique] = currentChar++;
        // 为每个样本收集标识符
        vector<string> sampleLabels(n);
        for (int i = 0; i < n; ++i) {
            string labels;
            for (const auto& clique : maximalCliques)
                if (find(clique.begin(), clique.end(), i) != clique.end())
                    labels += cliqueToChar[clique];
            sort(labels.begin(), labels.end());
            sampleLabels[i] = labels;
        }
        // 输出结果
        for (int i = 0; i < n; ++i) cout << sampleLabels[i] << '\n';
        cout << "-----\n";
    }
    return 0;
}
