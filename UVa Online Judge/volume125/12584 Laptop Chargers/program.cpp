#include <bits/stdc++.h>
using namespace std;

struct Laptop {
    long double dis, rem;
};

bool canRun(const vector<Laptop>& a, int m, int chps, long double tim) {
    long double need = 0, have = (long double)m * chps * tim;
    for (const Laptop& x : a) {
        long double cur = x.dis * tim - x.rem;
        if (cur > 0) need += cur;
    }
    return need <= have + 1e-12L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q, tc = 0;
    while (cin >> n >> q && (n || q)) {
        int chps;
        long double sumDis = 0;
        vector<Laptop> a(n);
        cin >> chps;
        for (int i = 0; i < n; i++) {
            int c, t, r;
            cin >> c >> t >> r;
            a[i].dis = (long double)c / t;
            a[i].rem = r;
            sumDis += a[i].dis;
        }
        int minCharger = (int)ceill(sumDis / chps - 1e-12L);
        cout << "Case " << ++tc << ":\n";
        cout << minCharger << "\n";
        for (int i = 0; i < q; i++) {
            int m;
            cin >> m;
            if ((long double)m * chps >= sumDis - 1e-12L) {
                cout << "-1.000\n";
                continue;
            }
            long double sumRem = 0, lo = 0;
            for (const Laptop& x : a) sumRem += x.rem;
            long double hi = sumRem / (sumDis - (long double)m * chps);
            for (int j = 0; j < 120; j++) {
                long double mid = (lo + hi) / 2;
                if (canRun(a, m, chps, mid)) lo = mid;
                else hi = mid;
            }
            if (lo > 100000.0L + 1e-7L) cout << "-1.000\n";
            else cout << fixed << setprecision(3) << (double)lo << "\n";
        }
    }
    return 0;
}
