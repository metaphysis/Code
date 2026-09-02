#include <bits/stdc++.h>
using namespace std;

const double Eps = 1e-10;

struct Point {
    double x, y;
    Point operator + (const Point &other) const {
        return {x + other.x, y + other.y};
    }
    Point operator - (const Point &other) const {
        return {x - other.x, y - other.y};
    }
    Point operator * (double value) const {
        return {x * value, y * value};
    }
};

double Dot(Point first, Point second) {
    return first.x * second.x + first.y * second.y;
}

double Norm2(Point point) {
    return Dot(point, point);
}

struct Path {
    vector<Point> point;
    vector<double> time;
    vector<Point> velocity;
    double total;
};

bool HasSolution(double a, double b, double c, double left, double right) {
    double best = min(a * left * left + b * left + c, a * right * right + b * right + c);
    if (a > Eps) {
        double middle = -b / (2.0 * a);
        if (middle >= left && middle <= right)
            best = min(best, a * middle * middle + b * middle + c);
    }
    return best <= Eps;
}

Point GetPoint(const Path &path, int index, double current) {
    double ratio = (current - path.time[index]) / (path.time[index + 1] - path.time[index]);
    return path.point[index] + path.velocity[index] * (current - path.time[index]);
}

bool CheckPart(const Path &misha, const Path &nadia, double deliveryTime, double rightTime) {
    if (rightTime < -Eps)
        return false;
    int mIndex = 0, nIndex = 0;
    double current = 0.0;
    while (current < rightTime - Eps) {
        while (mIndex + 1 < (int)misha.time.size() && misha.time[mIndex + 1] <= current + Eps)
            mIndex++;
        while (nIndex + 1 < (int)nadia.time.size() && nadia.time[nIndex + 1] <= current + deliveryTime + Eps)
            nIndex++;
        if (mIndex + 1 >= (int)misha.time.size() || nIndex + 1 >= (int)nadia.time.size())
            break;
        double nextTime = min(rightTime, misha.time[mIndex + 1]);
        nextTime = min(nextTime, nadia.time[nIndex + 1] - deliveryTime);
        if (nextTime <= current + Eps) {
            if (misha.time[mIndex + 1] <= current + Eps)
                mIndex++;
            if (nadia.time[nIndex + 1] - deliveryTime <= current + Eps)
                nIndex++;
            continue;
        }
        Point mPoint = GetPoint(misha, mIndex, current);
        Point nPoint = GetPoint(nadia, nIndex, current + deliveryTime);
        Point relativePoint = mPoint - nPoint;
        Point relativeVelocity = misha.velocity[mIndex] - nadia.velocity[nIndex];
        double length = nextTime - current;
        double a = Norm2(relativeVelocity);
        double b = 2.0 * Dot(relativePoint, relativeVelocity);
        double c = Norm2(relativePoint) - deliveryTime * deliveryTime;
        if (HasSolution(a, b, c, 0.0, length))
            return true;
        current = nextTime;
    }
    return false;
}

bool CheckEnd(const Path &misha, const Path &nadia, double deliveryTime) {
    double leftTime = max(0.0, nadia.total - deliveryTime);
    double rightTime = min(misha.total, nadia.total);
    if (leftTime > rightTime + Eps)
        return false;
    int mIndex = 0;
    while (mIndex + 1 < (int)misha.time.size() && misha.time[mIndex + 1] <= leftTime + Eps)
        mIndex++;
    double current = leftTime;
    Point endPoint = nadia.point.back();
    while (current < rightTime - Eps) {
        while (mIndex + 1 < (int)misha.time.size() && misha.time[mIndex + 1] <= current + Eps)
            mIndex++;
        if (mIndex + 1 >= (int)misha.time.size())
            break;
        double nextTime = min(rightTime, misha.time[mIndex + 1]);
        if (nextTime <= current + Eps) {
            mIndex++;
            continue;
        }
        Point mPoint = GetPoint(misha, mIndex, current);
        Point relativePoint = mPoint - endPoint;
        double remain = nadia.total - current;
        double a = Norm2(misha.velocity[mIndex]) - 1.0;
        double b = 2.0 * Dot(relativePoint, misha.velocity[mIndex]) + 2.0 * remain;
        double c = Norm2(relativePoint) - remain * remain;
        if (HasSolution(a, b, c, 0.0, nextTime - current))
            return true;
        current = nextTime;
    }
    return false;
}

bool Check(const Path &misha, const Path &nadia, double deliveryTime) {
    double rightTime = min(misha.total, nadia.total - deliveryTime);
    if (rightTime >= -Eps && CheckPart(misha, nadia, deliveryTime, rightTime))
        return true;
    return CheckEnd(misha, nadia, deliveryTime);
}

Path ReadPath() {
    int n;
    cin >> n;
    Path path;
    path.point.resize(n);
    path.time.assign(n, 0.0);
    path.velocity.resize(n - 1);
    for (int i = 0; i < n; i++)
        cin >> path.point[i].x >> path.point[i].y;
    for (int i = 1; i < n; i++)
        path.time[i] = path.time[i - 1] + sqrt(Norm2(path.point[i] - path.point[i - 1]));
    for (int i = 0; i + 1 < n; i++)
        path.velocity[i] = (path.point[i + 1] - path.point[i]) * (1.0 / (path.time[i + 1] - path.time[i]));
    path.total = path.time.back();
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin) {
        Path misha = ReadPath();
        if (!cin)
            break;
        Path nadia = ReadPath();
        if (!Check(misha, nadia, nadia.total)) {
            cout << "impossible\n";
            continue;
        }
        double left = 0.0, right = nadia.total;
        for (int iteration = 0; iteration < 55; iteration++) {
            double middle = (left + right) / 2.0;
            if (Check(misha, nadia, middle))
                right = middle;
            else
                left = middle;
        }
        cout << fixed << setprecision(5) << right << '\n';
    }
    return 0;
}
