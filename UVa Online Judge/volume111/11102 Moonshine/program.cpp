// Moonshine
// UVa ID: 11102
// Verdict: Accepted
// Submission Date: 2026-08-01
// UVa Run Time: 0.690s

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);

// 弓形面积：h为弓形高度，R为圆半径
double segmentArea(double h, double R) {
    if (h <= 0.0) return 0.0;
    if (h >= 2.0 * R) return PI * R * R;
    double t = R - h;
    return R * R * acos(t / R) - t * sqrt(2.0 * R * h - h * h);
}

// 水平放置时，液面深度为s时的液体体积
double horizontalVolume(double s, double hb, double db, double hn, double dn, double h) {
    double Rb = db / 2.0, Rn = dn / 2.0;
    double hs = h - hb - hn;          // 肩部高度
    double vol = 0.0;
    // 主体（半径Rb，偏移0）
    vol += hb * segmentArea(s, Rb);
    // 颈部（半径Rn，偏移 Rb - Rn）
    double neckOffset = Rb - Rn;
    double neckEff = s - neckOffset;
    vol += hn * segmentArea(neckEff, Rn);
    // 肩部（若存在），梯形数值积分
    if (hs > 1e-12) {
        int N = 10000;
        double step = hs / N;
        double sum = 0.0;
        for (int i = 0; i <= N; ++i) {
            double t = (double)i / N;
            double R = Rb - (Rb - Rn) * t;   // 当前截面半径
            double offset = Rb - R;          // 该截面最低点相对整体最低点的抬高量
            double eff = s - offset;         // 该截面有效弓形高度
            double area = segmentArea(eff, R);
            if (i == 0 || i == N) sum += area * 0.5;
            else sum += area;
        }
        vol += sum * step;
    }
    return vol;
}

// 直立时，液面高度为k时的液体体积
double verticalVolume(double k, double hb, double db, double hn, double dn, double h) {
    if (k <= 0.0) return 0.0;
    if (k >= h) return horizontalVolume(db, hb, db, hn, dn, h); // 满罐
    double Rb = db / 2.0, Rn = dn / 2.0;
    double hs = h - hb - hn;
    double vol = 0.0;
    // 主体部分
    if (k <= hb) return PI * Rb * Rb * k;
    vol += PI * Rb * Rb * hb;
    // 肩部部分（若存在）
    if (k <= hb + hs) {
        double t0 = (k - hb) / hs;
        double a = Rb, b = Rb - Rn;
        // 积分 ∫0^t0 π*(a - b*t)^2 * hs dt
        double integral = hs * (a * a * t0 - a * b * t0 * t0 + b * b * t0 * t0 * t0 / 3.0);
        return vol + PI * integral;
    }
    // 满肩部，进入颈部
    double tFull = 1.0;
    double a = Rb, b = Rb - Rn;
    double integralFull = hs * (a * a * tFull - a * b * tFull * tFull + b * b * tFull * tFull * tFull / 3.0);
    vol += PI * integralFull;
    // 颈部
    double neckHeight = k - (hb + hs);
    vol += PI * Rn * Rn * neckHeight;
    return vol;
}

int main() {
    double k, hb, db, hn, dn, h;
    while (cin >> k >> hb >> db >> hn >> dn >> h) {
        if (k == 0.0 && hb == 0.0 && db == 0.0 && hn == 0.0 && dn == 0.0 && h == 0.0) break;
        double V = verticalVolume(k, hb, db, hn, dn, h);
        double low = 0.0, high = db;   // 水平液面深度范围 [0, db]
        for (int iter = 0; iter < 100; ++iter) {
            double mid = (low + high) / 2.0;
            double Vmid = horizontalVolume(mid, hb, db, hn, dn, h);
            if (Vmid < V) low = mid;
            else high = mid;
        }
        double s = (low + high) / 2.0;
        printf("%.2f\n", s);
    }
    return 0;
}
