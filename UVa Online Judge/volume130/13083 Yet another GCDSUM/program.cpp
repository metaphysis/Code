// Yet another GCDSUM
// UVa ID: 13083
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 线性筛法求 1e7 以内的所有质数
const int MAXP = 10000000;
vector<int> primes;
vector<int> lp(MAXP + 1, 0);

void sieve() {
    for (int i = 2; i <= MAXP; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > lp[i] || 1LL * i * p > MAXP) break;
            lp[i * p] = p;
        }
    }
}

// 分解质因数，返回 vector<pair<质数, 指数>>
vector<pair<long long, int>> factorize(long long n) {
    vector<pair<long long, int>> fac;
    for (int p : primes) {
        if (1LL * p * p > n) break;
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) {
                n /= p;
                ++cnt;
            }
            fac.push_back({p, cnt});
        }
    }
    if (n > 1) fac.push_back({n, 1});
    return fac;
}

vector<pair<long long, int>> factors; // 当前 N 的质因数分解
int k;                                // 质因数个数
__int128 ans;                         // 累加答案（防止中间溢出）

// DFS 枚举所有因子指数组合
// idx    : 当前处理的质因数下标
// phi    : 当前因子 d 的欧拉函数值
// tau    : 当前已选指数对应的 (N/d) 因子个数部分乘积
void dfs(int idx, long long phi, long long tau) {
    if (idx == k) {
        ans += (__int128)phi * tau * tau;
        return;
    }
    long long p = factors[idx].first;
    int a = factors[idx].second;
    long long curPow = 1; // p^b，b 从 0 开始
    for (int b = 0; b <= a; ++b) {
        long long newPhi = phi;
        if (b > 0) {
            // 计算 phi(p^b) = p^{b-1} * (p-1)
            long long pPowBminus1 = curPow / p; // curPow == p^b
            newPhi = (long long)((__int128)phi * (p - 1) * pPowBminus1);
        }
        long long newTau = tau * (a - b + 1);
        dfs(idx + 1, newPhi, newTau);
        curPow *= p; // 准备下一个指数
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        long long N;
        cin >> N;

        factors = factorize(N);
        k = (int)factors.size();
        ans = 0;
        dfs(0, 1, 1); // 初始 d=1, phi(1)=1, tau=1

        cout << "Case " << caseNo << ": " << (long long)ans << '\n';
    }
    return 0;
}
