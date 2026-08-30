#include <bits/stdc++.h>
using namespace std;

double calcValue(double s, double x, double d) {
    double leftDist = sqrt(x * x + s * s), rightDist = sqrt(x * x + (s + d) * (s + d));
    double diff = rightDist - leftDist;
    return (leftDist + rightDist) / 2.0 + d / 4.0 - diff * diff / (4.0 * d);
}

double simpson(double left, double right, double leftValue, double midValue, double rightValue) {
    return (right - left) * (leftValue + 4.0 * midValue + rightValue) / 6.0;
}

double adaptiveSimpson(double left, double right, double leftValue, double midValue, double rightValue, double wholeValue, double eps, int depth, double x, double d) {
    double midPoint = (left + right) / 2.0, leftMid = (left + midPoint) / 2.0, rightMid = (midPoint + right) / 2.0;
    double leftMidValue = calcValue(leftMid, x, d), rightMidValue = calcValue(rightMid, x, d);
    double leftPart = simpson(left, midPoint, leftValue, leftMidValue, midValue), rightPart = simpson(midPoint, right, midValue, rightMidValue, rightValue);
    if (depth <= 0 || fabs(leftPart + rightPart - wholeValue) <= 15.0 * eps)
        return leftPart + rightPart + (leftPart + rightPart - wholeValue) / 15.0;
    return adaptiveSimpson(left, midPoint, leftValue, leftMidValue, midValue, leftPart, eps / 2.0, depth - 1, x, d) + adaptiveSimpson(midPoint, right, midValue, rightMidValue, rightValue, rightPart, eps / 2.0, depth - 1, x, d);
}

double solveCase(double x, double y1, double y2, double d) {
    double length = y1 - y2 - d;
    if (length == 0.0)
        return calcValue(y2, x, d);
    double left = y2, right = y1 - d, midPoint = (left + right) / 2.0;
    double leftValue = calcValue(left, x, d), midValue = calcValue(midPoint, x, d), rightValue = calcValue(right, x, d);
    double wholeValue = simpson(left, right, leftValue, midValue, rightValue);
    double integral = adaptiveSimpson(left, right, leftValue, midValue, rightValue, wholeValue, 1e-10, 30, x, d);
    return integral / length;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, caseIndex;
    cin >> testCount;
    for (caseIndex = 1; caseIndex <= testCount; caseIndex++) {
        int x, y1, y2, d;
        cin >> x >> y1 >> y2 >> d;
        cout << "Case " << caseIndex << ": " << fixed << setprecision(6) << solveCase(x, y1, y2, d) << '\n';
    }
    return 0;
}
