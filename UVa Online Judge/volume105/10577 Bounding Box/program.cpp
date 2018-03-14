// Bounding Box
// UVa ID: 10577
// Verdict: Accepted
// Submission Date: 2017-12-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double PI = 2.0 * acos(0);

double getValue(double a[3][3])
{
    double r = 0.0;
    r += a[0][0] * a[1][1] * a[2][2] + a[0][1] * a[1][2] * a[2][0] + a[1][0] * a[2][1] * a[0][2];
    r -= a[0][0] * a[1][2] * a[2][1] + a[0][1] * a[1][0] * a[2][2] + a[0][2] * a[1][1] * a[2][0];
    return r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0, n;
    double xi, yi;
    double a[3][3], b[3][3], c[3][3];

    while (cin >> n, n > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            cin >> xi >> yi;
            a[i][0] = 1.0, a[i][1] = xi * xi + yi * yi, a[i][2] = yi;
            b[i][0] = 1.0, b[i][1] = xi, b[i][2] = xi * xi + yi * yi;
            c[i][0] = 1.0, c[i][1] = xi, c[i][2] = yi;
        }

        double x = getValue(a) / (2.0 * getValue(c));
        double y = getValue(b) / (2.0 * getValue(c));

        double d = sqrt(pow(c[0][1] - x, 2) + pow(c[0][2] - y, 2));
        double angle = atan2(c[0][2] - y, c[0][1] - x);
        double step = 2.0 * PI / (1.0 * n);

        double leftx = c[0][1], rightx = c[0][1], topy = c[0][2], bottomy = c[0][2];
        for (int i = 2; i <= n; i++)
        {
            angle += step;
            double xx = x + d * cos(angle);
            double yy = y + d * sin(angle);
            if (xx < leftx) leftx = xx;
            if (xx > rightx) rightx = xx;
            if (yy < bottomy) bottomy = yy;
            if (yy > topy) topy = yy;
        }

        double area = abs(leftx - rightx) * abs(topy - bottomy);

        cout << "Polygon " << ++cases << ": ";
        cout << fixed << setprecision(3) << area << '\n';
    }

    return 0;
}
