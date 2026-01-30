// Kings Wish
// UVa ID: 11773
// Verdict: Accepted
// Submission Date: 2026-01-17
// UVa Run Time: 0.230s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 位操作宏，用于埃拉托斯特尼筛法的位压缩存储
#define GET(x) (MASK[(x) >> 5] & (1 << ((x) & 0x1F)))
#define SET(x) (MASK[(x) >> 5] |= (1 << ((x) & 0x1F)))

typedef pair<long long, long long> pll;

const int MAXN = 1000010;          // 筛法上限，大于 sqrt(10^12)
int primes[MAXN >> 3], cnt;        // 素数表
int MASK[MAXN >> 5] = {3};         // 位数组，初始值3表示0和1不是素数

// 埃拉托斯特尼筛法，求出所有小于 MAXN 的素数
void sieve() {
    for (int i = 2; i < MAXN; i++) {
        if (!GET(i)) primes[cnt++] = i;          // i是素数
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++) {
            SET(i * primes[j]);                  // 标记合数
            if (i % primes[j] == 0) break;       // 保证每个数只被最小质因子标记
        }
    }
}

// 求解单个测试用例
pll solve(long long K) {
    long long KK = K;                            // 保存原始的 K
    map<long long, int> factor;                  // 质因数分解结果：质数 -> 指数
    // 用预处理的素数表分解 K
    for (int i = 0; i < cnt && primes[i] <= K; i++)
        while (K % primes[i] == 0) {
            factor[primes[i]]++;
            K /= primes[i];
        }
    // 如果剩余部分大于1，说明它是一个大于 MAXN 的质因子
    if (K > 1) factor[K]++;
    // 如果质因数个数不超过1（即 K 是质数或质数的幂），则无解
    if (factor.size() <= 1) return {-1, -1};
    vector<pll> answer;                          // 候选解列表
    // 对每个质因子构造候选解
    for (auto f : factor) {
        long long p = f.first;                   // 质因子
        int e = f.second;                        // 指数
        long long L = KK / p;                    // L = K / p
        long long W = pow(p, e);                 // W = p^e
        // 确保 L > W
        if (L < W) swap(L, W);
        answer.push_back({L, W});
    }
    // 按题目要求排序：先按 L-W 降序，再按周长降序
    sort(answer.begin(), answer.end(), [](pll a, pll b) {
        long long d1 = a.first - a.second, d2 = b.first - b.second;
        long long s1 = a.first + a.second, s2 = b.first + b.second;
        if (d1 != d2) return d1 > d2;
        return s1 > s2;
    });
    // 返回最优解
    return answer.front();
}

int main() {
    sieve();                                     // 预处理素数表
    int T;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        long long K;
        cin >> K;
        auto [L, W] = solve(K);                  // C++17 结构化绑定
        cout << "Case " << cs << ": ";
        if (L == -1) cout << "Impossible\n";
        else cout << L << ' ' << W << '\n';
    }
    return 0;
}
