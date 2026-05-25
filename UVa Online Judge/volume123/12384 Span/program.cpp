// Span
// UVa ID: 12384
// Verdict: Accepted
// Submission Date: 2026-05-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

// 全局素数列表
vector<int> primes;

// 埃氏筛，生成所有不超过 limit 的素数
void sieve(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= limit; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
            if ((long long)i * i <= limit) {
                for (int j = i * i; j <= limit; j += i)
                    isPrime[j] = false;
            }
        }
    }
}

int main() {
    // 预先生成足够多的素数（第 100000 个素数约 1299709，取 2e6 安全）
    const int MAX_PRIME_LIMIT = 2000000;
    sieve(MAX_PRIME_LIMIT);

    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        // 步骤1：生成 X 数组
        vector<int> X(n);
        for (int i = 0; i < n; ++i) X[i] = primes[i] % m;

        // 步骤2：单调栈计算 span
        vector<int> S(n);
        stack<int> st; // 存下标，维护 X[st] 递减
        long long totalSum = 0;

        for (int i = 0; i < n; ++i) {
            while (!st.empty() && X[st.top()] <= X[i]) st.pop();
            if (st.empty()) S[i] = i + 1;
            else S[i] = i - st.top();
            st.push(i);
            totalSum += S[i];
        }

        // 输出 sum % m
        printf("%lld\n", totalSum % m);
    }
    return 0;
}
