#include <bits/stdc++.h>
using namespace std;

const int maxN = 25;
const double eps = 1e-10;
int n;
double len[maxN], minR[maxN], maxR[maxN], needR[maxN];
double sumX[maxN], sumY[maxN], vecX[maxN], vecY[maxN];

void buildRange() {
    double sum = 0, mx = 0;
    for (int i = 1; i <= n; i++) {
        sum += len[i];
        mx = max(mx, len[i]);
        maxR[i] = sum;
        minR[i] = max(2.0 * mx - sum, 0.0);
    }
}

double getValue(double left, double right, double low, double high) {
    double l = max(left, low), r = min(right, high);
    if (l > r) return l;
    return (l + r) * 0.5;
}

void buildVectors(double targetX, double targetY) {
    double targetR = hypot(targetX, targetY), finalR = min(max(targetR, minR[n]), maxR[n]);
    double dirX = 1.0, dirY = 0.0;
    if (targetR > eps) {
        dirX = targetX / targetR;
        dirY = targetY / targetR;
    }
    needR[n] = finalR;
    for (int i = n - 1; i >= 1; i--)
        needR[i] = getValue(fabs(needR[i + 1] - len[i + 1]), needR[i + 1] + len[i + 1], minR[i], maxR[i]);
    sumX[n] = finalR * dirX;
    sumY[n] = finalR * dirY;
    for (int i = n; i >= 1; i--) {
        double curR = needR[i], preR = i == 1 ? 0.0 : needR[i - 1];
        if (curR < eps) {
            sumX[i - 1] = preR;
            sumY[i - 1] = 0.0;
            vecX[i] = sumX[i] - sumX[i - 1];
            vecY[i] = sumY[i] - sumY[i - 1];
        } else if (preR < eps) {
            sumX[i - 1] = 0.0;
            sumY[i - 1] = 0.0;
            vecX[i] = sumX[i];
            vecY[i] = sumY[i];
        } else {
            double cosA = (curR * curR + preR * preR - len[i] * len[i]) / (2.0 * curR * preR);
            cosA = max(-1.0, min(1.0, cosA));
            double angle = atan2(sumY[i], sumX[i]) + acos(cosA);
            sumX[i - 1] = preR * cos(angle);
            sumY[i - 1] = preR * sin(angle);
            vecX[i] = sumX[i] - sumX[i - 1];
            vecY[i] = sumY[i] - sumY[i - 1];
        }
    }
}

void solve() {
    double targetX, targetY;
    while (cin >> n) {
        for (int i = 1; i <= n; i++) cin >> len[i];
        cin >> targetX >> targetY;
        buildRange();
        buildVectors(targetX, targetY);
        double x = 0, y = 0;
        for (int i = 1; i <= n; i++) {
            x += vecX[i];
            y += vecY[i];
            cout << fixed << setprecision(10) << x << ' ' << y << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
