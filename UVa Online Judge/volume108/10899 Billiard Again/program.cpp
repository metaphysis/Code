// Billiard Again
// UVa ID: 10899
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-9;

// 折叠函数：将展开坐标 z 映射回 [0, L] 区间
double fold(double z, double L) {
    double period = 2.0 * L;
    double mod = fmod(z, period);
    if (mod < 0) mod += period;       // 保证非负
    if (mod <= L) return mod;
    return period - mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(2);

    int a_int, b_int, v_int, A_int, s_int, x_int, y_int;
    while (cin >> a_int >> b_int >> v_int >> A_int >> s_int >> x_int >> y_int) {
        if (a_int == 0 && b_int == 0 && v_int == 0 && A_int == 0 && s_int == 0 && x_int == 0 && y_int == 0)
            break;

        double a = a_int, b = b_int, v = v_int, s = s_int;
        double x = x_int, y = y_int;
        double A = A_int * PI / 180.0;
        double cosA = cos(A), sinA = sin(A);

        double X0 = a / 2.0, Y0 = b / 2.0;
        double Lmax = v * s / 2.0;          // 总位移长度

        vector<double> bp;
        bp.push_back(0.0);
        bp.push_back(Lmax);

        // x 方向转折点：X0 + l*cosA = k*a
        if (cosA > EPS) {
            double left = X0 / a;           // k 的最小值，k>=1
            int kMin = max(1, (int)ceil(left - EPS));
            double right = (X0 + Lmax * cosA) / a;
            int kMax = (int)floor(right + EPS) + 2; // 多取几个确保覆盖
            for (int k = kMin; k <= kMax; ++k) {
                double l = (k * a - X0) / cosA;
                if (l >= -EPS && l <= Lmax + EPS)
                    bp.push_back(l);
            }
        }

        // y 方向转折点：Y0 + l*sinA = n*b
        if (sinA > EPS) {
            double left = Y0 / b;
            int nMin = max(1, (int)ceil(left - EPS));
            double right = (Y0 + Lmax * sinA) / b;
            int nMax = (int)floor(right + EPS) + 2;
            for (int n = nMin; n <= nMax; ++n) {
                double l = (n * b - Y0) / sinA;
                if (l >= -EPS && l <= Lmax + EPS)
                    bp.push_back(l);
            }
        }

        // 排序去重
        sort(bp.begin(), bp.end());
        vector<double> pts;
        for (double p : bp) {
            if (pts.empty() || p - pts.back() > 1e-8)
                pts.push_back(p);
        }

        double minD2 = 1e100;

        // 遍历每个区间 [pts[i], pts[i+1]]
        for (size_t i = 0; i + 1 < pts.size(); ++i) {
            double l1 = pts[i], l2 = pts[i + 1];
            if (l2 - l1 < EPS) continue;

            double lmid = (l1 + l2) / 2.0;
            double zx = X0 + lmid * cosA;
            double zy = Y0 + lmid * sinA;

            // 确定 x 方向折叠斜率
            double modx = fmod(zx, 2.0 * a);
            if (modx < 0) modx += 2.0 * a;
            int signX = (modx < a || fabs(modx - a) < EPS) ? 1 : -1; // 在转折点附近，但区间内不会正好在转折点

            double mody = fmod(zy, 2.0 * b);
            if (mody < 0) mody += 2.0 * b;
            int signY = (mody < b || fabs(mody - b) < EPS) ? 1 : -1;

            // 计算偏移量，使得 fold = sign * (X0 + l*cosA) + offset
            double foldX_mid = fold(zx, a);
            double foldY_mid = fold(zy, b);
            double offsetX = foldX_mid - signX * (X0 + lmid * cosA);
            double offsetY = foldY_mid - signY * (Y0 + lmid * sinA);

            // 距离平方函数 D2(l) = (signX*(X0+l*cosA)+offsetX - x)^2
            //                        + (signY*(Y0+l*sinA)+offsetY - y)^2
            // 展开为 l^2 + 2*B*l + C
            double B = signX * cosA * (signX * X0 + offsetX - x)
                     + signY * sinA * (signY * Y0 + offsetY - y);
            // 顶点 l_opt = -B (因为二次项系数为1)
            double lOpt = -B;

            // 检查顶点是否在区间内
            double cand_l;
            if (lOpt >= l1 && lOpt <= l2)
                cand_l = lOpt;
            else {
                // 否则取两端点中较小的
                double d1 = pow(fold(X0 + l1 * cosA, a) - x, 2)
                          + pow(fold(Y0 + l1 * sinA, b) - y, 2);
                double d2 = pow(fold(X0 + l2 * cosA, a) - x, 2)
                          + pow(fold(Y0 + l2 * sinA, b) - y, 2);
                minD2 = min(minD2, min(d1, d2));
                continue;
            }

            // 计算候选点的距离平方
            double Xc = X0 + cand_l * cosA;
            double Yc = Y0 + cand_l * sinA;
            double dx = fold(Xc, a) - x;
            double dy = fold(Yc, b) - y;
            double d2 = dx * dx + dy * dy;
            minD2 = min(minD2, d2);
        }

        double ans = sqrt(max(0.0, minD2));
        cout << ans << "\n";
    }

    return 0;
}
