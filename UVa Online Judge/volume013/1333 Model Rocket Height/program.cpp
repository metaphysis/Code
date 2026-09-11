// Model Rocket Height
// UVa ID: 1333
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

double computeHeight(double D, double H, double alpha, double beta, double gamma) {
    const double PI = acos(-1.0);
    double a = alpha * PI / 180.0;
    double b = beta * PI / 180.0;
    double c = gamma * PI / 180.0;
    double tanA = tan(a), tanB = tan(b), tanC = tan(c);
    double denom = 1.0 / (tanA * tanA) + 1.0 / (tanC * tanC) - 2.0 / (tanB * tanB);
    double u = D * sqrt(2.0) / sqrt(denom);
    return H + u;
}

int main() {
    double D, H;
    cin >> D >> H;
    double alpha, beta, gamma;
    while (cin >> alpha >> beta >> gamma) {
        if (alpha <= 0 || beta <= 0 || gamma <= 0) break;
        double height = computeHeight(D, H, alpha, beta, gamma);
        int ans = (int)floor(height + 0.5);
        cout << ans << "\n";
    }
    return 0;
}
