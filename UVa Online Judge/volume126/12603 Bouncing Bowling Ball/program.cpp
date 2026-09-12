// Bouncing Bowling Ball 
// UVa ID: 12603
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const double PI = acos(-1.0);
    const double BALL_RADIUS = 0.10;
    const double PIN_RADIUS = 0.06;
    const double HIT_RADIUS = BALL_RADIUS + PIN_RADIUS;
    const double HALF_CENTER_WIDTH = (1.05 - 0.20) / 2.0;
    const double PERIOD = 2.0 * HALF_CENTER_WIDTH;
    const double EPS = 1e-10;
    int test;
    cin >> test;
    for (int cas = 1; cas <= test; cas++) {
        double t;
        int x;
        cin >> t >> x;
        double angle = x * PI / 180.0;
        double slope = tan(angle);
        double unfoldedY = t * slope;
        double remainder = fmod(unfoldedY, PERIOD);
        if (remainder < 0) remainder += PERIOD;
        double verticalDistance = min(remainder, PERIOD - remainder);
        double distance = verticalDistance / sqrt(1.0 + slope * slope);
        cout << (distance <= HIT_RADIUS + EPS ? "yes" : "no") << '\n';
    }
    return 0;
}
