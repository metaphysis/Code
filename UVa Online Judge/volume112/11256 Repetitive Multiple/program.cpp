// Repetitive Multiple
// UVa ID: 11256
// Verdict: Accepted
// Submission Date: 2026-01-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string solve(ll n) {
    // 计算 n 的位数 L
    int L = to_string(n).size();
    string best; // 存储最小解
    // 枚举总位数 totalLen，从 L 到 2L
    for (int x = L; x <= 2 * L; x++) {
        // 枚举重复单元的长度 len
        for (int y = 1; y <= x / 2; y++) {
            if (x % y != 0) continue; // len 必须是 totalLen 的因子
            int k = x / y; // 重复次数
            if (k < 2) continue; // 至少重复两次
            // 计算 y = (10^totalLen - 1) / (10^len - 1)
            ll z = (pow(10, x) - 1) / (pow(10, y) - 1);
            // 计算 n1 = n / gcd(y, n)
            ll nn = n / __gcd(n, z);
            // len 位数的范围
            ll least = pow(10, y - 1);      // 最小 len 位数
            ll greatest = pow(10, y) - 1;   // 最大 len 位数
            // 计算最小的 base = ceil(least / nn) * nn
            ll base = ((least + nn - 1) / nn) * nn;
            if (base > greatest) continue; // base 超出范围
            // 构造重复数：将 base 重复 k 次拼接
            string s;
            for (int i = 0; i < k; i++) s += to_string(base);
            // 更新最小解（字符串比较即数值比较）
            if (best.empty() || s < best) best = s;
        }
        // 一旦找到解就退出，因为 totalLen 从小到大枚举
        if (best.size()) break;
    }
    return best;
}

int main() {
    int N;
    cin >> N;
    while (N--) {
        ll n;
        cin >> n;
        cout << solve(n) << '\n';
    }
    return 0;
}
