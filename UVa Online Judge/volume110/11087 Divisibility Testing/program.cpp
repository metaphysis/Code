// Divisibility Testing
// UVa ID: 11087
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.140s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        int n, k;
        cin >> n >> k;
        
        vector<int> a(n);
        map<int, int> freq;  // 统计每个值的出现次数
        
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            freq[a[i]]++;
        }
        
        // 排序并去重，得到不同的值
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
        
        // 按余数分组
        vector<vector<int>> groups(k);
        for (int val : a) {
            int r = ((val % k) + k) % k;  // 处理负数情况
            groups[r].push_back(val);
        }
        
        long long count = 0;
        
        // 处理余数为0的组
        if (!groups[0].empty()) {
            // 相同值配对：需要该值出现次数 >= 2
            for (int val : groups[0]) {
                if (freq[val] >= 2) {
                    count++;  // (val, val) 算一次
                }
            }
            // 不同值之间的配对
            for (int i = 0; i < groups[0].size(); ++i) {
                for (int j = i + 1; j < groups[0].size(); ++j) {
                    count++;
                }
            }
        }
        
        // 处理k为偶数时的余数k/2组
        if (k % 2 == 0) {
            int r = k / 2;
            if (!groups[r].empty()) {
                // 相同值配对
                for (int val : groups[r]) {
                    if (freq[val] >= 2) {
                        count++;  // (val, val) 算一次
                    }
                }
                // 不同值之间的配对
                for (int i = 0; i < groups[r].size(); ++i) {
                    for (int j = i + 1; j < groups[r].size(); ++j) {
                        count++;
                    }
                }
            }
        }
        
        // 处理其他互补余数对
        for (int r = 1; r < (k + 1) / 2; ++r) {
            int comp = k - r;
            if (r == comp) continue;  // 避免重复处理k/2
            
            // 两组间的所有值对都满足条件
            count += (long long)groups[r].size() * groups[comp].size();
        }
        
        cout << "Case " << caseNum << ": " << count << "\n";
    }

    return 0;
}
