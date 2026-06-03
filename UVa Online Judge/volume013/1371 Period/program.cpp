// Period
// UVa ID: 1371
// Verdict: Accepted
// Submission Date: 2026-06-03
// UVa Run Time: 1.850s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n, m;
string x, y;

// 返回 true 如果存在一种划分使得每段与 y 的编辑距离 <= k
bool check(int k) {
    // reachable[i] 表示 x[0..i-1] 能否被成功划分
    vector<bool> reachable(n + 1, false);
    reachable[0] = true;
    
    // 对每个可能的分段起点
    for (int start = 0; start < n; ++start) {
        if (!reachable[start]) continue;
        
        // 计算从 start 开始的所有子串与 y 的编辑距离
        // dpPrev[j] 表示 x[start..cur-1] 与 y[0..j-1] 的编辑距离
        vector<int> dpPrev(m + 1), dpCurr(m + 1);
        for (int j = 0; j <= m; ++j) dpPrev[j] = j;
        
        int curLen = 0;
        for (int end = start + 1; end <= n; ++end) {
            ++curLen;
            dpCurr[0] = curLen;
            int minVal = curLen;
            
            for (int j = 1; j <= m; ++j) {
                int cost = (x[end - 1] == y[j - 1]) ? 0 : 1;
                dpCurr[j] = min({dpPrev[j] + 1, dpCurr[j - 1] + 1, dpPrev[j - 1] + cost});
                minVal = min(minVal, dpCurr[j]);
            }
            
            if (dpCurr[m] <= k) reachable[end] = true;
            if (minVal > k) break;  // 继续扩展只会更大，提前退出
            
            swap(dpPrev, dpCurr);
        }
    }
    return reachable[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        cin >> y >> x;
        n = x.size(), m = y.size();
        
        int lo = 0, hi = m, ans = m;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (check(mid)) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
