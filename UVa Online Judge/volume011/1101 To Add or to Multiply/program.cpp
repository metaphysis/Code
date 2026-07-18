// To Add or to Multiply
// UVa ID: 1101
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 向上取整除法，b > 0
ll ceil_div(ll a, ll b) {
    if (a >= 0) return (a + b - 1) / b;
    return a / b;   // 负数时向零取整正好是上取整
}

// 向下取整除法，b > 0
ll floor_div(ll a, ll b) {
    if (a >= 0) return a / b;
    return - ((-a + b - 1) / b);
}

// 将 c[0..k] 对应的操作序列压缩成输出格式
string makeProgram(const vector<ll>& c, int k) {
    vector<pair<char, ll>> runs;
    auto addRun = [&](char ch, ll cnt) {
        if (cnt == 0) return;
        if (!runs.empty() && runs.back().first == ch)
            runs.back().second += cnt;
        else
            runs.push_back({ch, cnt});
    };
    for (int i = 0; i <= k; ++i) {
        if (c[i] > 0) addRun('A', c[i]);
        if (i < k) addRun('M', 1);
    }
    string res;
    for (size_t i = 0; i < runs.size(); ++i) {
        if (i) res += ' ';
        res += to_string(runs[i].second) + runs[i].first;
    }
    return res;
}

// 比较两个程序（只比较原始 A/M 字符串），返回 prog1 < prog2 是否成立
bool isLessRaw(const vector<ll>& c1, int k1, const vector<ll>& c2, int k2) {
    int i1 = 0, i2 = 0;
    ll a1 = 0, a2 = 0;   // 当前段已经输出的 A 个数
    while (true) {
        char ch1 = 0, ch2 = 0;
        // 取 prog1 的下一个字符
        if (i1 <= k1) {
            if (a1 < c1[i1]) {
                ch1 = 'A';
                ++a1;
            } else {
                if (i1 == k1) {
                    // 没有更多字符
                } else {
                    ch1 = 'M';
                    ++i1;
                    a1 = 0;
                }
            }
        }
        // 取 prog2 的下一个字符
        if (i2 <= k2) {
            if (a2 < c2[i2]) {
                ch2 = 'A';
                ++a2;
            } else {
                if (i2 == k2) {
                } else {
                    ch2 = 'M';
                    ++i2;
                    a2 = 0;
                }
            }
        }
        if (ch1 == 0 && ch2 == 0) return false;   // 完全相同
        if (ch1 == 0) return true;                // prog1 先结束（总长度应相同，不会发生）
        if (ch2 == 0) return false;
        if (ch1 != ch2) return ch1 < ch2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int caseNo = 1;
    ll a, m, p, q, r, s;
    while (cin >> a >> m >> p >> q >> r >> s) {
        if (a == 0 && m == 0 && p == 0 && q == 0 && r == 0 && s == 0) break;
        cout << "Case " << caseNo++ << ": ";
        // 空程序可用
        if (p >= r && q <= s) {
            cout << "empty\n";
            continue;
        }
        // 处理 m == 1 的情况：乘法无效，只用加法
        if (m == 1) {
            // 只有 k = 0，程序全由 A 组成
            // 需要 L = ceil((r - p) / a)，U = floor((s - q) / a)
            ll L = ceil_div(r - p, a);
            ll U = floor_div(s - q, a);
            if (L < 0) L = 0;
            if (L <= U) {
                // 选最小的加法次数，即 L
                if (L == 0) cout << "empty\n";
                else cout << L << "A\n";
            } else {
                cout << "impossible\n";
            }
            continue;
        }
        // m > 1
        ll bestN = LLONG_MAX;
        vector<ll> bestC;
        int bestK = 0;
        ll power = 1;   // m^k
        for (int k = 0; ; ++k) {
            if (k > 0) {
                if (power > s / m) break;
                power *= m;
            }
            if (q * power > s) break;   // 即使 S=0 也超出上限
            ll pPow = p * power;
            ll qPow = q * power;
            ll L = ceil_div(r - pPow, a);
            ll U = floor_div(s - qPow, a);
            if (L < 0) L = 0;
            if (U < 0 || L > U) {
                // 继续尝试更大的 k
                continue;
            }
            // 预计算 m 的各次幂，用于后续分解 S
            vector<ll> powM(k + 1, 1);
            for (int i = 1; i <= k; ++i) powM[i] = powM[i-1] * m;
            // 生成候选 S：L 以及将 L 的某低位清零并进位
            vector<ll> candidates;
            candidates.push_back(L);
            for (int t = 0; t <= k; ++t) {
                ll step = powM[t];   // m^t
                ll cand = (L / step + 1) * step;
                if (cand >= L && cand <= U) candidates.push_back(cand);
            }
            // 对每个候选计算其数字和（c_i 之和）以及总长度 N
            ll bestSum = LLONG_MAX;
            ll bestS = -1;
            for (ll S : candidates) {
                vector<ll> c(k + 1);
                ll tmp = S;
                for (int i = 0; i <= k; ++i) {
                    c[i] = tmp / powM[k - i];
                    tmp %= powM[k - i];
                }
                ll sum = 0;
                for (ll v : c) sum += v;
                if (sum < bestSum || (sum == bestSum && S > bestS)) {
                    bestSum = sum;
                    bestS = S;
                }
            }
            if (bestS == -1) continue;
            // 根据 bestS 还原 c
            vector<ll> c(k + 1);
            ll tmp = bestS;
            for (int i = 0; i <= k; ++i) {
                c[i] = tmp / powM[k - i];
                tmp %= powM[k - i];
            }
            ll N = k + bestSum;
            if (N < bestN || (N == bestN && isLessRaw(c, k, bestC, bestK))) {
                bestN = N;
                bestC = c;
                bestK = k;
            }
        }
        if (bestN == LLONG_MAX) {
            cout << "impossible\n";
        } else {
            if (bestN == 0) cout << "empty\n";
            else cout << makeProgram(bestC, bestK) << '\n';
        }
    }
    return 0;
}
