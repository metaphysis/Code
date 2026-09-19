#include <bits/stdc++.h>
using namespace std;

const long double Eps = 1e-12L;

struct Point {
    long double x, y;
};

struct Circle {
    long double x, y, r;
};

struct Arc {
    int circleId;
    long double leftY, rightY, midY;
    bool upper;
};

long double SafeSqrt(long double value) {
    return sqrtl(max(value, 0.0L));
}

long double SafeAcos(long double value) {
    return acosl(max(-1.0L, min(1.0L, value)));
}

Circle BuildCircle(Point first, Point second) {
    Circle circle;
    long double dx = first.x - second.x, dy = first.y - second.y;
    circle.x = (first.x + second.x) * 0.5L;
    circle.y = (first.y + second.y) * 0.5L;
    circle.r = SafeSqrt(dx * dx + dy * dy) * 0.5L;
    return circle;
}

void AddIntersectionX(const Circle &first, const Circle &second, vector<long double> &xs) {
    long double dx = second.x - first.x, dy = second.y - first.y;
    long double distance = SafeSqrt(dx * dx + dy * dy);
    if (distance < Eps) return;
    if (distance > first.r + second.r + Eps) return;
    if (distance < fabsl(first.r - second.r) - Eps) return;
    long double along = (distance * distance + first.r * first.r - second.r * second.r) / (2.0L * distance);
    long double height = SafeSqrt(first.r * first.r - along * along);
    long double baseX = first.x + dx * along / distance;
    long double offsetX = fabsl(dy * height / distance);
    xs.push_back(baseX - offsetX);
    xs.push_back(baseX + offsetX);
}

bool IsValid(long double x, long double y, const vector<Circle> &circles) {
    int outsideCount = 0;
    for (const Circle &circle : circles) {
        long double dx = x - circle.x, dy = y - circle.y;
        long double distance = SafeSqrt(dx * dx + dy * dy);
        if (distance > circle.r - 1e-10L) outsideCount++;
    }
    return outsideCount > 0 && outsideCount < 4;
}

long double GetArcArea(const Arc &arc, long double leftX, long double rightX, const vector<Circle> &circles) {
    const Circle &circle = circles[arc.circleId];
    long double dx1 = leftX - circle.x, dx2 = rightX - circle.x;
    long double dy1 = arc.leftY - circle.y, dy2 = arc.rightY - circle.y;
    long double dot = dx1 * dx2 + dy1 * dy2;
    long double cross = dx1 * dy2 - dx2 * dy1;
    long double cosine = dot / (circle.r * circle.r);
    long double angle = SafeAcos(cosine);
    return (circle.r * circle.r * angle - fabsl(cross)) * 0.5L;
}

long double GetArea(Point a1, Point a2, Point b1, Point b2) {
    vector<Circle> circles;
    vector<long double> xs;
    Point as[2] = {a1, a2}, bs[2] = {b1, b2};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            circles.push_back(BuildCircle(as[i], bs[j]));
    for (const Circle &circle : circles) {
        xs.push_back(circle.x - circle.r);
        xs.push_back(circle.x + circle.r);
    }
    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 4; j++)
            AddIntersectionX(circles[i], circles[j], xs);
    sort(xs.begin(), xs.end());
    long double answer = 0.0L;
    for (int i = 1; i < (int)xs.size(); i++) {
        long double leftX = xs[i - 1], rightX = xs[i];
        if (rightX - leftX < Eps) continue;
        long double midX = (leftX + rightX) * 0.5L;
        vector<Arc> arcs;
        for (int j = 0; j < 4; j++) {
            const Circle &circle = circles[j];
            long double midSquare = circle.r * circle.r - (midX - circle.x) * (midX - circle.x);
            if (midSquare < -Eps || circle.r < Eps) continue;
            long double leftDelta = SafeSqrt(circle.r * circle.r - (leftX - circle.x) * (leftX - circle.x));
            long double rightDelta = SafeSqrt(circle.r * circle.r - (rightX - circle.x) * (rightX - circle.x));
            long double midDelta = SafeSqrt(midSquare);
            arcs.push_back({j, circle.y - leftDelta, circle.y - rightDelta, circle.y - midDelta, false});
            arcs.push_back({j, circle.y + leftDelta, circle.y + rightDelta, circle.y + midDelta, true});
        }
        sort(arcs.begin(), arcs.end(), [](const Arc &first, const Arc &second) {
            if (fabsl(first.midY - second.midY) > Eps) return first.midY < second.midY;
            if (first.upper != second.upper) return first.upper < second.upper;
            return first.circleId < second.circleId;
        });
        for (int j = 1; j < (int)arcs.size(); j++) {
            long double testY = (arcs[j - 1].midY + arcs[j].midY) * 0.5L;
            if (!IsValid(midX, testY, circles)) continue;
            const Arc &lower = arcs[j - 1], &upper = arcs[j];
            long double heightSum = upper.leftY + upper.rightY - lower.leftY - lower.rightY;
            long double stripArea = fabsl(heightSum) * (rightX - leftX) * 0.5L;
            long double upperArea = GetArcArea(upper, leftX, rightX, circles);
            long double lowerArea = GetArcArea(lower, leftX, rightX, circles);
            if (upper.upper) stripArea += upperArea;
            else stripArea -= upperArea;
            if (lower.upper) stripArea -= lowerArea;
            else stripArea += lowerArea;
            answer += stripArea;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x1, y1, x2, y2, x3, y3, x4, y4, caseId = 1;
    while (cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4) {
        if (x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0 && x3 == 0 && y3 == 0 && x4 == 0 && y4 == 0) break;
        Point a1 = {(long double)x1, (long double)y1};
        Point a2 = {(long double)x2, (long double)y2};
        Point b1 = {(long double)x3, (long double)y3};
        Point b2 = {(long double)x4, (long double)y4};
        long double answer = GetArea(a1, a2, b1, b2);
        if (fabsl(answer) < 0.0005L) answer = 0.0L;
        cout << "Case " << caseId++ << ": " << fixed << setprecision(3) << answer << "\n\n";
    }
    return 0;
}
