#include <bits/stdc++.h>
using namespace std;

const double inf = 1e100;
const double pi = acos(-1.0);

struct Point
{
    double x, y;
};

double getSquareDist(const Point& a, const Point& b)
{
    double dx, dy;
    dx = a.x - b.x;
    dy = a.y - b.y;
    return dx * dx + dy * dy;
}

double getMinDist(vector<Point>& points, int left, int right)
{
    if (right - left <= 3) {
        double ans;
        int i, j;
        ans = inf;
        for (i = left; i < right; ++i)
            for (j = i + 1; j < right; ++j)
                ans = min(ans, getSquareDist(points[i], points[j]));
        return ans;
    }
    int middle, i, j;
    double middleX, leftAns, rightAns, ans;
    middle = (left + right) / 2;
    middleX = points[middle].x;
    leftAns = getMinDist(points, left, middle);
    rightAns = getMinDist(points, middle, right);
    ans = min(leftAns, rightAns);
    vector<Point> strip;
    for (i = left; i < right; ++i)
        if ((points[i].x - middleX) * (points[i].x - middleX) < ans)
            strip.push_back(points[i]);
    sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });
    for (i = 0; i < (int)strip.size(); ++i)
        for (j = i + 1; j < (int)strip.size(); ++j) {
            double dy;
            dy = strip[j].y - strip[i].y;
            if (dy * dy >= ans)
                break;
            ans = min(ans, getSquareDist(strip[i], strip[j]));
        }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseId;
    double e, theta;
    caseId = 1;
    while (cin >> n >> e >> theta) {
        if (n == 0 && e == 0.0 && theta == 0.0)
            break;
        cout << "Case " << caseId << ":\n";
        if (e >= 1.0) {
            cout << fixed << setprecision(6) << 0.0 << '\n';
            ++caseId;
            continue;
        }
        double radian, cosTheta, sinTheta, shortRate;
        radian = theta * pi / 180.0;
        cosTheta = cos(radian);
        sinTheta = sin(radian);
        shortRate = sqrt(1.0 - e * e);
        vector<Point> points(n);
        int i;
        for (i = 0; i < n; ++i) {
            double x, y, newX, newY;
            cin >> x >> y;
            // 旋转坐标并按照短轴比例进行缩放
            newX = x * cosTheta + y * sinTheta;
            newY = (-x * sinTheta + y * cosTheta) / shortRate;
            points[i] = {newX, newY};
        }
        sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
            if (a.x != b.x)
                return a.x < b.x;
            return a.y < b.y;
        });
        double minSquareDist, area;
        minSquareDist = getMinDist(points, 0, n);
        area = pi * shortRate * minSquareDist / 4.0;
        cout << fixed << setprecision(6) << area << '\n';
        ++caseId;
    }
    return 0;
}
