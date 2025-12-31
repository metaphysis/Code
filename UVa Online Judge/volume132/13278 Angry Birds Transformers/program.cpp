// Angry Birds Transformers
// UVa ID: 13278
// Verdict: Accepted
// Submission Date: 2025-12-26
// UVa Run Time: 0.120s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n, n) {
        vector<pair<int, int>> events; // (位置, 类型: 1起点, -1终点)
        for (int i = 0; i < n; ++i) {
            int xi, yi;
            cin >> xi >> yi;
            events.emplace_back(xi - yi, 1);   // 进入视野
            events.emplace_back(xi + yi, -1);  // 离开视野
        }
        // 排序：位置小的在前，位置相同时起点在前（保证共线时计数正确）
        sort(events.begin(), events.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second > b.second; // 起点类型值大，先处理
        });
        int maxVisible = 0;
        int currentVisible = 0;
        for (const auto& e : events) {
            currentVisible += e.second;
            maxVisible = max(maxVisible, currentVisible);
        }
        cout << maxVisible << "\n";
    }
    return 0;
}
