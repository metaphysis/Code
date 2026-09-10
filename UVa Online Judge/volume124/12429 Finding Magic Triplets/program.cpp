// Finding Magic Triplets
// UVa ID: 12429
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.930s

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

class Fenwick {
    int n;
    vector<int> bit;
public:
    Fenwick(int n) : n(n), bit(n + 1, 0) {}
    void add(int idx, int val) {
        for (++idx; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    int sumPrefix(int idx) {
        int res = 0;
        for (++idx; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }
    int rangeSum(int l, int r) {
        if (l > r) return 0;
        return sumPrefix(r) - (l ? sumPrefix(l - 1) : 0);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int n, k;
        cin >> n >> k;
        if (k == 1) {
            ll ans = 1LL * n * (n + 1) * (n + 2) / 6;
            cout << "Case " << caseNo << ": " << ans << '\n';
            continue;
        }
        vector<int> valC(n + 1);
        vector<int> cntAll(k, 0);
        for (int c = 1; c <= n; ++c) {
            ll cube = (1LL * c * c % k) * c % k;
            valC[c] = (int)cube;
            cntAll[valC[c]]++;
        }
        vector<int> prefC(k + 1, 0);
        for (int i = 0; i < k; ++i) prefC[i + 1] = prefC[i] + cntAll[i];
        auto queryC = [&](int start, int len) -> ll {
            if (len == 0) return 0;
            ll res;
            if (start + len <= k) {
                res = prefC[start + len] - prefC[start];
            } else {
                res = (prefC[k] - prefC[start]) + prefC[(start + len) % k];
            }
            return res;
        };
        Fenwick bit(k);
        ll ans = 0;
        for (int b = 1; b <= n; ++b) {
            int S = (1LL * b * b) % k;
            int start = (S + 1) % k;
            int q = b / k;
            int rem = b % k;
            ll A = 1LL * q * n + queryC(start, rem);
            ll totalP = b - 1;
            ll B = 1LL * q * totalP;
            if (rem > 0) {
                if (start + rem <= k) {
                    B += bit.rangeSum(start, start + rem - 1);
                } else {
                    B += bit.rangeSum(start, k - 1);
                    B += bit.rangeSum(0, (start + rem - 1) % k);
                }
            }
            ans += A - B;
            bit.add(valC[b], 1);
        }
        cout << "Case " << caseNo << ": " << ans << '\n';
    }
    return 0;
}
