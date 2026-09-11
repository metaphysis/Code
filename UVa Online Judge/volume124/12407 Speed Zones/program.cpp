// Speed Zones
// UVa ID: 12407
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        long double D;
        cin >> N >> D;
        vector<long double> S(N);
        long double maxSpeed = 0.0L;
        for (int i = 0; i < N; ++i) {
            cin >> S[i];
            maxSpeed = max(maxSpeed, S[i]);
        }
        auto getDistance = [&](long double k) {
            long double distance = 0.0L;
            for (int i = 0; i < N; ++i) {
                long double x = k * S[i];
                if (x >= 1.0L) return numeric_limits<long double>::infinity();
                long double cosValue = sqrtl(1.0L - x * x);
                distance += 100.0L * x / cosValue;
            }
            return distance;
        };
        long double low = 0.0L;
        long double high = 1.0L / maxSpeed;
        for (int iter = 0; iter < 120; ++iter) {
            long double mid = (low + high) / 2.0L;
            if (getDistance(mid) <= D) low = mid;
            else high = mid;
        }
        long double k = (low + high) / 2.0L;
        long double answer = 0.0L;
        for (int i = 0; i < N; ++i) {
            long double x = k * S[i];
            long double cosValue = sqrtl(max(0.0L, 1.0L - x * x));
            answer += 100.0L / (S[i] * cosValue);
        }
        cout << "Case " << tc << ": " << fixed << setprecision(8) << (double)answer << '\n';
    }
    return 0;
}
