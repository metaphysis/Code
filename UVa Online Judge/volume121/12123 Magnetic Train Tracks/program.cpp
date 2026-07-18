// Magnetic Train Tracks
// UVa ID: 12123
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.390s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const double PI = acos(-1.0);
    const double EPS = 1e-12;
    int n, scenario = 1;
    while (cin >> n && n) {
        vector<int> x(n), y(n);
        for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
        ll totalTriangles = (ll)n * (n - 1) * (n - 2) / 6;
        ll nonAcutePairs = 0;   // 所有顶点处夹角在[90°,180°]内的有序点对总数
        for (int i = 0; i < n; ++i) {
            vector<double> ang;
            ang.reserve(n - 1);
            for (int j = 0; j < n; ++j) {
                if (j == i) continue;
                double dx = x[j] - x[i];
                double dy = y[j] - y[i];
                double a = atan2(dy, dx);
                if (a < 0) a += 2 * PI;
                ang.push_back(a);
            }
            sort(ang.begin(), ang.end());
            int m = n - 1;
            vector<double> ext(2 * m);
            for (int k = 0; k < m; ++k) {
                ext[k] = ang[k];
                ext[k + m] = ang[k] + 2 * PI;
            }
            int p1 = 0, p2 = 0;
            for (int j = 0; j < m; ++j) {
                double base = ang[j];
                if (p1 < j + 1) p1 = j + 1;
                while (p1 < j + m && ext[p1] - base < PI / 2 - EPS) ++p1;
                if (p2 < p1) p2 = p1;
                while (p2 < j + m && ext[p2] - base <= PI + EPS) ++p2;
                nonAcutePairs += (p2 - p1);
            }
        }
        ll nonAcuteTriangles = nonAcutePairs; // 每个非锐角三角形被计数一次
        ll acuteTriangles = totalTriangles - nonAcuteTriangles;
        cout << "Scenario " << scenario << ":\n";
        cout << "There are " << acuteTriangles << " sites for making valid tracks\n";
        ++scenario;
    }
    return 0;
}
