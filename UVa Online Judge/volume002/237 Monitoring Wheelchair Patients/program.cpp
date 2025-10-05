// Monitoring Wheelchair Patients
// UVa ID: 237
// Verdict: Accepted
// Submission Date: 2025-10-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0.0), EPSILON = 1E-10;

struct point {
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
    point operator + (point p) { return point(x + p.x, y + p.y); }
    point operator - (point p) { return point(x - p.x, y - p.y); }
    point operator * (double u) { return point(x * u, y * u); }
    point operator / (double u) { return point(x / u, y / u); }
    point rotate(double alpha) {
        return point(x * cos(alpha) - y * sin(alpha), x * sin(alpha) + y * cos(alpha));
    }
    double norm() { return sqrt(x * x + y * y); }
};

int dcmp(double x) {
    if (abs(x) <= EPSILON) return 0;
    return x > 0 ? 1 : -1;
}

bool isInBox(point p) {
    return dcmp(p.x) > 0 && dcmp(p.x - 400) < 0 && dcmp(p.y) > 0 && dcmp(p.y - 200) < 0;
}

int main(int argc, char *argv[]) {
    int lines, cases = 0;
    while (cin >> lines) {
        if (lines == 0) break;
        int out = 0;
        point start(200, 0), outP;
        double t1, t2, speed, bearing, totalD = 0, maxD = 0, outT;
        for (int i = 1; i <= lines; i++) {
            cin >> t1 >> t2 >> speed >> bearing;
            point scale = point(0, 1).rotate(-bearing / 180 * PI) * speed;
            point now = start + scale * (t2 - t1);
            totalD += speed * (t2 - t1);
            if (!out && !isInBox(now)) {
                out = 1;
                int cnt = 0;
                double left = t1, right = t2, middle;
                // use binary search to find the intersection point
                while (cnt++ <= 50) {
                    middle = (left + right) / 2;
                    point tmp = start + scale * (middle - t1);
                    if (isInBox(tmp)) left = middle;
                    else right = middle;
                }
                outP = start + scale * (middle - t1);
                outT = middle;
            }
            start = now;
            maxD = max(maxD, (start - point(200, 0)).norm());
        }
        cout << "Case Number " << ++cases << '\n';
        cout.precision(1);
        if (out) {
            cout << "Left restricted area at point (" << fixed << outP.x;
            cout << fixed << "," << outP.y << ") and time " << fixed << outT;
            cout << " sec." << '\n';
        } else {
            cout << "No departure from restricted area" << '\n';
            cout << "Maximum distance patient traveled from door was ";
            cout << fixed << maxD << " feet" << '\n';
        }
        cout << "Total distance traveled was ";
        cout << fixed << totalD << " feet" << '\n';
        cout << "***************************************" << '\n';
    }
	return 0;
}
