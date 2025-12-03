// Hyper-drive
// UVa ID: 10542
// Verdict: Accepted
// Submission Date: 2025-12-01
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, a[12];  // a[i]存储第i个维度的坐标差绝对值

ll solve() {
    // 检查是否有任何维度差为0
    for (int i = 0; i < n; i++)
        if (a[i] == 0) return 0;
    
    ll r = 0;
    // 遍历所有非空子集 (2^n - 1 个子集)
    for (int S = 1; S < (1 << n); S++) {
        int cnt = 0;  // 子集中元素个数
        ll d = 0;     // 子集中所有元素的最大公约数
        
        for (int i = 0; i < n; i++) {
            if (S & (1 << i)) {
                cnt++;
                d = __gcd(a[i], d);
            }
        }
        
        // 容斥原理：奇数个元素加，偶数个元素减
        if (cnt & 1) r += d;    // 奇数个元素，加
        else r -= d;    // 偶数个元素，减
    }
    return r;
}

int main() {
    int T;
    cin >> T;
    
    for (int cs = 1; cs <= T; cs++) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        
        // 读取Q点，计算坐标差的绝对值
        for (int i = 0, x; i < n; i++) {
            cin >> x;
            a[i] = abs(a[i] - x);
        }
        
        cout << "Case " << cs << ": " << solve() << '\n';
    }
    return 0;
}
