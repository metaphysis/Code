// Reverse Assignment
// UVa ID: 12062
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll LIMIT = 1000000000000000LL;          // 10^15
vector<int> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};
ll bestM;                                     // 当前最优答案

// 深度优先搜索
// remaining : 剩余待分解的因子 (即 (e+1) 的乘积)
// maxExp    : 上一个指数，保证非递增
// idx       : 当前使用的质数在 primes 中的下标
// cur       : 当前构造出的数
void dfs(int remaining, int maxExp, int idx, ll cur) {
    if (cur >= bestM) return;                 // 剪枝：不可能更优
    if (remaining == 1) {                     // 分解完毕，更新答案
        bestM = cur;
        return;
    }
    if (idx >= (int)primes.size()) return;    // 质数不够
    int p = primes[idx];
    int maxE = min(maxExp, remaining - 1);    // e+1 至少为 2，故 e <= remaining-1
    for (int e = 1; e <= maxE; ++e) {
        if (remaining % (e + 1) != 0) continue;
        // 计算 p^e，同时检测溢出
        ll power = 1;
        bool overflow = false;
        for (int i = 0; i < e; ++i) {
            if (power > LIMIT / p) { overflow = true; break; }
            power *= p;
        }
        if (overflow) continue;               // power 本身超限，跳过
        if (cur > LIMIT / power) continue;    // cur * power > LIMIT
        ll newCur = cur * power;
        dfs(remaining / (e + 1), e, idx + 1, newCur);
    }
}

int main() {
    int D, caseNo = 1;
    while (cin >> D && D != 0) {
        bestM = LLONG_MAX;
        if (D == 1) {
            cout << "Case " << caseNo++ << ": 1\n";
            continue;
        }
        dfs(D, D, 0, 1);                      // 初始 maxExp = D，cur = 1
        if (bestM == LLONG_MAX)
            cout << "Case " << caseNo++ << ": Impossible\n";
        else
            cout << "Case " << caseNo++ << ": " << bestM << '\n';
    }
    return 0;
}
