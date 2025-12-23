// Just Make A Wish
// UVa ID: 12619
// Verdict: Accepted
// Submission Date: 2025-12-17
// UVa Run Time: 0.200s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAX = 2000005; // 足够大，因为 G 最大 1e6，但面积质因子可能更大
const LL MOD = 1000000007LL;

vector<int> lpf; // 最小质因子 Least Prime Factor
vector<LL> inv; // 模逆元

// 快速幂取模
LL modPow(LL a, LL b) {
    LL res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// 预处理最小质因子和逆元
void init() {
    lpf.resize(MAX, 0);
    inv.resize(MAX, 0);
    for (int i = 2; i < MAX; i++) {
        if (lpf[i] == 0) { // i 是质数
            lpf[i] = i;
            for (int j = i + i; j < MAX; j += i) {
                if (lpf[j] == 0) lpf[j] = i;
            }
        }
    }
    // 预处理逆元： inv[x] = x^(-1) mod MOD
    for (int i = 1; i < MAX; i++) inv[i] = modPow(i, MOD - 2);
}

// 分解 x，返回质因子-指数的映射
vector<pair<int, int>> factorize(int x) {
    vector<pair<int, int>> res;
    while (x > 1) {
        int p = lpf[x];
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        res.push_back({p, cnt});
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init(); // 预处理

    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; caseNo++) {
        int D;
        cin >> D;

        unordered_map<int, int> expMap; // 当前面积的质因子指数
        LL divCount = 1; // 当前面积的因子个数
        LL sumWays = 0;

        for (int day = 0; day < D; day++) {
            int G;
            cin >> G;
            int val = abs(G);
            vector<pair<int, int>> factors = factorize(val);

            if (G > 0) { // 乘以 val
                for (auto &pf : factors) {
                    int p = pf.first, e = pf.second;
                    int oldExp = expMap[p];
                    int newExp = oldExp + e;
                    // 更新因子个数：除以(oldExp+1)，乘以(newExp+1)
                    divCount = divCount * inv[oldExp + 1] % MOD;
                    divCount = divCount * (newExp + 1) % MOD;
                    expMap[p] = newExp;
                }
            } else { // 除以 val
                for (auto &pf : factors) {
                    int p = pf.first, e = pf.second;
                    int oldExp = expMap[p];
                    int newExp = oldExp - e;
                    divCount = divCount * inv[oldExp + 1] % MOD;
                    divCount = divCount * (newExp + 1) % MOD;
                    expMap[p] = newExp;
                }
            }

            sumWays = (sumWays + divCount) % MOD;
        }

        cout << "Case " << caseNo << ": " << sumWays << "\n";
    }

    return 0;
}
