#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
};

struct Line {
    long double nx, ny, c, len;
};

const long double pi = acosl(-1.0L);
Point point[3];
Line lineData[3];
long double edgeLen[3], areaValue, productValue, rootValue;

long double calcValue(long double t) {
    long double sum = 0.0L, valueA = sqrtl(productValue) * expl(t), valueB = sqrtl(productValue) * expl(-t);
    for (int i = 0; i < 3; i++) {
        long double distance = sqrtl(lineData[i].nx * lineData[i].nx * valueA + lineData[i].ny * lineData[i].ny * valueB);
        sum += edgeLen[i] * distance;
    }
    return sum - 2.0L * areaValue;
}

void buildData() {
    long double crossValue = (point[1].x - point[0].x) * (point[2].y - point[0].y) - (point[1].y - point[0].y) * (point[2].x - point[0].x);
    areaValue = fabsl(crossValue) * 0.5L;
    for (int i = 0; i < 3; i++) {
        int nextIndex = (i + 1) % 3;
        long double dx = point[nextIndex].x - point[i].x, dy = point[nextIndex].y - point[i].y;
        long double length = sqrtl(dx * dx + dy * dy);
        edgeLen[i] = length;
        lineData[i].len = length;
        lineData[i].nx = -dy / length;
        lineData[i].ny = dx / length;
        lineData[i].c = (dy * point[i].x - dx * point[i].y) / length;
    }
}

void findRoot() {
    long double left = -logl(10.0L), right = logl(10.0L);
    for (int i = 0; i < 160; i++) {
        long double mid1 = (2.0L * left + right) / 3.0L, mid2 = (left + 2.0L * right) / 3.0L;
        if (calcValue(mid1) < calcValue(mid2))
            right = mid2;
        else
            left = mid1;
    }
    long double minPoint = (left + right) * 0.5L, minValue = calcValue(minPoint);
    long double leftValue = calcValue(-logl(10.0L)), rightValue = calcValue(logl(10.0L));
    long double searchLeft, searchRight;
    if (fabsl(leftValue) < 1e-18L) {
        rootValue = -logl(10.0L);
        return;
    }
    if (fabsl(rightValue) < 1e-18L) {
        rootValue = logl(10.0L);
        return;
    }
    if (fabsl(minValue) < 1e-18L) {
        rootValue = minPoint;
        return;
    }
    if (leftValue > 0.0L) {
        searchLeft = -logl(10.0L);
        searchRight = minPoint;
    } else {
        searchLeft = minPoint;
        searchRight = logl(10.0L);
    }
    for (int i = 0; i < 180; i++) {
        long double mid = (searchLeft + searchRight) * 0.5L;
        if (calcValue(searchLeft) * calcValue(mid) <= 0.0L)
            searchRight = mid;
        else
            searchLeft = mid;
    }
    rootValue = (searchLeft + searchRight) * 0.5L;
}

void getCenter(long double valueA, long double valueB, long double &centerX, long double &centerY) {
    long double distance[3];
    for (int i = 0; i < 3; i++)
        distance[i] = sqrtl(lineData[i].nx * lineData[i].nx * valueA + lineData[i].ny * lineData[i].ny * valueB);
    long double right1 = distance[0] - lineData[0].c, right2 = distance[1] - lineData[1].c;
    long double determinant = lineData[0].nx * lineData[1].ny - lineData[1].nx * lineData[0].ny;
    centerX = (right1 * lineData[1].ny - right2 * lineData[0].ny) / determinant;
    centerY = (lineData[0].nx * right2 - lineData[1].nx * right1) / determinant;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long double x1, y1, x2, y2, x3, y3, ellipseArea;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> ellipseArea) {
        if (ellipseArea < 0.0L)
            break;
        point[0] = {x1, y1};
        point[1] = {x2, y2};
        point[2] = {x3, y3};
        productValue = (ellipseArea / pi) * (ellipseArea / pi);
        buildData();
        findRoot();
        long double valueA = sqrtl(productValue) * expl(rootValue), valueB = sqrtl(productValue) * expl(-rootValue);
        long double centerX, centerY;
        getCenter(valueA, valueB, centerX, centerY);
        cout << fixed << setprecision(10) << centerX << ' ' << centerY << ' ' << sqrtl(valueA) << ' ' << sqrtl(valueB) << '\n';
    }
    return 0;
}
