// BFS(Binary Fibonacci String)
// UVa ID: 12041
// Verdict: Accepted
// Submission Date: 2025-11-17
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long fib[64]; // 存储BFS(n)的长度，即斐波那契数列，fib[0]=|BFS(0)|=1, fib[1]=|BFS(1)|=1

// 递归查找BFS(n)中第pos个字符（0-based）
char getCharAt(long long n, long long pos) {
    if (n == 0) return '0'; // 基础情况：BFS(0) = "0"
    if (n == 1) return '1'; // 基础情况：BFS(1) = "1"
    // BFS(n) = BFS(n-2) + BFS(n-1)
    if (pos < fib[n - 2]) return getCharAt(n - 2, pos);      // 字符在前半部分(BFS(n-2))
    else return getCharAt(n - 1, pos - fib[n - 2]); // 字符在后半部分(BFS(n-1))
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // 预计算斐波那契数列作为BFS字符串的长度
    fib[0] = fib[1] = 1; // BFS(0)和BFS(1)的长度都是1
    for (int i = 2; i < 64; i++) fib[i] = fib[i - 1] + fib[i - 2]; // 斐波那契递推
    int t;
    cin >> t;
    while (t--) {
        long long n, i, j;
        cin >> n >> i >> j;
        // 关键优化：当n过大时，压缩到50或51（保持奇偶性）
        // 因为斐波那契数增长极快，BFS(50)长度已远超题目最大索引2^31-1
        // 保持奇偶性确保字符串开头字符正确（奇数n以'1'开头，偶数n以'0'开头）
        if (n >= 50) n = 50 + (n % 2);
        // 输出BFS(n)中从位置i到j的子串
        for (long long pos = i; pos <= j; pos++)
            cout << getCharAt(n, pos);
        cout << '\n';
    }
    return 0;
}
