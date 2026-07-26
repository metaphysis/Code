// Next Generation Macaw
// UVa ID: 12593
// Verdict: Accepted
// Submission Date: 2026-07-26
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163220824

#include <bits/stdc++.h>
using namespace std;

const int MOD = 10007;

// 多项式乘法并模特征多项式 x^k = x^(k-2) + x^(k-3) + ... + 1
vector<int> multiply(const vector<int>& a, const vector<int>& b, int k) {
    int len = 2 * k - 1;
    vector<int> res(len, 0);
    for (int i = 0; i < k; ++i) if (a[i])
        for (int j = 0; j < k; ++j) if (b[j])
            res[i + j] = (res[i + j] + a[i] * b[j]) % MOD;
    for (int d = len - 1; d >= k; --d) {
        int coef = res[d];
        if (!coef) continue;
        for (int i = 2; i <= k; ++i) {
            int idx = d - i;
            if (idx >= 0) res[idx] = (res[idx] + coef) % MOD;
        }
        res[d] = 0;
    }
    res.resize(k);
    return res;
}

// 计算 x^exp 模特征多项式，返回次数 < k 的多项式
vector<int> polyPow(long long exp, int k) {
    vector<int> result(k, 0), base(k, 0);
    result[0] = 1;
    if (k > 1) base[1] = 1; // x
    while (exp) {
        if (exp & 1) result = multiply(result, base, k);
        base = multiply(base, base, k);
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        long long n;
        int k;
        cin >> n >> k;
        // 计算 B[1..k]，B[i]=0 for i<=0
        vector<int> B(k + 1, 0);
        B[1] = 1;
        for (int i = 2; i <= k; ++i) {
            int sum = 0;
            for (int j = 2; j <= k; ++j) {
                if (i - j >= 1) sum = (sum + B[i - j]) % MOD;
                // 当 i-j<=0 时 B 为 0，无需处理
            }
            B[i] = sum % MOD;
        }
        // 构建初始状态 V_i = [B(i), B(i-1), ..., B(i-k+1)]，i=1..k
        vector<vector<int>> states(k + 1, vector<int>(k, 0));
        for (int i = 1; i <= k; ++i) {
            for (int j = 0; j < k; ++j) {
                int idx = i - j;
                if (idx >= 1) states[i][j] = B[idx];
                else states[i][j] = 0;
            }
        }
        // 计算 x^(n-1) 模特征多项式
        vector<int> Q = polyPow(n - 1, k);
        // 计算 V_n = sum Q[i] * V_{i+1}
        vector<int> vn(k, 0);
        for (int i = 0; i < k; ++i) {
            if (!Q[i]) continue;
            for (int j = 0; j < k; ++j) {
                vn[j] = (vn[j] + Q[i] * states[i + 1][j]) % MOD;
            }
        }
        // 总对数为 V_n 所有元素之和
        int pairs = 0;
        for (int j = 0; j < k; ++j) pairs = (pairs + vn[j]) % MOD;
        int ans = (2 * pairs) % MOD;
        cout << "Case " << caseNo << ": " << ans << '\n';
    }
    return 0;
}
