// Best Friend
// UVa ID: 12425
// Verdict: Accepted
// Submission Date: 2025-11-16
// UVa Run Time: 0.090s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> getDivisors(ll n, const vector<ll>& factors) {
    vector<ll> divisors = {1};
    for (auto p : factors) {
        ll prime = p;
        int count = 0;
        while (n % p == 0) {
            n /= p;
            count++;
        }
        int sz = divisors.size();
        ll multiplier = 1;
        for (int i = 0; i < count; i++) {
            multiplier *= prime;
            for (int j = 0; j < sz; j++) {
                divisors.push_back(divisors[j] * multiplier);
            }
        }
    }
    return divisors;
}

ll eulerPhi(ll n, const vector<ll>& factors) {
    ll ans = n;
    for (auto p : factors) {
        if (n % p == 0) {
            ans -= ans / p;
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) ans -= ans / n;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int caseNo = 1; caseNo <= t; caseNo++) {
        ll n, q;
        cin >> n >> q;

        vector<ll> factors;
        ll temp = n;
        for (ll i = 2; i * i <= temp; i++) {
            if (temp % i == 0) {
                factors.push_back(i);
                while (temp % i == 0) temp /= i;
            }
        }
        if (temp > 1) factors.push_back(temp);

        vector<ll> divisors = getDivisors(n, factors);
        sort(divisors.begin(), divisors.end());

        vector<pair<ll, ll>> pairs;
        for (ll d : divisors) {
            pairs.emplace_back(d, eulerPhi(n / d, factors));
        }
        sort(pairs.begin(), pairs.end());

        vector<ll> preSum(pairs.size() + 1, 0);
        for (int i = 0; i < pairs.size(); i++) {
            preSum[i + 1] = preSum[i] + pairs[i].second;
        }

        cout << "Case " << caseNo << "\n";
        while (q--) {
            ll x;
            cin >> x;
            auto it = upper_bound(pairs.begin(), pairs.end(), make_pair(x, LLONG_MAX));
            int idx = it - pairs.begin();
            cout << preSum[idx] << "\n";
        }
    }

    return 0;
}
