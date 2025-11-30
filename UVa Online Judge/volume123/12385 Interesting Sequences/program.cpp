// Interesting Sequences
// UVa ID: 12385
// Verdict: Accepted
// Submission Date: 2025-11-26
// UVa Run Time: 0.210s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int testCases;
    cin >> testCases;
    
    while (testCases--) {
        int n;
        cin >> n;
        vector<int> sequence(n);
        
        // 读取序列
        for (int i = 0; i < n; i++) cin >> sequence[i];
        
        // 存储每个数值出现的位置
        unordered_map<int, vector<int>> positions;
        for (int i = 0; i < n; i++) positions[sequence[i]].push_back(i);
        
        vector<pair<int, int>> intervals;
        
        // 为每个数值生成所有可能的区间
        for (auto& entry : positions) {
            const vector<int>& pos = entry.second;
            int size = pos.size();
            // 对于每个数值，生成所有可能的区间 [i, j]
            for (int i = 0; i < size; i++) 
                for (int j = i + 1; j < size; j++) 
                    intervals.emplace_back(pos[i], pos[j]);
        }
        
        // 如果没有区间，直接输出0
        if (intervals.empty()) {
            cout << 0 << "\n";
            continue;
        }
        
        // 按照区间结束位置排序
        sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
        });
        
        // 贪心选择不重叠的区间
        int count = 1;
        int lastEnd = intervals[0].second;
        
        for (int i = 1; i < intervals.size(); i++) 
            if (intervals[i].first >= lastEnd) {
                count++;
                lastEnd = intervals[i].second;
            }
        
        cout << count << "\n";
    }
    
    return 0;
}
