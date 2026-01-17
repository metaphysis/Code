// Prime Suspect
// UVa ID: 10956
// Verdict: Accepted
// Submission Date: 2026-01-09
// UVa Run Time: 0.350s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 快速幂取模，使用 __int128 防止溢出
unsigned long long powMod(unsigned long long a, unsigned long long b, unsigned long long m) {
    unsigned long long r = 1;
    a %= m;
    while (b) {
        if (b & 1) r = (unsigned long long)((__int128)r * a % m);
        a = (unsigned long long)((__int128)a * a % m);
        b >>= 1;
    }
    return r;
}

// 确定性 Miller-Rabin 素性测试
bool isPrime(unsigned long long n) {
    // 基本情况
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    // 小素数快速试除
    static const unsigned smallPrimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (unsigned p : smallPrimes)
        if (n % p == 0) return false;
    // 分解 n-1 = 2^s * d，其中 d 是奇数
    unsigned long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    // 使用三个基数进行测试（对于32位整数是确定性的）
    unsigned long long bases[] = {2, 7, 61};
    for (unsigned long long a : bases) {
        if (a % n == 0) continue;    // 如果 a 能被 n 整除，跳过
        unsigned long long x = powMod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        // 进行 s-1 次平方
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = (unsigned long long)((__int128)x * x % n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false; // 确定是合数
    }
    return true; // 通过所有测试，是素数
}

// 严格按照题目描述的 Suspect 函数
bool suspect(unsigned b, unsigned long long n) {
    // n 必须是大于2的奇数
    if (n < 3 || n % 2 == 0) return false;
    // 步骤1：分解 n-1 = 2^t * u
    int t = 0;
    unsigned long long u = n - 1;
    while (u % 2 == 0) {
        u /= 2;
        t++;
    }
    // 步骤2：计算 x0 = b^u mod n
    unsigned long long x0 = powMod(b, u, n);
    // 如果 x0 为 1 或 n-1，直接返回 TRUE
    if (x0 == 1 || x0 == n - 1) return true;
    // 步骤3-4：迭代计算 xi = (x_{i-1})^2 mod n
    for (int i = 1; i <= t; i++) {
        unsigned long long xi = (unsigned long long)((__int128)x0 * x0 % n);
        // 如果 xi == 1
        if (xi == 1) {
            // 检查失败条件：x_{i-1} ≠ 1 且 x_{i-1} ≠ n-1
            if (x0 != 1 && x0 != n - 1) return false; // 确定是合数
            return true;      // 可能是素数
        }
        x0 = xi;
    }
    // 步骤5：检查 x_t 是否等于 1
    return x0 == 1;
}

int main() {
    // 加速输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool first = true;          // 标记是否为第一个测试用例
    unsigned base;
    unsigned long long minV, maxV;
    while (cin >> base >> minV >> maxV) {
        // 输入结束条件
        if (base == 0 && minV == 0 && maxV == 0) break;
        // 输出空行分隔（除了第一个用例）
        if (!first) cout << '\n';
        first = false;
        unsigned long long oddComposites = 0; // 奇数合数计数
        vector<unsigned long long> fails;     // 失败数列表
        // 保存原始范围，用于输出
        unsigned long long origMin = minV, origMax = maxV;
        // 调整起始值，确保从奇数开始遍历
        if (minV % 2 == 0) minV++;
        // 遍历范围内的所有奇数
        for (unsigned long long n = minV; n <= maxV; n += 2) {
            if (n == 1) continue; // 跳过1（1不是素数也不是合数）
            bool prime = isPrime(n);
            if (!prime) {
                oddComposites++; // 统计奇数合数
                // 检查是否失败（即合数但 Suspect 返回 TRUE）
                if (suspect(base, n)) fails.push_back(n);
            }
        }
        // 输出统计信息
        cout << "There are " << oddComposites 
             << " odd non-prime numbers between "
             << origMin << " and " << origMax << ".\n";
        // 输出失败案例（如果有）
        if (!fails.empty()) {
            cout << fails.size() << " suspects fail in base " << base << ":\n";
            for (auto f : fails) cout << f << '\n';
        } else cout << "There are no failures in base " << base << ".\n";
    }
    return 0;
}
