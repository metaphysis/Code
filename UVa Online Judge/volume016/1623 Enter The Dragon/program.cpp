// Enter The Dragon
// UVa ID: 1623
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.730s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> solveTestCase(int n, int m, vector<int>& forecast) {
    vector<int> drys, result;
    vector<vector<int>> rains(n + 1);
    
    // 收集非雨天和下雨信息
    for (int i = 0; i < m; i++) {
        if (forecast[i] == 0) drys.push_back(i + 1);
        else rains[forecast[i]].push_back(i + 1);
    }
    
    result.resize(drys.size(), 0);
    set<int> drySet(drys.begin(), drys.end());
    vector<pair<int, pair<int, int>>> tasks;
    
    // 为每个湖泊生成喝水任务
    for (int lake = 1; lake <= n; lake++) {
        if (rains[lake].empty()) continue;
        for (int i = 0; i < rains[lake].size(); i++) {
            // 计算区间左右端点
            int left = (i == 0) ? 1 : rains[lake][i - 1] + 1;
            int right = rains[lake][i] - 1;
            // 检查区间有效性
            if (left > right) return vector<int>();
            tasks.push_back(make_pair(right, make_pair(left, lake)));
        }
    }
    
    // 按右端点排序
    sort(tasks.begin(), tasks.end());
    
    // 贪心匹配
    for (auto task : tasks) {
        int right = task.first;
        int left = task.second.first;
        int lake = task.second.second;
        // 找到在区间内的最小可用非雨天
        auto it = drySet.lower_bound(left);
        if (it == drySet.end() || *it > right) return vector<int>();
        int dryDay = *it;
        drySet.erase(it);
        // 记录匹配结果
        result[lower_bound(drys.begin(), drys.end(), dryDay) - drys.begin()] = lake;
    }
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int Z;
    cin >> Z;
    
    while (Z--) {
        int n, m;
        cin >> n >> m;
        vector<int> forecast(m);
        for (int i = 0; i < m; i++) cin >> forecast[i];
        
        vector<int> result = solveTestCase(n, m, forecast);
        
        if (result.empty()) cout << "NO\n";
        else {
            cout << "YES\n";
            for (int i = 0; i < result.size(); i++) {
                if (i > 0) cout << " ";
                cout << result[i];
            }
            cout << "\n";
        }
    }
    
    return 0;
}
