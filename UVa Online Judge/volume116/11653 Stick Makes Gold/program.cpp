// Stick Makes Gold
// UVa ID: 11653
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.220s

#include <bits/stdc++.h>
using namespace std;

using U64 = unsigned long long;

void addRange(vector<U64>& d0, vector<U64>& d1, vector<U64>& d2, vector<U64>& d3, int t, int a, int b) {
    U64 u = (U64)(1 - a), c0 = 0, c1 = 0, c2 = 0, c3 = 0;
    if (t == 1) {
        c0 = u;
        c1 = 1;
    } else if (t == 2) {
        c0 = u * u;
        c1 = 2 * u;
        c2 = 1;
    } else {
        c0 = u * u * u;
        c1 = 3 * u * u;
        c2 = 3 * u;
        c3 = 1;
    }
    d0[a] += c0;
    d0[b] -= c0;
    d1[a] += c1;
    d1[b] -= c1;
    d2[a] += c2;
    d2[b] -= c2;
    d3[a] += c3;
    d3[b] -= c3;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testNum;
    cin >> testNum;
    for (int caseId = 1; caseId <= testNum; ++caseId) {
        int n, m;
        cin >> n >> m;
        vector<U64> d0(n + 1), d1(n + 1), d2(n + 1), d3(n + 1);
        for (int i = 0; i < m; ++i) {
            int t, a, b;
            cin >> t >> a >> b;
            addRange(d0, d1, d2, d3, t, a, b);
        }
        int q;
        cin >> q;
        vector<int> query(q);
        for (int i = 0; i < q; ++i) cin >> query[i];
        cout << "Case " << caseId << ":\n";
        U64 cur0 = 0, cur1 = 0, cur2 = 0, cur3 = 0, sum = 0;
        int index = 0;
        for (int x = 0; x <= n; ++x) {
            while (index < q && query[index] == x) {
                cout << sum << '\n';
                ++index;
            }
            if (x == n) break;
            cur0 += d0[x];
            cur1 += d1[x];
            cur2 += d2[x];
            cur3 += d3[x];
            sum += ((cur3 * (U64)x + cur2) * (U64)x + cur1) * (U64)x + cur0;
        }
    }
    return 0;
}
