// OOPS! They did it Again...
// UVa ID: 10799
// Verdict: Accepted
// Submission Date: 2025-12-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 计算 k=2 时的方案数
ll solveK2(ll low, ll high) {
    ll n = high - low;           // 注意：是 high-low，不是 high-low+1
    ll m = n / 2;                // 偶数 d 的个数
    return m * n - m * m;        // 等差数列求和公式
}

// 计算 k>2 时的方案数
ll solveK(ll low, ll high, ll k) {
    ll maxD = (high - low) / (k - 1);  // 最大公差
    ll ans = 0;
    
    for (ll d = 1; d <= maxD; ++d) {
        // 条件：(k-1)*d 必须是偶数
        if (((k - 1) * d) & 1) continue;
        
        ll cnt = high - (k - 1) * d - low + 1;
        if (cnt > 0) ans += cnt;
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll low, high, k;
    int caseNo = 1;
    
    while (cin >> low >> high >> k) {
        if (low == 0 && high == 0 && k == 0) break;
        
        ll ans;
        if (k == 2) ans = solveK2(low, high);
        else ans = solveK(low, high, k);
        
        cout << "Case " << caseNo++ << ": " << ans << "\n";
    }
    
    return 0;
}
