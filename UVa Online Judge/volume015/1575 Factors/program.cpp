// Factors
// UVa ID: 1575
// Verdict: Accepted
// Submission Date: 2025-12-02
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
typedef __int128 int128_t;

const ULL INF = (1ULL << 63);  // 上限 2^63
const int MAX_PRIME = 16;      // 使用的质数个数
int primes[MAX_PRIME] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
map<ULL, ULL> ans;             // 存储 n -> 最小 k

// 深度优先搜索枚举指数序列
void dfs(int idx, int lastExp, ULL currentVal, int128_t currentDiv, int sumExp) {
    // 只有当 currentDiv 可以表示为 ULL 时才记录
    if (currentDiv <= INF && currentDiv > 0) {
        ULL n = (ULL)currentDiv;
        if (ans.find(n) == ans.end() || currentVal < ans[n]) {
            ans[n] = currentVal;
        }
    }
    
    // 尝试添加下一个质因子
    for (int e = 1; e <= lastExp; e++) {
        // 计算新的 k 值
        if (currentVal > INF / primes[idx]) break;  // 乘法溢出检查
        ULL newVal = currentVal;
        for (int i = 0; i < e; i++) {
            if (newVal > INF / primes[idx]) {
                newVal = INF;
                break;
            }
            newVal *= primes[idx];
        }
        if (newVal >= INF) break;  // 超过上限
        
        // 计算新的 n 值：currentDiv * C(sumExp + e, e)
        // 使用 int128_t 计算组合数避免溢出
        int128_t newDiv = currentDiv;
        int s = sumExp;
        for (int i = 1; i <= e; i++) {
            newDiv = newDiv * (s + i) / i;
            if (newDiv > INF) break;  // 超过上限
        }
        if (newDiv > INF) continue;
        
        // 递归搜索下一个质数
        dfs(idx + 1, e, newVal, newDiv, sumExp + e);
    }
}

int main() {
    // 从第一个质数开始搜索
    for (int e = 62; e >= 1; e--) {
        ULL val = 1;
        for (int i = 0; i < e; i++) {
            if (val > INF / 2) {
                val = INF;
                break;
            }
            val *= 2;
        }
        if (val >= INF) continue;  // 超过上限
        
        // 对于单个质数的情况，currentDiv = 1
        dfs(1, e, val, (int128_t)1, e);
    }
    
    // 处理输入输出
    ULL n;
    while (cin >> n) {
        cout << n << " " << ans[n] << endl;
    }
    return 0;
}
