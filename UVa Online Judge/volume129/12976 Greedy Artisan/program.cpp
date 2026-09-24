#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, tc = 0;
    while (cin >> n >> k && (n || k)) {
        vector<pair<long long, long long>> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i].first >> a[i].second;
        sort(a.begin(), a.end());
        long long preCnt = 0, preSum = 0, firstSum = 0;
        long double ans = 1e100L;
        for (int i = 0; i < n;) {
            int j = i;
            long long s = a[i].first;
            while (j < n && a[j].first == s) j++;
            int cnt = j - i;
            if (preCnt + cnt >= k) {
                int rank = 0;
                if (preCnt < k - 1) rank = k - 1 - preCnt;
                long long p = a[i + rank].second, sum;
                if (preCnt >= k - 1)
                    sum = firstSum + s;
                else
                    sum = preSum + 1LL * (k - preCnt) * s;
                ans = min(ans, (long double)p * sum / s);
            }
            long long take = min(1LL * cnt, max(0LL, 1LL * (k - 1) - preCnt));
            firstSum += take * s;
            preSum += 1LL * cnt * s;
            preCnt += cnt;
            i = j;
        }
        cout << fixed << setprecision(6);
        cout << "Case #" << ++tc << ": " << (double)ans << '\n';
    }
    return 0;
}
