#include <bits/stdc++.h>
using namespace std;

struct Circle {
    double x, y, r;
};

struct Rect {
    double x1, y1, x2, y2;
};

double arcIntegral(double value, double radius) {
    double part = sqrt(max(0.0, radius * radius - value * value));
    return 0.5 * (value * part + radius * radius * asin(value / radius));
}

double circleRectArea(const Circle &circle, const Rect &rect) {
    double left = max(rect.x1, circle.x - circle.r), right = min(rect.x2, circle.x + circle.r);
    if (left >= right || rect.y1 >= rect.y2) return 0.0;
    vector<double> cuts;
    cuts.push_back(left);
    cuts.push_back(right);
    double delta1 = rect.y1 - circle.y, delta2 = rect.y2 - circle.y;
    if (abs(delta1) < circle.r) {
        double offset = sqrt(circle.r * circle.r - delta1 * delta1);
        double point1 = circle.x - offset, point2 = circle.x + offset;
        if (point1 > left && point1 < right) cuts.push_back(point1);
        if (point2 > left && point2 < right) cuts.push_back(point2);
    }
    if (abs(delta2) < circle.r) {
        double offset = sqrt(circle.r * circle.r - delta2 * delta2);
        double point1 = circle.x - offset, point2 = circle.x + offset;
        if (point1 > left && point1 < right) cuts.push_back(point1);
        if (point2 > left && point2 < right) cuts.push_back(point2);
    }
    sort(cuts.begin(), cuts.end());
    vector<double> uniqueCuts;
    for (double value : cuts)
        if (uniqueCuts.empty() || value - uniqueCuts.back() > 1e-10) uniqueCuts.push_back(value);
    double area = 0.0;
    for (int i = 0; i + 1 < (int)uniqueCuts.size(); i++) {
        double begin = uniqueCuts[i], end = uniqueCuts[i + 1];
        double middle = (begin + end) * 0.5;
        double offset = middle - circle.x;
        double height = sqrt(max(0.0, circle.r * circle.r - offset * offset));
        double lowerCircle = circle.y - height, upperCircle = circle.y + height;
        double constantPart = 0.0, sqrtCoefficient = 0.0;
        if (rect.y1 > lowerCircle) constantPart -= rect.y1;
        else {
            constantPart -= circle.y;
            sqrtCoefficient += 1.0;
        }
        if (rect.y2 < upperCircle) constantPart += rect.y2;
        else {
            constantPart += circle.y;
            sqrtCoefficient += 1.0;
        }
        if (constantPart + sqrtCoefficient * height <= 0.0) continue;
        double value1 = begin - circle.x, value2 = end - circle.x;
        double integral = constantPart * (end - begin);
        integral += sqrtCoefficient * (arcIntegral(value2, circle.r) - arcIntegral(value1, circle.r));
        area += integral;
    }
    return area;
}

double getRectArea(const vector<Circle> &circles, const Rect &rect) {
    double area = 0.0;
    for (const Circle &circle : circles) area += circleRectArea(circle, rect);
    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCases;
    cin >> testCases;
    cout << fixed << setprecision(8);
    for (int caseNumber = 1; caseNumber <= testCases; caseNumber++) {
        int n, m;
        long long brushX, brushY, k;
        cin >> n >> brushX >> brushY >> k >> m;
        vector<Circle> circles(n);
        double totalArea = 0.0;
        for (int i = 0; i < n; i++) {
            cin >> circles[i].x >> circles[i].y >> circles[i].r;
            totalArea += acos(-1.0) * circles[i].r * circles[i].r;
        }
        Rect rect;
        rect.x1 = brushX;
        rect.y1 = brushY;
        rect.x2 = brushX + k;
        rect.y2 = brushY + k;
        double paintArea = getRectArea(circles, rect);
        long long currentX = brushX, currentY = brushY;
        for (int i = 0; i < m; i++) {
            string direction;
            long long moves;
            cin >> direction >> moves;
            if (direction == "east") {
                rect.x1 = currentX + k;
                rect.y1 = currentY;
                rect.x2 = currentX + (moves + 1) * k;
                rect.y2 = currentY + k;
                currentX += moves * k;
            } else if (direction == "west") {
                rect.x1 = currentX - moves * k;
                rect.y1 = currentY;
                rect.x2 = currentX;
                rect.y2 = currentY + k;
                currentX -= moves * k;
            } else if (direction == "north") {
                rect.x1 = currentX;
                rect.y1 = currentY + k;
                rect.x2 = currentX + k;
                rect.y2 = currentY + (moves + 1) * k;
                currentY += moves * k;
            } else {
                rect.x1 = currentX;
                rect.y1 = currentY - moves * k;
                rect.x2 = currentX + k;
                rect.y2 = currentY;
                currentY -= moves * k;
            }
            paintArea += getRectArea(circles, rect);
        }
        double percentage = paintArea * 100.0 / totalArea;
        cout << "Case " << caseNumber << ": " << percentage << '\n';
    }
    return 0;
}
