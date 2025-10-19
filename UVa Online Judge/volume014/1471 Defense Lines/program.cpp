// Defense Lines
// UVa ID: 1471
// Verdict: Accepted
// Submission Date: 2025-10-19
// UVa Run Time: 0.440s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int a[MAXN], f[MAXN], g[MAXN];

int main() {
    int Z;
    scanf("%d", &Z);
    while (Z--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        
        // 计算f[i]: 以i结尾的最长连续递增子序列长度
        f[0] = 1;
        for (int i = 1; i < n; i++) {
            if (a[i] > a[i-1]) f[i] = f[i-1] + 1;
            else f[i] = 1;
        }
        
        // 计算g[i]: 以i开头的最长连续递增子序列长度
        g[n-1] = 1;
        for (int i = n-2; i >= 0; i--) {
            if (a[i] < a[i+1]) g[i] = g[i+1] + 1;
            else g[i] = 1;
        }
        
        int ans = 0;
        // 情况1: 不删除任何塔楼
        for (int i = 0; i < n; i++) {
            ans = max(ans, f[i]);
        }
        
        // 情况2: 删除单个塔楼
        for (int i = 0; i < n - 2; i++) {
            if (a[i] < a[i+2]) {
                ans = max(ans, f[i] + g[i+2]);
            }
        }
        
        // 情况3: 使用set优化查找
        set<pair<int, int>> s; // 存储(a[j], f[j])对
        
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                // 在set中查找满足a[j] < a[i]的最大f[j]
                auto it = s.lower_bound({a[i], -1});
                if (it != s.begin()) {
                    it--;
                    ans = max(ans, it->second + g[i]);
                }
            }
            
            // 维护set，删除被支配的元素
            auto it = s.lower_bound({a[i], -1});
            bool should_insert = true;
            
            // 如果存在相同a值但f值更大的元素，不插入当前元素
            if (it != s.end() && it->first == a[i]) {
                if (it->second >= f[i]) {
                    should_insert = false;
                } else {
                    s.erase(it);
                }
            }
            
            if (should_insert) {
                // 插入当前元素
                it = s.insert({a[i], f[i]}).first;
                
                // 检查前一个元素，如果前一个元素的f值更大，删除当前元素
                if (it != s.begin()) {
                    auto prev_it = it;
                    prev_it--;
                    if (prev_it->second >= it->second) {
                        s.erase(it);
                        should_insert = false;
                    }
                }
                
                // 删除后面被当前元素支配的元素
                if (should_insert) {
                    auto next_it = it;
                    next_it++;
                    while (next_it != s.end() && next_it->second <= it->second) {
                        next_it = s.erase(next_it);
                    }
                }
            }
        }
        
        printf("%d\n", ans);
    }
    return 0;
}
