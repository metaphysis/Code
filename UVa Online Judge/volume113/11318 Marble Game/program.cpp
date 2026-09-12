#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> tr;
    Fenwick(int n = 0) : n(n), tr(n + 1, 0) {}
    void add(int x, long long v) {
        while (x <= n) {
            tr[x] += v;
            x += x & -x;
        }
    }
    long long sum(int x) {
        long long res = 0;
        while (x > 0) {
            res += tr[x];
            x -= x & -x;
        }
        return res;
    }
    int kth(long long k) {
        int x = 0, d = 1;
        while ((d << 1) <= n) d <<= 1;
        while (d) {
            int y = x + d;
            if (y <= n && tr[y] < k) {
                x = y;
                k -= tr[y];
            }
            d >>= 1;
        }
        return x + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        long long total = 0, cur = 0, ans = 0, cnt = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            total += a[i];
        }
        Fenwick cntBit(2 * n), sumBit(2 * n);
        for (int i = 0; i < n; i++) {
            int p1 = i + 1, p2 = i + n + 1;
            cntBit.add(p1, a[i]);
            cntBit.add(p2, a[i]);
            sumBit.add(p1, 1LL * p1 * a[i]);
            sumBit.add(p2, 1LL * p2 * a[i]);
            cur += a[i] * ((n - i) % n);
        }
        for (int t = 0; t < n; t++) {
            if (cur % n == 0) {
                long long k = cur / n, move = 0;
                if (k > 0) {
                    long long pre = cntBit.sum(t + 1);
                    int pos = cntBit.kth(pre + k);
                    long long beforeCnt = cntBit.sum(pos - 1) - pre;
                    long long beforeSum = sumBit.sum(pos - 1) - sumBit.sum(t + 1);
                    long long rest = k - beforeCnt;
                    long long offset = beforeSum - 1LL * (t + 1) * beforeCnt + rest * (pos - t - 1);
                    move = cur - 1LL * n * k + offset;
                }
                cnt++;
                ans += move;
            }
            cur += total - 1LL * n * a[(t + 1) % n];
        }
        cout << cnt << ' ' << ans << '\n';
    }
    return 0;
}
