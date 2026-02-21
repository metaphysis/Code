// VOID
// UVa ID: 12574
// Verdict: Accepted
// Submission Date: 2026-02-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007; // 定义模数

int main() {
    ios_base::sync_with_stdio(false); // 关闭同步，提高输入输出效率
    cin.tie(nullptr); // 解除 cin 和 cout 的绑定
    int T; // 测试用例数
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        long long product = 1; // 存储 (W_i + 1) 的乘积
        long long sumW = 0;    // 存储 W_i 的总和
        for (int i = 0; i < N; i++) {
            long long W;
            cin >> W;
            product = product * ((W + 1) % MOD) % MOD; // 累乘并取模
            sumW = (sumW + W) % MOD; // 累加并取模
        }
        // 计算最终答案：product - 1 - sumW，注意处理负数
        long long r = (product - 1 - sumW + MOD) % MOD;
        cout << r << '\n'; // 输出结果
    }
    return 0;
}
