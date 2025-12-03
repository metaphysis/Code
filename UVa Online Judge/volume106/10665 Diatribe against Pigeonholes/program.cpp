// Diatribe against Pigeonholes
// UVa ID: 10665
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 排序函数1：包裹数降序，包裹数相同时字母序升序
bool cmp1(const pair<char, int>& a, const pair<char, int>& b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
}

// 排序函数2：包裹数降序，包裹数相同时字母序降序
bool cmp2(const pair<char, int>& a, const pair<char, int>& b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first > b.first;
}

int main() {
    int M;
    cin >> M;
    
    while (M--) {
        int N;
        cin >> N;
        string s;
        cin >> s;
        
        // 统计包裹数
        vector<int> parcels(26, 0);
        for (char ch : s) {
            if (ch == '#') break;
            if (ch >= 'A' && ch <= 'Z' && ch - 'A' < N) 
                parcels[ch - 'A']++;
        }
        
        // 创建工人列表
        vector<pair<char, int>> workers(N);
        for (int i = 0; i < N; i++) 
            workers[i] = {'A' + i, parcels[i]};
        
        // 结果存储
        vector<pair<char, int>> result(N);
        int left = 0, right = N - 1;
        
        // 处理工人
        for (int i = 0; i < N; ) {
            if (i + 1 < N) {
                // 对剩余工人按cmp1排序
                sort(workers.begin() + i, workers.end(), cmp1);
                
                if (workers[i].second != workers[i + 1].second) {
                    // 包裹数不同
                    if (workers[i].first < workers[i + 1].first) {
                        result[left++] = workers[i];
                        // 对剩余工人按cmp2排序
                        sort(workers.begin() + i + 1, workers.end(), cmp2);
                        result[right--] = workers[i + 1];
                    } else {
                        swap(workers[i], workers[i + 1]);
                        result[left++] = workers[i];
                        sort(workers.begin() + i + 1, workers.end(), cmp2);
                        result[right--] = workers[i + 1];
                    }
                } else {
                    // 包裹数相同
                    result[left++] = workers[i];
                    sort(workers.begin() + i + 1, workers.end(), cmp2);
                    result[right--] = workers[i + 1];
                }
                i += 2;
            } else {
                // 只剩一个工人
                result[left] = workers[i];
                i++;
            }
        }
        
        // 输出工人字母
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << " ";
            cout << result[i].first;
        }
        cout << endl;
        
        // 输出包裹数
        for (int i = 0; i < N; i++) {
            if (i > 0) cout << " ";
            cout << result[i].second;
        }
        cout << endl;
    }
    
    return 0;
}
