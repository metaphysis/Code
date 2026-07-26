// Practice
// UVa ID: 10727
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163173465

#include <bits/stdc++.h>
using namespace std;

// sigmoid 函数，防止溢出
double sigmoid(double x) {
    if (x > 700.0) return 1.0;
    if (x < -700.0) return 0.0;
    return 1.0 / (1.0 + exp(-x));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    while (cin >> k && k != 0) {
        vector<pair<int,int>> obs;
        obs.reserve(k);
        for (int i = 0; i < k; ++i) {
            int n, w;
            cin >> n >> w;
            obs.emplace_back(n, w);
        }
        double a = 0.0, b = 0.0;
        for (int iter = 0; iter < 100; ++iter) {
            double ga = 0.0, gb = 0.0;
            double Haa = 0.0, Hab = 0.0, Hbb = 0.0;
            for (auto &p : obs) {
                int n = p.first, w = p.second;
                double x = a + b * n;
                double p_hat = sigmoid(x);
                double diff = w - p_hat;
                double p1 = p_hat * (1.0 - p_hat);
                ga += diff;
                gb += diff * n;
                Haa -= p1;
                Hab -= p1 * n;
                Hbb -= p1 * n * n;
            }
            // 解 2x2 线性方程组 H * delta = -g
            double det = Haa * Hbb - Hab * Hab;
            if (fabs(det) < 1e-12) {
                Haa += 1e-8;
                Hbb += 1e-8;
                det = Haa * Hbb - Hab * Hab;
            }
            double deltaA = (-ga * Hbb + gb * Hab) / det;
            double deltaB = (Haa * (-gb) - Hab * (-ga)) / det;
            a += deltaA;
            b += deltaB;
            if (fabs(deltaA) < 1e-8 && fabs(deltaB) < 1e-8) break;
        }
        cout << fixed << setprecision(4) << a << " " << b << "\n";
    }
    return 0;
}
