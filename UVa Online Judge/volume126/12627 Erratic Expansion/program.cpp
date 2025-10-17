// Erratic Expansion
// UVa ID: 12627
// Verdict: Accepted
// Submission Date: 2025-10-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
#include <map>
using namespace std;

map<pair<int, int>, long long> memo; // 记忆化存储

long long R(int K) {
    // 计算第K小时整个网格的红气球总数
    static long long pow3[31]; // 预计算3的幂次
    if (pow3[0] == 0) {
        pow3[0] = 1;
        for (int i = 1; i <= 30; i++)
            pow3[i] = pow3[i-1] * 3;
    }
    return pow3[K];
}

long long F(int K, int r) {
    if (r == 0) return 0; // 前0行没有气球
    if (K == 0) return 1; // 第0小时只有1行1个红气球
    if (memo.count({K, r})) return memo[{K, r}]; // 记忆化
    
    int half = 1 << (K-1); // 2^(K-1)
    long long res;
    
    if (r <= half) {
        // 只在上半部分
        res = 2 * F(K-1, r);
    } else {
        // 跨越上下两部分
        res = 2 * R(K-1) + F(K-1, r - half);
    }
    
    memo[{K, r}] = res; // 存储结果
    return res;
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int K, A, B;
        cin >> K >> A >> B;
        long long ans = F(K, B) - F(K, A-1); // 计算[A,B]行的红气球数
        cout << "Case " << t << ": " << ans << endl;
    }
    return 0;
}
