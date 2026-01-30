// Marbles in Jars
// UVa ID: 13032
// Verdict: Accepted
// Submission Date: 2026-01-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N;
        cin >> N;
        vector<int> M(N);
        for (int i = 0; i < N; ++i) cin >> M[i];
        
        // 如果有罐子不能取弹珠（M[i] == 0），则无解
        bool hasZero = false;
        for (int m : M) if (m == 0) hasZero = true;
        if (hasZero) {
            cout << "Case " << caseNo << ": 0\n";
            continue;
        }
        
        // 将 M 从小到大排序，方便计算
        sort(M.begin(), M.end());
        
        ll ans = 1;
        bool valid = true;
        for (int i = 0; i < N; ++i) {
            // 第 i 个罐子（排序后）可选的 X 值个数
            // 已经选了 i 个不同的数，还剩 M[i] - i 种选择
            int available = M[i] - i;
            if (available <= 0) {
                valid = false;
                break;
            }
            ans = ans * available % MOD;
        }
        
        if (!valid) ans = 0;
        cout << "Case " << caseNo << ": " << ans << "\n";
    }
    
    return 0;
}
