// Airport
// UVa ID: 1450
// Verdict: Accepted
// Submission Date: 2025-12-16
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int N = 5005;

int t, n, a[N], b[N];

// 检查最大等待数不超过 mid 是否可行
bool check(int mid) {
    int an = 0, bn = 0, have = 0;  // an: W路累计等待数, bn: E路累计等待数, have: 可用起飞时隙
    for (int i = 0; i < n; i++) {
        an += a[i];  // 更新W路累计等待数
        bn += b[i];  // 更新E路累计等待数
        
        // 计算至少需要从各条路起飞的飞机数
        int needa = max(an - mid, 0);
        int needb = max(bn - mid, 0);
        
        // 如果需要的起飞数超过可用时隙，则不可行
        if (needa + needb > have) return false;
        
        // 更新可用起飞时隙和等待数
        if (an == 0 && bn > 0) bn--;           // 只能从E路起飞
        else if (bn == 0 && an > 0) an--;      // 只能从W路起飞
        else if (an > 0 && bn > 0 && an + bn > have) have++;  // 两条路都有飞机，增加起飞机会
    }
    return true;
}

// 二分查找最小可行最大等待数
int solve() {
    int left = 0, right = 100000;  // 等待数上界
    while (left < right) {
        int mid = (left + right) / 2;
        if (check(mid)) right = mid;
        else left = mid + 1;
    }
    // 最大等级 = 最大等待数 - 1
    return left == 0 ? 0 : left - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
        cout << solve() << "\n";
    }
    
    return 0;
}
