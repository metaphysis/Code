// Judge in Queue
// UVa ID: 12839
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.470s

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool check(ll x, const vector<ll>& w, const vector<ll>& t) {
    multiset<pair<ll, ll>> ms; // first=门槛, second=服务时间T
    for (ll ti : t) ms.insert({x, ti});
    for (ll wi : w) {
        auto it = ms.lower_bound({wi, -1}); // 找门槛>=wi且T最小的
        if (it == ms.end()) return false;
        auto cur = *it;
        ms.erase(it);
        cur.first -= cur.second; // 门槛下降
        ms.insert(cur);
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    for (int cas = 1; cas <= tc; ++cas) {
        int N, M;
        cin >> N >> M;
        vector<ll> W(N), T(M);
        for (int i = 0; i < N; ++i) cin >> W[i];
        for (int i = 0; i < M; ++i) cin >> T[i];
        sort(W.begin(), W.end(), greater<ll>());
        ll maxW = W[0];
        ll maxT = *max_element(T.begin(), T.end());
        ll low = maxW, high = maxW + (ll)(N - 1) * maxT;
        while (low < high) {
            ll mid = low + (high - low) / 2;
            if (check(mid, W, T)) high = mid;
            else low = mid + 1;
        }
        cout << "Case " << cas << ": " << low << "\n";
    }
    return 0;
}
