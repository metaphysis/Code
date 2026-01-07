// Environment Protection
// UVa ID: 12528
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int W, D, A, K;
vector<int> P1, Q1, P2, Q2;
double leftBound, rightBound;

// 计算多项式值
double polyEval(const vector<int>& coeffs, double x) {
    double result = 0, power = 1;
    for (int c : coeffs) {
        result += c * power;
        power *= x;
    }
    return result;
}

// 计算 y1(x) 和 y2(x)
double y1(double x) { return polyEval(P1, x) / polyEval(Q1, x); }
double y2(double x) { return polyEval(P2, x) / polyEval(Q2, x); }

// 被积函数
double integrand(double x, double d) {
    double upper = y1(x);
    double lower = max(y2(x), d);
    return max(0.0, upper - lower);
}

// 自适应辛普森积分
double adaptiveSimpson(double a, double b, double d, double eps) {
    function<double(double)> f = [&](double x) { return integrand(x, d); };
    function<double(double, double, double, double, double, double, double, int)> simpson =
        [&](double l, double r, double fl, double fr, double fm, double whole, double eps, int depth) {
        double mid = (l + r) / 2;
        double fml = f((l + mid) / 2);
        double fmr = f((mid + r) / 2);
        double left = (mid - l) * (fl + 4 * fml + fm) / 6;
        double right = (r - mid) * (fm + 4 * fmr + fr) / 6;
        double delta = left + right - whole;
        if (abs(delta) <= 15 * eps || depth >= 20) return left + right + delta / 15;
        return simpson(l, mid, fl, fm, fml, left, eps / 2, depth + 1) +
               simpson(mid, r, fm, fr, fmr, right, eps / 2, depth + 1);
    };
    double fl = f(a), fr = f(b), fm = f((a + b) / 2);
    double whole = (b - a) * (fl + 4 * fm + fr) / 6;
    return simpson(a, b, fl, fr, fm, whole, eps, 0);
}

// 计算面积
double area(double d) { return adaptiveSimpson(0, W, d, 1e-8); }

int main() {
    while (cin >> W >> D >> A >> K) {
        P1.resize(K + 1); Q1.resize(K + 1); P2.resize(K + 1); Q2.resize(K + 1);
        for (int i = 0; i <= K; i++) cin >> P1[i];
        for (int i = 0; i <= K; i++) cin >> Q1[i];
        for (int i = 0; i <= K; i++) cin >> P2[i];
        for (int i = 0; i <= K; i++) cin >> Q2[i];

        leftBound = -D, rightBound = 0;
        // 二分搜索
        for (int iter = 0; iter < 100; iter++) {
            double mid = (leftBound + rightBound) / 2;
            if (area(mid) > A) leftBound = mid;
            else rightBound = mid;
        }
        cout << fixed << setprecision(5) << -leftBound << endl; // 输出正值深度
    }
    return 0;
}
