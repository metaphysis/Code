#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000009LL;

long long calc(vector<long long> bound, int n, int p) {
    int i, j, mask, sub, len = 1, size = 1 << n;
    long long mx = 0, tmp;
    for (i = 0; i < n; i++) {
        if (bound[i] < 0) return 0;
        mx = max(mx, bound[i]);
    }
    tmp = mx;
    while (tmp >= p) {
        tmp /= p;
        len++;
    }
    vector<vector<int>> dig(n, vector<int>(len));
    for (i = 0; i < n; i++) {
        tmp = bound[i];
        for (j = 0; j < len; j++) {
            dig[i][j] = tmp % p;
            tmp /= p;
        }
    }
    vector<long long> dp(size), ndp(size), poly(p), nxt(p);
    dp[size - 1] = 1;
    for (j = len - 1; j >= 0; j--) {
        fill(ndp.begin(), ndp.end(), 0);
        for (mask = 0; mask < size; mask++) {
            if (dp[mask] == 0) continue;
            for (sub = mask;; sub = (sub - 1) & mask) {
                fill(poly.begin(), poly.end(), 0);
                poly[0] = 1;
                for (i = 0; i < n; i++) {
                    fill(nxt.begin(), nxt.end(), 0);
                    if (sub & (1 << i)) {
                        int d = dig[i][j];
                        for (int s = 0; s + d < p; s++)
                            nxt[s + d] = poly[s];
                    } else {
                        int lim = (mask & (1 << i)) ? dig[i][j] - 1 : p - 1;
                        long long sum = 0;
                        for (int s = 0; s < p; s++) {
                            sum += poly[s];
                            if (sum >= mod) sum -= mod;
                            if (s - lim - 1 >= 0) {
                                sum -= poly[s - lim - 1];
                                if (sum < 0) sum += mod;
                            }
                            nxt[s] = sum;
                        }
                    }
                    poly.swap(nxt);
                }
                long long ways = 0;
                for (i = 0; i < p; i++) {
                    ways += poly[i];
                    if (ways >= mod) ways -= mod;
                }
                ndp[sub] = (ndp[sub] + dp[mask] * ways) % mod;
                if (sub == 0) break;
            }
        }
        dp.swap(ndp);
    }
    long long ans = 0;
    for (i = 0; i < size; i++) {
        ans += dp[i];
        if (ans >= mod) ans -= mod;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, p, i, mask, bits;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        cin >> n >> p;
        vector<long long> low(n), high(n), bound(n);
        for (i = 0; i < n; i++) cin >> low[i];
        for (i = 0; i < n; i++) cin >> high[i];
        long long valid = 0;
        for (mask = 0; mask < (1 << n); mask++) {
            bool ok = true;
            bits = 0;
            for (i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bound[i] = low[i] - 1;
                    bits++;
                } else {
                    bound[i] = high[i];
                }
                if (bound[i] < 0) ok = false;
            }
            if (!ok) continue;
            long long ways = calc(bound, n, p);
            if (bits & 1) {
                valid -= ways;
                if (valid < 0) valid += mod;
            } else {
                valid += ways;
                if (valid >= mod) valid -= mod;
            }
        }
        cout << "Case " << cs << ": " << valid << '\n';
    }
    return 0;
}
