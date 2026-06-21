// The Bells are Ringing
// UVa ID: 12119
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.090s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 i128;

vector<int> primes;

// 埃氏筛，生成 <= 1000000 的素数
void sieve() {
    const int N = 1000000;
    vector<bool> isComp(N + 1, false);
    for (int i = 2; i <= N; ++i) {
        if (!isComp[i]) {
            primes.push_back(i);
            if ((ll)i * i <= N)
                for (ll j = (ll)i * i; j <= N; j += i)
                    isComp[(int)j] = true;
        }
    }
}

// 求最大公约数（__int128 版本）
i128 gcd128(i128 a, i128 b) {
    while (b) {
        i128 r = a % b;
        a = b;
        b = r;
    }
    return a;
}

// 求最小公倍数（__int128 版本）
i128 lcm128(i128 a, i128 b) {
    return a / gcd128(a, b) * b;
}

// 分解 D，生成所有 <= 1e6 的约数，存入 divs，返回是否可能
bool getDivisors(ll D, vector<ll>& divs) {
    ll n = D;
    map<ll, int> fac;
    for (int p : primes) {
        if ((ll)p * p > n) break;
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) {
                n /= p;
                ++cnt;
            }
            fac[p] = cnt;
        }
    }
    if (n > 1) {
        if (n > 1000000) return false;  // 大质因子，无解
        fac[n] = 1;
    }

    // DFS 生成所有约数
    vector<pair<ll, int>> vec(fac.begin(), fac.end());
    function<void(int, ll)> dfs = [&](int idx, ll cur) {
        if (idx == (int)vec.size()) {
            if (cur >= 1 && cur <= 1000000)
                divs.push_back(cur);
            return;
        }
        ll val = 1;
        for (int e = 0; e <= vec[idx].second; ++e) {
            if (cur * val > 1000000) break;
            dfs(idx + 1, cur * val);
            val *= vec[idx].first;
        }
    };
    dfs(0, 1);

    sort(divs.begin(), divs.end());
    divs.erase(unique(divs.begin(), divs.end()), divs.end());
    return true;
}

int main() {
    sieve();
    int caseNo = 1;
    ll D;
    while (cin >> D && D) {
        vector<ll> divs;
        bool possible = getDivisors(D, divs);
        vector<tuple<ll, ll, ll>> ans;

        if (possible) {
            int m = (int)divs.size();
            for (int i = 0; i < m; ++i) {
                ll t1 = divs[i];
                for (int j = i + 2; j < m; ++j) {
                    ll t3 = divs[j];
                    if (t3 - t1 > 25) break;  // 后续差值更大，直接跳出
                    for (int k = i + 1; k < j; ++k) {
                        ll t2 = divs[k];
                        i128 L = lcm128(lcm128((i128)t1, (i128)t2), (i128)t3);
                        if (L == (i128)D) {
                            ans.emplace_back(t1, t2, t3);
                        }
                    }
                }
            }
            sort(ans.begin(), ans.end());
        }

        cout << "Scenario " << caseNo << ":" << endl;
        if (ans.empty()) {
            cout << "Such bells don't exist" << endl;
        } else {
            for (auto& tp : ans) {
                cout << get<0>(tp) << " " << get<1>(tp) << " " << get<2>(tp) << endl;
            }
        }
        cout << endl;
        ++caseNo;
    }
    return 0;
}
