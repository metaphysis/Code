// GCD Guessing Game
// UVa ID: 1521
// Verdict: Accepted
// Submission Date: 2025-11-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10005;
vector<int> primes;
bool vis[MAX_N];

// 预处理：使用筛法生成所有质数
void initPrimes() {
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i < MAX_N; i++) {
        if (!vis[i]) {
            primes.push_back(i);
            for (int j = i + i; j < MAX_N; j += i) {
                vis[j] = true;
            }
        }
    }
}

int main() {
    initPrimes();
    int n;
    while (cin >> n) {
        int head = 0;
        int tail = primes.size() - 1;
        int ans = 0;
        
        // 调整tail到不超过n的最大质数
        while (tail >= 0 && primes[tail] > n) tail--;
        
        // 双指针分组策略
        while (head <= tail) {
            int product = primes[tail];  // 从当前最大的质数开始
            // 尽量乘上更多的小质数，但保证乘积不超过n
            while (head < tail && product * primes[head] <= n) {
                product *= primes[head];
                head++;
            }
            ans++;   // 完成一组猜测
            tail--;  // 处理下一个大质数
        }
        
        cout << ans << endl;
    }
    return 0;
}
