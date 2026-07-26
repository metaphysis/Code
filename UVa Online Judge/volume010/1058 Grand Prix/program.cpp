// Grand Prix
// UVa ID: 1058
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163173738

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-12;

// 计算区间 [A, B]（实数轴上）内离 0 最近的带符号角度（弧度），正为顺时针
double getNearest(double A, double B) {
    double a = fmod(A, 2 * PI);
    if (a < 0) a += 2 * PI;
    double b = fmod(B, 2 * PI);
    if (b < 0) b += 2 * PI;

    // 区间跨过 0 或端点包含 0
    if (a > b || fabs(a) < EPS || fabs(b) < EPS)
        return 0.0;

    // 区间完全在 (0, 2PI) 内
    double distCw = a;               // 顺时针到 0
    double distCcw = 2 * PI - b;     // 逆时针到 0
    if (distCw < distCcw) return distCw;
    if (distCcw < distCw) return -distCcw;
    return distCw;  // 相等选顺时针
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, thetaDeg;
    int caseNo = 1;
    while (cin >> N >> thetaDeg) {
        if (N == 0 && thetaDeg == 0) break;

        vector<double> x(N + 1), y(N + 1);
        x[0] = y[0] = 0.0;
        for (int i = 1; i <= N; ++i)
            cin >> x[i] >> y[i];

        cout << "Case " << caseNo++ << ": ";

        if (thetaDeg == 0) {
            cout << "Acceptable as proposed\n\n";
            continue;
        }

        vector<double> ang;
        ang.reserve(N);
        for (int i = 1; i <= N; ++i) {
            double dx = x[i] - x[i - 1];
            double dy = y[i] - y[i - 1];
            double a = atan2(dy, dx);
            if (a < 0) a += 2 * PI;
            ang.push_back(a);
        }
        sort(ang.begin(), ang.end());

        // 收集所有间隔 >= PI 的起始和结束（展开）
        vector<pair<double, double>> gaps; // {start, end} 展开
        for (int i = 0; i < N; ++i) {
            double start = ang[i];
            double end = (i + 1 < N) ? ang[i + 1] : ang[0] + 2 * PI;
            double gap = end - start;
            if (gap >= PI - EPS) {
                gaps.push_back({start, end});
            }
        }

        if (gaps.empty()) {
            cout << "Unacceptable\n\n";
            continue;
        }

        double bestAngle = 1e100; // 带符号，正顺时针
        bool found = false;

        for (auto &p : gaps) {
            double start = p.first, end = p.second;
            double L = end;                 // 补区间左端点
            double R = start + 2 * PI;      // 补区间右端点
            double A = R - PI / 2;
            double B = L + PI / 2;
            double cand = getNearest(A, B);

            double absCand = fabs(cand);
            if (!found || absCand < fabs(bestAngle) - EPS ||
                (fabs(absCand - fabs(bestAngle)) < EPS && cand > bestAngle)) {
                bestAngle = cand;
                found = true;
            }
        }

        if (!found || fabs(bestAngle) < EPS) {
            cout << "Acceptable as proposed\n";
        } else {
            double deg = fabs(bestAngle) * 180.0 / PI;
            if (bestAngle > 0)
                cout << "Acceptable after clockwise rotation of "
                     << fixed << setprecision(2) << deg << " degrees\n";
            else
                cout << "Acceptable after counterclockwise rotation of "
                     << fixed << setprecision(2) << deg << " degrees\n";
        }
        cout << "\n";
    }
    return 0;
}
