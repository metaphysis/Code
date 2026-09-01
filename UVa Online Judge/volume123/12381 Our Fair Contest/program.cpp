#include <bits/stdc++.h>
using namespace std;

struct Event {
    long long p, q;
    int type;
};

bool cmpEvent(const Event &a, const Event &b) {
    return a.p * b.q < b.p * a.q;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n), b(n);
        vector<Event> ev;
        long long cur2 = 0, best2;
        for (int i = 0; i < n; i++)
            cin >> a[i] >> b[i];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int da, db;
                if (i == j) continue;
                if (b[j] > b[i] || (b[j] == b[i] && a[j] > a[i])) cur2 += 2;
                else if (a[i] == a[j] && b[i] == b[j]) cur2++;
                da = a[i] - a[j];
                db = b[i] - b[j];
                if (da > 0 && db < 0) ev.push_back({-db, da, 0});
                else if (da < 0 && db > 0) ev.push_back({db, -da, 1});
            }
        }
        best2 = cur2;
        sort(ev.begin(), ev.end(), cmpEvent);
        for (size_t l = 0; l < ev.size();) {
            size_t r = l;
            long long down = 0, up = 0, mid2;
            while (r < ev.size() && ev[r].p * ev[l].q == ev[l].p * ev[r].q) {
                if (ev[r].type == 0) down++;
                else up++;
                r++;
            }
            mid2 = cur2 - down + up;
            best2 = min(best2, mid2);
            cur2 = cur2 - 2 * down + 2 * up;
            best2 = min(best2, cur2);
            l = r;
        }
        double ans = 1.0 * (2LL * m * (n - 1) - best2) / (2 * (n - 1));
        cout << fixed << setprecision(4) << ans << '\n';
    }
    return 0;
}
