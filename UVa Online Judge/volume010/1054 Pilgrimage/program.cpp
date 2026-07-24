// Pilgrimage
// UVa ID: 1054
// Verdict: Accepted
// Submission Date: 2026-07-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Op { string type; ll num; };

vector<ll> getFactors(ll x) {
    vector<ll> f;
    for (ll i = 1; i * i <= x; ++i) {
        if (x % i == 0) {
            f.push_back(i);
            if (i != x / i) f.push_back(x / i);
        }
    }
    return f;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (true) {
        int N;
        cin >> N;
        if (N == 0) break;
        vector<Op> ops(N);
        for (int i = 0; i < N; ++i) cin >> ops[i].type >> ops[i].num;

        vector<int> idx;
        vector<ll> dList;
        vector<pair<ll, ll>> outs;
        ll d = 0;
        dList.push_back(0);
        for (int i = 0; i < N; ++i) {
            if (ops[i].type == "IN" || ops[i].type == "OUT") {
                ll dBefore = d;
                idx.push_back(i);
                dList.push_back(dBefore);
                if (ops[i].type == "OUT") outs.push_back({dBefore, ops[i].num});
                if (ops[i].type == "IN") d += ops[i].num;
                else d -= ops[i].num;
                dList.push_back(d);
            }
        }

        ll L = 1;
        for (ll dd : dList) L = max(L, 1 - dd);
        for (auto &p : outs) {
            ll dBefore = p.first, k = p.second;
            L = max(L, k + 1 - dBefore);
        }

        if (idx.empty()) {
            cout << "SIZE >= " << L << "\n";
            continue;
        }

        vector<pair<ll, ll>> constraints;
        for (size_t i = 0; i + 1 < idx.size(); ++i) {
            int start = idx[i] + 1, end = idx[i + 1] - 1;
            ll sum = 0;
            for (int j = start; j <= end; ++j) {
                if (ops[j].type == "PAY") sum += ops[j].num;
            }
            if (sum == 0) continue;
            ll dAfter = 0;
            ll tmp = 0;
            for (int j = 0; j <= idx[i]; ++j) {
                if (ops[j].type == "IN") tmp += ops[j].num;
                else if (ops[j].type == "OUT") tmp -= ops[j].num;
            }
            dAfter = tmp;
            constraints.push_back({dAfter, sum});
        }

        if (constraints.empty()) {
            cout << "SIZE >= " << L << "\n";
            continue;
        }

        ll dFirst = constraints[0].first, xFirst = constraints[0].second;
        vector<ll> factors = getFactors(xFirst);
        vector<ll> candidates;
        for (ll factor : factors) {
            ll S0 = factor - dFirst;
            if (S0 >= L) candidates.push_back(S0);
        }
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

        for (size_t k = 1; k < constraints.size(); ++k) {
            ll dNow = constraints[k].first, xNow = constraints[k].second;
            vector<ll> filtered;
            for (ll S0 : candidates) {
                ll S = S0 + dNow;
                if (S > 0 && xNow % S == 0) filtered.push_back(S0);
            }
            candidates = filtered;
            if (candidates.empty()) break;
        }

        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

        if (candidates.empty()) {
            cout << "IMPOSSIBLE\n";
        } else if (candidates.size() == 1) {
            cout << candidates[0] << "\n";
        } else {
            for (size_t i = 0; i < candidates.size(); ++i) {
                if (i) cout << " ";
                cout << candidates[i];
            }
            cout << "\n";
        }
    }
    return 0;
}
