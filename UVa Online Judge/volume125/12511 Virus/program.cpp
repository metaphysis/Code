// Virus
// UVa ID: 12511
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.070s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int LCIS(const vector<int>& A, const vector<int>& B) {
    int n = A.size();
    int m = B.size();
    vector<int> dp(m, 0);  // dp[j] 表示以 B[j] 结尾的 LCIS 长度
    
    for (int i = 0; i < n; i++) {
        int current = 0;  // 记录当前小于 A[i] 的 LCIS 的最大长度
        for (int j = 0; j < m; j++) {
            if (A[i] == B[j]) {
                // 找到公共元素，可以扩展 LCIS
                dp[j] = max(dp[j], current + 1);
            } else if (A[i] > B[j]) {
                // 如果 A[i] 更大，可以用于后续扩展
                if (dp[j] > current) {
                    current = dp[j];
                }
            }
        }
    }
    
    return *max_element(dp.begin(), dp.end());
}

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int n1;
        cin >> n1;
        vector<int> log1(n1);
        for (int i = 0; i < n1; i++) {
            cin >> log1[i];
        }
        
        int n2;
        cin >> n2;
        vector<int> log2(n2);
        for (int i = 0; i < n2; i++) {
            cin >> log2[i];
        }
        
        int ans = LCIS(log1, log2);
        cout << ans << endl;
    }
    
    return 0;
}
