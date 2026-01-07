// Common Palindrome
// UVa ID: 12473
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 4.600s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int dp[61][61][61][61];
string A, B;
int n, m;

int dfs(int i, int j, int k, int l) {
    if (i > j || k > l) return 0;
    int &r = dp[i][j][k][l];
    if (~r) return r;
    r = 0;
    // 尝试匹配 A[i] 和 A[j]（如果 i != j）作为回文的两端
    if (i == j) {
        // 单个字符
        char ch = A[i];
        for (int p = k; p <= l; ++p)
            if (B[p] == ch) return r = 1;
        return r = 0;
    } else {
        // 情况1：不使用 A[i] 和 A[j]
        r = max(r, dfs(i + 1, j, k, l));
        r = max(r, dfs(i, j - 1, k, l));
        // 情况2：如果 A[i] == A[j]，尝试在 B 中找到匹配的相同字符作为两端
        if (A[i] == A[j]) {
            // 在 B 中寻找两个位置 p, q (k <= p < q <= l) 使得 B[p] == B[q] == A[i]
            for (int p = k; p <= l; ++p) {
                if (B[p] == A[i]) {
                    for (int q = p + 1; q <= l; ++q) {
                        if (B[q] == A[i]) {
                            // 找到一对匹配
                            int inner = dfs(i + 1, j - 1, p + 1, q - 1);
                            r = max(r, inner + 2);
                        }
                    }
                }
            }
        }
        // 情况3：尝试用 A[i] 匹配 B 中的某个字符，或者用 A[j] 匹配 B 中的某个字符
        // 这里通过递归已经覆盖
    }
    return r;
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        cin >> A >> B;
        n = A.size(), m = B.size();
        memset(dp, -1, sizeof(dp));
        cout << "Case " << t << ": " << dfs(0, n - 1, 0, m - 1) << '\n';
    }
    return 0;
}
