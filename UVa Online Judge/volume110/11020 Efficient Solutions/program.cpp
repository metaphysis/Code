// Efficient Solutions
// UVa ID: 11020
// Verdict: Accepted
// Submission Date: 2025-10-21
// UVa Run Time: 0.820s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    
    for (int caseNum = 1; caseNum <= N; caseNum++) {
        int n;
        cin >> n;
        multiset<pair<int, int>> efficient;  // 存储有效点，按家世升序，家世相同时按魅力升序
        vector<int> result;  // 存储每次更新后的结果
        
        for (int i = 0; i < n; i++) {
            int L, C;
            cin >> L >> C;
            pair<int, int> p = {L, C};
            
            // 检查新点是否被支配
            auto it = efficient.lower_bound({L, INT_MIN});  // 找到第一个家世>=L的点
            bool dominated = false;
            
            // 检查前一个点（家世<=L）是否支配新点
            if (it != efficient.begin()) {
                auto prev = it;
                --prev;
                if (prev->first <= L && prev->second <= C) {  // 前一个点两个维度都不比新点差
                    if (prev->first < L || prev->second < C) {  // 且至少一个严格优于
                        dominated = true;
                    }
                }
            }
            
            // 检查同家世的点是否支配新点
            if (!dominated) {
                while (it != efficient.end() && it->first == L) {
                    if (it->second < C) {  // 同家世但魅力更优
                        dominated = true;
                        break;
                    }
                    ++it;
                }
            }
            
            // 如果被支配，跳过插入
            if (dominated) {
                result.push_back(efficient.size());
                continue;
            }
            
            // 插入新点
            efficient.insert(p);
            
            // 删除所有被新点支配的点
            it = efficient.upper_bound(p);  // 从新点的下一个开始
            while (it != efficient.end()) {
                if (it->first >= L && it->second >= C) {  // 当前点两个维度都不比新点差
                    if (it->first > L || it->second > C) {  // 且新点至少一个严格优于
                        it = efficient.erase(it);  // 删除被支配的点
                    } else {
                        ++it;  // 完全相同，保留
                    }
                } else {
                    ++it;  // 不被支配，继续检查
                }
            }
            
            result.push_back(efficient.size());
        }
        
        // 输出结果
        cout << "Case #" << caseNum << ":\n";
        for (int sz : result) {
            cout << sz << "\n";
        }
        if (caseNum < N) {
            cout << "\n";
        }
    }
    return 0;
}
