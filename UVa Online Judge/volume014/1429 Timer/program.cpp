#include <bits/stdc++.h>
using namespace std;

const double Pi = acos(-1.0);

double H, D, V, R;

double getVol(double b) {
    if (b >= R) return 0.0;
    double t = sqrt(max(0.0, R * R - b * b));
    double ans = R * R * R * acos(b / R) - 2.0 * b * R * t;
    if (b > 0.0) ans += b * b * b * log((R + t) / b);
    return H * ans / (3.0 * R);
}

double solve() {
    double low = 0.0, high = R;
    for (int i = 0; i < 100; i++) {
        double mid = (low + high) / 2.0;
        if (getVol(mid) > V) low = mid;
        else high = mid;
    }
    return R + (low + high) / 2.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    cout << fixed << setprecision(5);
    while (T--) {
        cin >> H >> D >> V;
        R = D / 2.0;
        cout << solve() << '\n';
    }
    return 0;
}
