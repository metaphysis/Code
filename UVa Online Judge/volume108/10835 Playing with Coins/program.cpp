// Playing with Coins
// UVa ID: 10835
// Verdict: Accepted
// Submission Date: 2025-12-22
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

set<int> forbidden;  // 存储禁止模式的位掩码
int N, K, M;         // N:总长度, K:禁止模式数, M:模式长度
long long dp[64][1024];  // dp[i][j]: 长度i，最后M位的掩码为j

// 记忆化搜索
long long dfs(int length, int mask) {
    if (length >= N) return 1LL;  // 找到一个安全序列
    if (~dp[length][mask]) return dp[length][mask];  // 记忆化
    
    long long &r = dp[length][mask];
    r = 0;
    
    // 尝试添加 H(1) 或 T(0)
    for (int i = 0; i <= 1; i++) {
        int nextMask = (((mask << 1) & ((1 << M) - 1))) | i;
        // 只有长度足够时才检查禁止模式
        if (length < M - 1 || !forbidden.count(nextMask))
            r += dfs(length + 1, nextMask);
    }
    return r;
}

int main() {
    int caseNo = 1;
    while (cin >> N >> K, N) {
        cout << "Case " << caseNo++ << ": ";
        forbidden.clear();
        
        // 读入禁止模式并转换为位掩码
        for (int i = 0; i < K; i++) {
            string pattern;
            cin >> pattern;
            M = pattern.length();
            int mask = 0;
            for (auto p : pattern) mask = (mask << 1) | (p == 'H' ? 1 : 0);
            forbidden.insert(mask);
        }
        
        // 特殊情况处理：没有禁止模式或模式长度大于序列长度
        if (K == 0 || M > N) {
            cout << "1/1\n";
            continue;
        }
        
        // 动态规划计算安全序列数
        memset(dp, -1, sizeof dp);
        long long safe = dfs(0, 0);
        
        // 输出结果
        if (safe == 0) cout << "0\n";
        else {
            long long total = 1LL << N;
            long long g = __gcd(safe, total);
            cout << safe / g << '/' << total / g << '\n';
        }
    }
    return 0;
}
