// Prime Darts
// UVa ID: 13245
// Verdict: Accepted
// Submission Date: 2026-04-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 生成前 maxCount 个质数
vector<int> generatePrimes(int maxCount) {
    vector<int> primes;
    for (int num = 2; primes.size() < maxCount; ++num) {
        bool isPrime = true;
        for (int p : primes) {
            if (p * p > num) break;
            if (num % p == 0) { isPrime = false; break; }
        }
        if (isPrime) primes.push_back(num);
    }
    return primes;
}

int main() {
    vector<int> primes = generatePrimes(100); // 最多需要前 99 个质数
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        
        // 构造分数面值列表
        vector<int> scores;
        scores.push_back(1);
        for (int i = 0; i < n - 1; ++i) scores.push_back(primes[i]);
        
        const int INF = 1e9;
        vector<int> dp(q + 1, INF);
        dp[0] = 0;
        
        // 完全背包，求最少个数
        for (int score : scores)
            for (int v = score; v <= q; ++v)
                if (dp[v - score] != INF)
                    dp[v] = min(dp[v], dp[v - score] + 1);
        
        cout << dp[q] << endl;
    }
    return 0;
}
