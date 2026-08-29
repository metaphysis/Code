#include <bits/stdc++.h>

using namespace std;

int dist, num, maxTime;

struct Light {
    int x, red, green;
    int t[6000], k;
    double dp[6000];
    bool operator<(const Light &l) const {
        return x < l.x;
    }
} light[64];

bool check(int from, int to, int t1, int x1, int t2, int x2) {
    assert(x1 < x2);
    for (int i = from; i <= to; i++) {
        const Light &L = light[i];
        int p = t1 * (x2 - x1) + (t2 - t1) * (L.x - x1);
        int q = 20 * (x2 - x1);
        p %= q * (L.red + L.green);
        if (0 < p && p < q * L.red) return false;
    }
    return true;
}

double lineCost(double dx, double dt) {
    return dx + dt * dt / dx - 0.1 * dt;
}

double solve() {
    if (dist <= 0) return 0;
    if (num == 0) return lineCost(dist, dist / 20.0);
    maxTime = dist / 20 + 5;
    for (int i = 1; i <= num; i++) maxTime += light[i].red;
    for (int i = 1; i <= num; i++) {
        Light &L = light[i];
        assert(0 < L.x && L.x < dist);
        L.k = 1;
        L.t[0] = L.red;
        while (true) {
            L.t[L.k] = L.t[L.k - 1] + (L.k % 2 == 1 ? L.green : L.red);
            if (L.t[L.k] > maxTime) break;
            L.k++;
        }
    }
    light[0].k = 1;
    light[0].t[0] = 0;
    light[0].dp[0] = 0;
    for (int b = 1; b <= num; b++) {
        Light &B = light[b];
        for (int bi = 0; bi < B.k; bi++) {
            double res = 1e99;
            for (int a = 0; a < b; a++) {
                const Light &A = light[a];
                for (int ai = 0; ai < A.k && A.t[ai] < B.t[bi]; ai++) {
                    if (!check(a + 1, b - 1, A.t[ai] * 20, A.x, B.t[bi] * 20, B.x)) continue;
                    double dx = B.x - A.x;
                    double dt = B.t[bi] - A.t[ai];
                    res = min(res, A.dp[ai] + lineCost(dx, dt));
                }
            }
            B.dp[bi] = res;
        }
    }
    double best = 1e99;
    for (int a = 0; a <= num; a++) {
        const Light &A = light[a];
        for (int ai = 0; ai < A.k; ai++) {
            int x0 = A.x, dx = dist - x0;
            int t0 = A.t[ai] * 20;
            int t1 = t0 + dx;
            if (check(a + 1, num, t0, x0, t1, dist)) best = min(best, A.dp[ai] + lineCost(dx, dx / 20.0));
        }
    }
    return best;
}

int main() {
    while (cin >> dist >> num) {
        if (dist == 0 && num == 0) break;
        for (int i = 1; i <= num; i++) cin >> light[i].x >> light[i].red >> light[i].green;
        sort(light + 1, light + num + 1);
        printf("%.2f\n", solve());
    }
}
